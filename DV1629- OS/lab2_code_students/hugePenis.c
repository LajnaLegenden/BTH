#include <stdio.h>
#include <stdlib.h>
#define MAX 99999

// This function checks if current strea item(key) exists in any of the frames or not
int search(int key, int frame_items[], int frame_occupied)
{
    for (int i = 0; i < frame_occupied; i++)
        if (frame_items[i] == key)
            return 1;
    return 0;
}

void printOuterStructure(int max_frames)
{
}
void printCurrFrames(int item, int frame_items[], int frame_occupied, int max_frames)
{
}
// This Function helps in finding frame that will not be used
// for the longest period of time in future in ref_str[0 ... refStrLen - 1]
int predict(int ref_str[], int frame_items[], int refStrLen, int index, int frame_occupied)
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
            if (frame_items[i] == ref_str[j])
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

void optimalPage(int ref_str[], int refStrLen, int frame_items[], int max_frames)
{
    // initially none of the frames are occupied
    int frame_occupied = 0;
    printOuterStructure(max_frames);

    // Here we traverse through reference string
    // and check for miss and hit.
    int hits = 0;
    for (int i = 0; i < refStrLen; i++)
    {

        // If found already in the frame items : HIT
        if (search(ref_str[i], frame_items, frame_occupied))
        {
            hits++;
            printCurrFrames(ref_str[i], frame_items, frame_occupied, max_frames);
            continue;
        }

        // If not found in frame items : MISS

        // If frames are empty then current reference string item in frame
        if (frame_occupied < max_frames)
        {
            frame_items[frame_occupied] = ref_str[i];
            frame_occupied++;
            printCurrFrames(ref_str[i], frame_items, frame_occupied, max_frames);
        }
        // else we need to use optmial algorithm to find
        // frame index where we need to do replacement for this
        // incoming reference string item
        else
        {
            int pos = predict(ref_str, frame_items, refStrLen, i + 1, frame_occupied);
            frame_items[pos] = ref_str[i];
            printCurrFrames(ref_str[i], frame_items, frame_occupied, max_frames);
        }
    }
    printf("\n\nHits: %d\n", hits);
    printf("Misses: %d", refStrLen - hits);
}

// Driver Function
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
    int max_frames = page_size;
    int frame_items[max_frames];

    optimalPage(array, MAX, frame_items, max_frames);
    return 0;
}