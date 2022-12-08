#include "BST.h"

int main() {
    int lowestH = 100000;
#pragma omp parallel for
    for (int j = 0; j < 1; j++) {
        BST<int> bst;


        int i = 1000;
        srand(time(NULL));

        //add i random numbers to the tree
        while (i--) {}
        // std::cout << bst.ToGraphviz();

        int h = bst.height();
        if (h < lowestH)
            lowestH = h;
    }
    std::cout << lowestH;
    return 0;
}