//
// Created by lajna on 12/2/22.
//
#include <vector>

#ifndef OPTIMAL_PAGE_H
#define OPTIMAL_PAGE_H

class Page {
private:
    int maxSize;
    int id;
public:
    std::vector<int> data;
    int size;
    int startRange;
    int endRange;
    int startIndex;
    explicit Page(int size, int defaultValue = -1);
    bool has(int value) const;
    bool add(int value);
    void setIndexRange(int startIndex);
};

Page::Page(int size, int defaultValue) {
    this->size = 0;
    this->maxSize = size;
    this->startIndex = -1;
    this->startRange = -1;
    this->endRange = -1;
    this->id = rand()%1000;
    for (int i = 0; i < this->maxSize; i++) {
        this->data.push_back(defaultValue);
    }
}

bool Page::add(int value) {
    this->data[size++] = value;
    return size == this->maxSize;
}

bool Page::has(int value) const {
    for(int i = 0; i < this->size; i++){
        if(this->data[i] == value){
            return true;
        }
    }
    return false;
}

void Page::setIndexRange(int startRange) {
    this->startRange = startRange;
    this->endRange = startRange+ this->maxSize;
    this->startIndex = startRange / this->maxSize;
}


#endif //OPTIMAL_PAGE_H
