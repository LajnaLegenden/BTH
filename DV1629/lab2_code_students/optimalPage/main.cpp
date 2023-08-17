#include <fstream>
#include <iostream>
#include <vector>
#include "page.h"

#define MAX 99999

void readFile(const std::string &fileName, std::vector<int> *out) {
    std::string line;
    std::ifstream theFile;
    theFile.open(fileName);

    if (!theFile.is_open()) {
        perror("Error open");
        exit(EXIT_FAILURE);
    }
    while (getline(theFile, line)) {
        out->push_back(std::stoi(line));
    }
}

bool isInMemory(int value, std::vector<Page> &memory) {
    for (auto &pageIndex: memory) {
        if (pageIndex.has(value)) {
            return true;
        }
    }
    return false;
}

bool hasNone(int value, const std::vector<int> &data) {
    for (int i: data) {
        if (i == value) {
            return false;
        }
    }
    return true;
}


int
predict(const std::vector<Page> &memory, const std::vector<int> &data, const int &currentIndex, const int &numPages) {
    std::vector<int> distance(numPages, -1);
    int index = currentIndex;
    while (!hasNone(-1, distance) && index < MAX) {
        for (int pageIndex = 0; pageIndex < numPages; pageIndex++) {
            if (distance[pageIndex] == -1) {
                if (memory[pageIndex].has(data[index])) {
                    distance[pageIndex] = index - currentIndex;
                }
            }
        }
        index++;
    }

    int maxIndex = 0;
    int max = -2;
    for (int d = 0; d < numPages; d++) {
        if (distance[d] > max) {
            max = distance[d];
            maxIndex = d;
        }
    }
    return maxIndex;

}

void optimal(const std::vector<int> &data, const int &numPages, const int &pageSize) {
    int misses = 0, hits = 0, fullPages = 0;
    std::vector<Page> memory;
    for (int i = 0; i < numPages; i++) {
        memory.emplace_back(pageSize);
    }
    for (int addressIndex = 0; addressIndex < MAX; addressIndex++) {
        if (addressIndex % 10000 == 0) {
            printf("Progress %i/%i\n", addressIndex, MAX);
            fflush(stdout);
        }

        int currentItem = data[addressIndex];

        if (isInMemory(currentItem, memory)) {
            hits++;
            continue;
        }

        if (fullPages < numPages) {
            if (memory[fullPages].add(currentItem)) {
                fullPages++;
            }
        } else {
            misses++;
            int pageToOverwrite = predict(memory, data, addressIndex, numPages);
            fullPages--;
            //Shift pages to fill the gap
            for (int i = pageToOverwrite; i == numPages - 1; i++) {
                memory[i] = memory[i + 1];
            }
            Page p = Page(pageSize);
            p.add(currentItem);
            memory[fullPages] = p;
        }
    }
    printf("Misses %i\n", misses);


}

int main(int argc, char **argv) {

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

    std::vector<int> data;
    readFile(filename, &data);

    optimal(data, no_phys_pages, page_size);


    return 0;
}