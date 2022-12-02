#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 99999

struct Page {
    int *data;
    int size;
};



int hasItem(struct Page page, int item) {
    for (int i = 0; i < page.size; i++) {
        if (page.data[i] == item) {
            return 1;
        }
    }
    return 0;
}


int isInMemory(struct Page *memory, int item, int numPages) {
    for (int frameIndex = 0; frameIndex < numPages; frameIndex++) {
        for (int itemIndex = 0; itemIndex < memory[frameIndex].size; itemIndex++) {
            if (memory[frameIndex].data[itemIndex] == item)
                return 1;
        }
    }
    return 0;
}

int addToFrame(struct Page *page, int item, int itemsPerPage) {
    page->data[page->size] = item;
    page->size++;
    return page->size == itemsPerPage - 1 ? 1 : 0;
}


int predict(int *data, struct Page memory[], int index, int maxAddress, int numPages) {
    //predict page index to be replaced using OPtimal algorithm
    int i, frameIndex;
    int ttUse[numPages];
    for (i = 0; i < numPages; i++) {
        ttUse[i] = -1;
    }
    int isDone = 0;
    for (i = index; i < maxAddress; i++) {
        for (frameIndex = 0; frameIndex < numPages; frameIndex++) {
            if (ttUse[frameIndex] != -1) continue;
            if (hasItem(memory[frameIndex], data[i])) {
                if (ttUse[frameIndex] == -1) {
                    ttUse[frameIndex] = i - index;
                }
            }
        }
        isDone = 1;
        for (int k = 0; k < numPages; k++) {
            if (ttUse[k] == -1) {
                isDone = 0;
            }
        }
        if (isDone) {
            break;
        }
    }
    int max = 0;
    int maxIndex = 0;
    for (int k = 0; k < numPages; k++) {
        if (ttUse[k] > max) {
            max = ttUse[k];
            maxIndex = k;
        }
    }
    return maxIndex;
}

void optimalPage(int *data, struct Page *memory_pages, int numPages, int pageSize) {
    int misses = 0, hits = 0, fullPages = 0;

    for (int addressIndex = 0; addressIndex < MAX; addressIndex++) {
        if(addressIndex % 5000 == 0){
            printf("Progress %i/%i", addressIndex,MAX);
            fflush(stdout);
        }

        int currentItem = data[addressIndex];
        if (isInMemory(memory_pages, currentItem, numPages)) {
            hits++;
            continue;
        }
        misses++;

        if (fullPages < numPages) {
            int full = addToFrame(&memory_pages[fullPages], currentItem, pageSize);
            if (full == 1)
                fullPages++;
        } else {
            int frameIndexToDelete = predict(data, memory_pages, addressIndex, MAX, numPages);
            struct Page newPage;
            newPage.data = (int *) malloc(pageSize * sizeof(int));
            newPage.size = 1;
            newPage.data[0] = currentItem;
        }
    }

    printf("Misses: %i", misses);


}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: no_phys_pages page_size filename\n");
        return -1;
    }
    // Load file into int array
    int no_phys_pages = atoi(argv[1]);
    int page_size = atoi(argv[2]);
    char *filename = argv[3];
    printf("No physical pages = %i, page size = %i\n", no_phys_pages, page_size);
    printf("Reading memory trace from %s ...\n", filename);

    // read file of integers to array
    FILE *fp = fopen(filename, "r");
    int array[MAX];
    int i = 0;
    while (fscanf(fp, "%d", &array[i])) {
        i++;
        if (i == MAX)
            break;
    }
    fclose(fp);
    printf("Read %i memory references\n", i + 1);
    struct Page frame_items[no_phys_pages];
    for (int i = 0; i < no_phys_pages; i++) {
        frame_items[i].data = (int *) malloc(page_size * sizeof(int));
        frame_items[i].size = 0;
    }
    optimalPage(array, frame_items, no_phys_pages, page_size);
    return 0;
}
