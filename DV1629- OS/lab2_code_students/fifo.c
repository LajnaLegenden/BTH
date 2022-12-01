#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

    if (argc != 4) {
        printf("Usage: no_phys_pages page_size filename");
        return -1;
    }
    //Load file into int array
    int no_phys_pages = atoi(argv[1]);
    int page_size = atoi(argv[2]);
    char *filename = argv[3];
    long *file;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file");
        return -1;
    }
    int counter = 0;
    char line;
    while ((line = fgetc(fp)) != EOF)
        file[counter++] =line;

    fclose(fp);


    return 0;
}