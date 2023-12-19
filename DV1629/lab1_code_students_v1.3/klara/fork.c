#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    unsigned i;
    unsigned niterations = 100;
    pid_t pid = fork();
    if (pid == 0)
    {
        for (i = 0; i < niterations; ++i)
            printf("A = %d, ", i);
    }
    else
    {
        printf("A child pid = %d\n", pid);
        pid = fork();
        if (pid == 0)
        {
            for (i = 0; i < niterations; ++i)
                printf("B = %d, ", i);
        }
        else
        {
            printf("B child pid = %d\n", pid);
            for (i = 0; i < niterations; ++i)
                printf("C = %d, ", i);
        }
    }
    printf("\n");
}
