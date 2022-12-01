#include <stdio.h>
#include <stdlib.h>

#define MAX 99999

struct Page
{
    int *data;
    int size;
};

int hasItem(struct Page page, int item)
{
    for (int i = 0; i < page.size; i++)
    {
        printf("page.data[i] = %i, item = %i\n", page.data[i], item);
        if (page.data[i] == item)
        {
            return 1;
        }
    }
    return 0;
}

// predict funtion for optimal page replacement
int predict(int ref_str[], struct Page frame_items[], int refStrLen, int index, int frame_occupied)
{
    // For each current occupant in frame item
    // we try to find the frame item that will not be referenced in
    // for the longest in future in the upcoming reference string
    int result = -1, farthest = index;
    for (int i = 0; i < frame_occupied; i++)
    {
        int j;
        for (j = index; j < refStrLen; j++)
        {
            if (hasItem(frame_items[i], ref_str[j]))
            {
                if (j > farthest)
                {
                    farthest = j;
                    result = i;
                }
                break;
            }
        }

        // If we find a page that is never referenced in future,
        // return it immediately as its the best
        if (j == refStrLen)
            return i;
    }

    // If none of the frame items appear in reference string
    // in the future then we return 0th index. Otherwise we return result
    return (result == -1) ? 0 : result;
}

// bool search function for optimal page replacement
int search(int key, struct Page frame_items[], int frame_occupied)
{
    for (int i = 0; i < frame_occupied; i++)
        if (hasItem(frame_items[i], key))
            return 1;
    return 0;
}

// page replacement function for optimal page replacement
void optimalPage(int ref_str[], int refStrLen, struct Page frame_items[], int max_frames, int page_size)
{
    // initially none of the frames are occupied
    int frame_occupied = 0;
    int page_faults = 0;
    int hit = 0;

    // Traverse through the reference string
    for (int i = 0; i < refStrLen; i++)
    {
        // If the page is not present in the memory, bring it in
        if (!search(ref_str[i], frame_items, page_size))
        {
            int added = 0;
            for (int j = 0; j < max_frames; j++)
            {
                if (frame_items[j].size < page_size)
                {
                    frame_items[j].data[frame_items[j].size] = ref_str[i];
                    frame_items[j].size++;
                    added = 1;
                    break;
                }
            }
            if (!added)
            {
                // Find the page that will not be used in the future
                int j = predict(ref_str, frame_items, refStrLen, i + 1, frame_occupied);

                struct Page newPage;
                newPage.size = 1;
                newPage.data = malloc(sizeof(int) * page_size);
                newPage.data[0] = ref_str[i];
                // Replace the page with the new page
                frame_items[j] = newPage;
            }

            // Increment the page fault
            page_faults++;
        }
        else
        {
            // print
            printf("Page %d already in memory\n", ref_str[i]);
            hit++;
        }
    }

    // Print the number of page faults
    printf("Number of page faults : %d\n", page_faults);
    printf("Number of page hits : %d\n", hit);
}

int main(int argc, char *argv[])
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
    int array[MAX];
    int i = 0;
    while (fscanf(fp, "%d", &array[i]))
    {
        i++;
        if (i == MAX)
            break;
    }
    fclose(fp);
    printf("Read %i memory references\n", i + 1);
    struct Page frame_items[no_phys_pages];
    for (int i = 0; i < no_phys_pages; i++)
    {
        frame_items[i].data = (int *)malloc(page_size * sizeof(int));
        frame_items[i].size = 0;
    }
    optimalPage(array, MAX, frame_items, no_phys_pages, page_size);
    return 0;
}
