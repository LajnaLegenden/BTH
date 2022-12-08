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
    // FIFO page implementation
    int pageFaults = 0;
    int pageHits = 0;
    int page = 0;

    for (int i = 0; i < MAX; i++)
    {
        if (numExistsInPage(array[i], &memory[page]) == 0)
        {
            pageFaults++;
            memory[page].data[memory[page].size] = array[i];
            memory[page].size++;
            if (memory[page].size == page_size)
            {
                page++;
                if (page == no_phys_pages)
                {
                    page = 0;
                }
            }
        }
        else
        {
            pageHits++;
        }
    }
    printf("Page faults: %i", pageFaults);

    return 0;
}