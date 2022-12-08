#include "frame.h"

Frame::Frame(int* _data,int start, int end){
    int counter= 0;
    for(int i = start;  i< end; i++){
        this->data[counter++] = file[i];
    }
}