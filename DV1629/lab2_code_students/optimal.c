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
    // Optimal page replacement (Bélády’s algorithm) implementation
    int hits = 0;
    int misses = 0;
    int noPages = 0;
    struct Page memory[no_phys_pages];
    for (int i = 0; i < no_phys_pages; i++)
    {
        memory[i].data = malloc(page_size * sizeof(int));
        memory[i].size = 0;
    }

    for (int i = 0; i < MAX; i++)
    {
        int num = array[i];
        int found = 0;
        for (int j = 0; j < noPages; j++)
        {
            if (numExistsInPage(num, &memory[j]))
            {
                hits++;
                found = 1;
                break;
            }
        }
        if (found)
        {
            continue;
        }
        else
        {
            misses++;
            if (noPages < no_phys_pages)
            {
                memory[noPages].data[0] = num;
                memory[noPages].size = 1;
                noPages++;
            }
            else
            {
                int max = 0;
                int maxIndex = 0;
                for (int j = 0; j < noPages; j++)
                {
                    int count = 0;
                    for (int k = i + 1; k < i + 1; k++)
                    {
                        if (numExistsInPage(array[k], &memory[j]))
                        {
                            break;
                        }
                        count++;
                    }
                    if (count > max)
                    {
                        max = count;
                        maxIndex = j;
                    }
                }
                memory[maxIndex].data[0] = num;
                memory[maxIndex].size = 1;
            }
        }
    }
    printf("Hits = %i, misses = %i, hit ratio = %f\n", hits, misses, (float)hits / (float)(hits + misses));
    return 0;
}