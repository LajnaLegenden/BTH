#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

#define MAX 99999

std::vector<int> readFile(const std::string &fileName) {
    std::string line;
    std::ifstream theFile;
    theFile.open(fileName);

    if (!theFile.is_open()) {
        perror("Error open");
        exit(EXIT_FAILURE);
    }

    std::vector<int> out;
    while (getline(theFile, line)) {
        out.push_back(std::stoi(line));
    }
    return out;
}

bool hasNone(int value, const std::vector<int> &data) {
    for (int i: data) {
        if (i == value) {
            return false;
        }
    }
    return true;
}


int predict(const std::vector<int> &data, const std::vector<int> &mem, int currentIndex, int numPages, int pageSize) {
//predict the next time the page will be used
    std::vector<int> distance(numPages, -1);

    // -1 -1 -1 -1
    for (int i = currentIndex + 1; i < MAX; i++) {
        int currentPageIndex = data[i] / pageSize;
        for (int pageIndex = 0; pageIndex < numPages; pageIndex++) {
            if (mem[pageIndex] == currentPageIndex) {
                distance[pageIndex] = i - currentIndex;
            }
        }
        if (hasNone(-1, distance))
            goto minmaxCount;
    }
    minmaxCount:
    int maxElementIndex = std::max_element(distance.begin(), distance.end()) - distance.begin();
    int minElementIndex = std::min_element(distance.begin(), distance.end()) - distance.begin();
    int minElement = *std::min_element(distance.begin(), distance.end());

    if (minElement == -1) {
        return minElementIndex;
    }
    return maxElementIndex;
}

void optimal(const std::vector<int> &data, const int &numPages, const int &pageSize) {
    int misses = 0, hits = 0;
    std::vector<int> mem;
    for (int i = 0; i < numPages; i++) {
        mem.push_back(-1);
    }

    for (int addressIndex = 0; addressIndex < MAX; addressIndex++) {

        int currentItem = data[addressIndex];
        int index = currentItem / pageSize;
        bool hasAdded = false;
        for (int i = 0; i < numPages; i++) {
            if (mem[i] == index) {
                hasAdded = true;
                break;
            } else if (mem[i] == -1) {
                mem[i] = index;
                misses++;
                hasAdded = true;
                break;
            }
        }

        if (!hasAdded) {
            misses++;
            int indexToReplace = predict(data, mem, addressIndex, numPages, pageSize);
            //       printf("removin page index %i\n", indexToReplace);
            for (int i = indexToReplace; i < numPages; i++) {
                mem[i] = mem[i + 1];
            }
            mem[numPages - 1] = index;
        }
    }
    printf("Misses %i\n", misses);
}

int main(int argc, char **argv) {
    srand(time(NULL));
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


    std::vector<int> data = readFile(filename);

    optimal(data, no_phys_pages, page_size);


    return 0;
}