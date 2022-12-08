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

/* void shiftPage(struct Page *newPage, struct Page *memory, int noPages)
{
    for (int i = noPages - 1; i > 0; i--)
    {
        memory[i] = memory[i - 1];
    }
    memory[0] = *newPage;
}
 */
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
    // LRU page implementation
    int noPages = 0;
    int noFaults = 0;
    int noHits = 0;
    int noEvictions = 0;
    int noAccesses = 0;

    struct Page memory[no_phys_pages];
    for (int i = 0; i < no_phys_pages; i++)
    {
        memory[i].data = malloc(page_size * sizeof(int));
        memory[i].size = 0;
    }

    for (int i = 0; i < MAX; i++)
    {
        int num = array[i];
        int page = num / page_size;
        int offset = num % page_size;
        int pageExists = 0;
        int pageExistsIndex = 0;
        for (int j = 0; j < noPages; j++)
        {
            if (memory[j].data[0] == page)
            {
                pageExists = 1;
                pageExistsIndex = j;
                break;
            }
        }
        if (pageExists)
        {
            noHits++;
            noAccesses++;
            // shiftPage(&memory[pageExistsIndex], memory, noPages);
            struct Page temp = memory[pageExistsIndex];
            for (int j = pageExistsIndex; j > 0; j--)
            {
                memory[j] = memory[j - 1];
            }
            memory[0] = temp;
        }
        else
        {
            noFaults++;
            noAccesses++;
            if (noPages < no_phys_pages)
            {
                memory[noPages].data[0] = page;
                memory[noPages].size = 1;
                noPages++;
            }
            else
            {
                noEvictions++;
                memory[noPages - 1].data[0] = page;
                memory[noPages - 1].size = 1;
                // shiftPage(&memory[noPages - 1], memory, noPages);
                struct Page temp = memory[noPages - 1];
                for (int j = noPages - 1; j > 0; j--)
                {
                    memory[j] = memory[j - 1];
                }
                memory[0] = temp;
            }
        }
    }
    printf("Number of accesses: %i", noAccesses);
    printf("Number of hits: %i", noHits);
    printf("Number of faults: %i", noFaults);
    printf("Number of evictions: %i", noEvictions);

    return 0;
}