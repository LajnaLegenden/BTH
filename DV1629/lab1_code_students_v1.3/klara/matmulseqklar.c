/***************************************************************************
 *
 * Sequential version of Matrix-Matrix multiplication
 *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 1024
#define CPUS 4

static double a[SIZE][SIZE];
static double b[SIZE][SIZE];
static double c[SIZE][SIZE];
struct threadArgs
{
    unsigned int id;
    unsigned int numRows;
};

void *multi(void *arg)
{
    struct threadArgs *args = (struct threadArgs *)arg;
    printf("id: %d, numRows: %d\n", args->id, args->numRows);

    int thread_id = args->id;
    for (int row = thread_id * args->numRows; row < (thread_id + 1) * args->numRows; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            c[row][col] = 0.0;
            for (int k = 0; k < SIZE; k++)
            {
                c[row][col] += a[row][k] * b[k][col];
            }
        }
    }
}
void *generator(void *params)
{
    struct threadArgs *args = (struct threadArgs *)params;

     for (int row = args->id * args->numRows; row < (args->id + 1) * args->numRows; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            a[row][col] = 1.0;
            b[row][col] = 1.0;
        }
    }
}

static void
init_matrix(void)
{
    int perThread = SIZE / CPUS;
    pthread_t *children;                         // dynamic array of child threads
    struct threadArgs *args;                     // argument buffer
    children = malloc(SIZE * sizeof(pthread_t)); // allocate array of handles

    for (unsigned int id = 0; id < CPUS; id++)
    {
        // create threads
        args = malloc(sizeof(struct threadArgs));
        args->id = id;
        args->numRows = perThread;
        pthread_create(&(children[id]), // our handle for the child
                       NULL,            // attributes of the child
                       generator,       // the function it should run
                       (void *)args);   // args to that function
    }
    for (unsigned int id = 0; id < CPUS; id++)
    {
        pthread_join(children[id], NULL);
    }
}



void *worker(void *params)
{
    struct threadArgs *args = (struct threadArgs *)params;

    int i, j, k;
    i = args->id;
    for (i = args->numRows * args->id; i < args->numRows * args->id + args->numRows; i++)
        for (j = 0; j < SIZE; j++)
        {
            c[i][j] = 0.0;
            for (k = 0; k < SIZE; k++)
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
        }
}

static void matmul_seq()
{
    pthread_t *children;                         // dynamic array of child threads
    struct threadArgs *args;                     // argument buffer
    children = malloc(CPUS * sizeof(pthread_t)); // allocate array of handles

    for (unsigned int id = 0; id < CPUS; id++)
    {
        // create threads
        args = malloc(sizeof(struct threadArgs));
        args->id = id;
        args->numRows = SIZE / CPUS;
        pthread_create(&(children[id]), // our handle for the child
                       NULL,            // attributes of the child
                       multi,          // the function it should run
                       (void *)args);   // args to that function
    }
    for (unsigned int id = 0; id < CPUS; id++)
    {
        pthread_join(children[id], NULL);
    }
}

static void
print_matrix(void)
{
    int i, j;

    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
            printf(" %7.2f", c[i][j]);
        printf("\n");
    }
}

int main(int argc, char **argv)
{
    init_matrix();
    matmul_seq();
    //print_matrix();
}
