//
// Created by lajna on 12/2/22.
//
#include <vector>

#ifndef OPTIMAL_PAGE_H
#define OPTIMAL_PAGE_H

class Page {
private:
    int maxSize;
public:
    std::vector<int> data;
    int size;

    explicit Page(int size, int defaultValue = -1);
    bool has(int value) const;
    bool add(int value);
};

Page::Page(int size, int defaultValue) {
    this->size = 0;
    this->maxSize = size;
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


#endif //OPTIMAL_PAGE_H
