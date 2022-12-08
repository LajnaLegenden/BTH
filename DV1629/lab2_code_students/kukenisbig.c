#include <stdio.h>
#include <stdlib.h>

#define MAX 99999

struct Page {
    int *data;
    int size;
};


int hasItem(struct Page page, int item) {
    //Chceks if the page has the item
    for (int i = 0; i < page.size; i++) {
        //printf("%i - %i", page.data[i], item);
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


int predict(int *data, struct Page memory[], int _index, int maxAddress, int numPages) {
    int furthestIndex = -1;
    int distance[numPages];
    for (int f = 0; f < numPages; ++f) {
        distance[f] = -10;
    }
    for(int index = _index; index < maxAddress; index++){
        for (int pageIndex = 0; pageIndex < numPages; pageIndex++) {
            if(hasItem(memory[pageIndex], data[index]) == 1){
                furthestIndex = pageIndex;
                distance[pageIndex] = index;
            }
        }
    }
    return furthestIndex;
}

void optimalPage(int *data, struct Page *memory_pages, int numPages, int pageSize) {
    int misses = 0, hits = 0, fullPages = 0;

    for (int addressIndex = 0; addressIndex < MAX; addressIndex++) {
        if (addressIndex % 5000 == 0) {
            printf("Progress %i/%i\n", addressIndex, MAX);
            printf("Misses %i\n", misses);
            fflush(stdout);
        }

        int currentItem = data[addressIndex];
        if (isInMemory(memory_pages, currentItem, numPages) == 1) {
            hits++;
            continue;
        }


        if (fullPages < numPages) {
            int full = addToFrame(&memory_pages[fullPages], currentItem, pageSize);
            if (full == 1)
                fullPages++;
        } else {
            int frameIndexToDelete = predict(data, memory_pages, addressIndex, MAX, numPages);
            misses++;
            //printf("Removing page %i\n", frameIndexToDelete);
            fflush(stdout);
            struct Page newPage;
            newPage.data = (int *) malloc(pageSize * sizeof(int));
            for (int q = 0; q < pageSize; ++q) {
                newPage.data[q] = -1;
            }
            newPage.size = 1;
            newPage.data[0] = currentItem;
            memory_pages[frameIndexToDelete] = newPage;
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
        for (int q = 0; q < page_size; ++q) {
            frame_items[i].data[q] = -1;
        }
        frame_items[i].size = 0;
    }
    optimalPage(array, frame_items, no_phys_pages, page_size);
    return 0;
}
