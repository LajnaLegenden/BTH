#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

    int numbers[10000];
    FILE *file;
    int i = 0;

    if (file = fopen("mp3d.mem", "r")) {
        while (fscanf(file, "%d", &numbers[i]) != EOF) {
            i++;
        }
        fclose(file);
    }
    numbers[i] = '\0';

    for (i = 0; numbers[i] != '\0'; i++)
    {
        printf("%d\n", numbers[i]);
    }

    return 0;
}