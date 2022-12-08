#include <stdio.h>
#include <stdlib.h>
#define MAX 99999

struct Page
{
    int *data;
    int size;
};

int numExistsInPage(int num, struct Page *page)
{

    for (int i = 0; i < page->size; i++)
    {
        if (page->data[i] == num)
        {
            return 1;
        }
    }
    return 0;
}

void shiftPage(struct Page *newPage, struct Page *memory, int noPages)
{
    for (int i = noPages - 1; i > 0; i--)
    {
        memory[i] = memory[i - 1];
    }
    memory[0] = *newPage;
}

int main(int argc, char **argv)
{

    if (argc != 4)
    {
        printf("Usage: no_phys_pages page_size filename");
        return -1;
    }
    // Load file into int array
    int no_phys_pages = atoi(argv[1]);
    int page_size = atoi(argv[2]);
    char *filename = argv[3];
    printf("No physical pages = %i, page size = %i\n", no_phys_pages, page_size);
    printf("Reading memory trace from %s ...\n", filename);
    struct Page memory[no_phys_pages];

    // read file of integers to array
    FILE *fp = fopen(filename, "r");
    int *array = malloc(MAX * sizeof(int));
    int i = 0;
    while (fscanf(fp, "%d", &array[i]))
    {
        i++;
        if (i == MAX)
            break;
    }
    fclose(fp);
    printf("Read %i memory references\n", i + 1);

    for (int i = 0; i < no_phys_pages; i++)
    {
        struct Page f;
        f.size = 0;
        f.data = malloc(page_size * sizeof(int));
        shiftPage(&f, memory, no_phys_pages);
    }
    int pageFaults = 0;
    for (int currentNumIndex = 0; currentNumIndex < MAX; currentNumIndex++)
    {
        int currentNum = array[currentNumIndex];
        // check if currentNum is in memory
        int found = 0;
        for (int i = 0; i < no_phys_pages; i++)
        {
            if (numExistsInPage(currentNum, &memory[i]))
            {
                found = 1;
                break;
            }
        }
        // If yes, do nothing continue
        if (found)
            continue;

        // If not in memory, add to a page if there is space in the page else add to a new page
        pageFaults++;

        int added = 0;
        for (int i = 0; i < no_phys_pages; i++)
        {
            if (memory[i].size < page_size)
            {
                memory[i].data[memory[i].size] = currentNum;
                memory[i].size++;
                added = 1;
                break;
            }
        }
        if (!added)
        {
            struct Page newPage;
            newPage.data = malloc(page_size * sizeof(int));
            newPage.data[0] = currentNum;
            newPage.size = 1;
            shiftPage(&newPage, memory, no_phys_pages);
        }
    }

    return 0;
}