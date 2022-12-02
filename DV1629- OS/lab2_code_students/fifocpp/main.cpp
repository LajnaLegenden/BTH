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

[[maybe_unused]] bool isInMemory(int value, std::vector<Page> &memory) {
    for (auto &pageIndex: memory) {
        if (pageIndex.has(value)) {
            return true;
        }
    }
    return false;
}

[[maybe_unused]] bool hasNone(int value, const std::vector<int> &data) {
    for (int i: data) {
        if (i == value) {
            return false;
        }
    }
    return true;
}

Page findPage(std::vector<Page> &disk, int &value, int pageIndex, int pageSize) {
    for (int i = 0; i < disk.size(); i++) {
        if (disk[i].startIndex == pageIndex) {
            Page toReturn = disk[i];
            disk.erase(disk.begin() + i);
        }
    }
    Page p = Page(pageSize);
    p.setIndexRange(pageIndex * pageSize);
    p.add(value);
    return p;

}

bool
placeItem(std::vector<Page> &memory, std::vector<Page> &disk, int &value, const int &numPages, const int &pageSize) {
    int pageIndex = value / pageSize;

    for (int memIndex = 0; memIndex < numPages; memIndex++) {
        if (memory[memIndex].startIndex == pageIndex || memory[memIndex].startIndex == -1) {
            if (memory[memIndex].startIndex == -1)
                memory[memIndex].setIndexRange(pageIndex * pageSize);
            memory[memIndex].add(value);
            return false;
        }
    }
    disk.push_back(memory[0]);
    //Shift pages to fill the gap
    for (int i = 0; i < numPages; i++) {
        memory[i] = memory[i + 1];
    }
    memory[numPages - 1] = findPage(disk, value, pageIndex, pageSize);

    return true;

}


void fifo(const std::vector<int> &data, const int &numPages, const int &pageSize) {
    int misses = 0, hits = 0, fullPages = 0;
    std::vector<Page> memory;
    std::vector<Page> disk;


    for (int i = 0; i < numPages; i++) {
        Page p = Page(pageSize);
        memory.push_back(p);
    }
    for (int addressIndex = 0; addressIndex < MAX; addressIndex++) {
        if (addressIndex % 10000 == 0) {
            printf("Progress %i/%i\n", addressIndex, MAX);
            fflush(stdout);
        }

        int currentItem = data[addressIndex];


        //Check if any pages in memory are free on in range

        if (placeItem(memory, disk, currentItem, numPages, pageSize)) {
            misses++;
        }







        /* if (fullPages < numPages) {
             if (memory[fullPages].add(currentItem)) {
                 fullPages++;
             }
         } else {
             misses++;
             int pageToOverwrite = 0;
             fullPages--;
             //Shift pages to fill the gap
             for (int i = pageToOverwrite; i == numPages - 1; i++) {
                 memory[i] = memory[i + 1];
             }
             Page p = Page(pageSize);
             p.add(currentItem);
             memory[fullPages] = p;
         }*/
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