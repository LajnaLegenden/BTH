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

void fifo(const std::vector<int> &data, const int &numPages, const int &pageSize) {
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

        if(!hasAdded){
            misses++;
            for (int i = 0; i < numPages; i++) {
                mem[i] = mem[i + 1];
            }
            mem[numPages-1] = index;
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

    std::vector<int> data;
    readFile(filename, &data);

    fifo(data, no_phys_pages, page_size);


    return 0;
}