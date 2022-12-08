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
    int index;

    explicit Page(int size, int defaultValue = -1);

    ~Page();

    bool has(int value) const;

    void operator=(const Page &C);

    bool add(int value);

    Page *setIndex(int index);
};

Page::Page(int size, int defaultValue) {
    this->size = 0;
    this->maxSize = size;
    this->index = -1;
    this->startRange = -1;
    this->endRange = -1;
    this->id = rand() % 1000;
    for (int i = 0; i < this->maxSize; i++) {
        this->data.push_back(defaultValue);
    }
}

bool Page::add(int value) {
    this->data[size++] = value;
    return size == this->maxSize;
}

bool Page::has(int value) const {
    for (int i = 0; i < this->size; i++) {
        if (this->data[i] == value) {
            return true;
        }
    }
    return false;
}

Page *Page::setIndex(int index) {
    this->startRange = index * maxSize;
    this->endRange = startRange + this->maxSize;
    this->index = index;
    return this;
}

Page::~Page() {
    std::destroy(this->data.begin(), this->data.end());
}

void Page::operator=(const Page &from) {
    this->data = from.data;
    this->size = from.size;
    this->maxSize = from.maxSize;
    this->index = from.index;
    this->startRange = from.startRange;
    this->endRange = from.endRange;
}


#endif //OPTIMAL_PAGE_H
