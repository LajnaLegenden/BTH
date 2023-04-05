/***************************************************************************
 *
 * Sequential version of Matrix-Matrix multiplication
 *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 1024

static double a[SIZE][SIZE];
static double b[SIZE][SIZE];
static double c[SIZE][SIZE];

static void init_matrix(void)
{
    int i, j;

    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
        {
            /* Simple initialization, which enables us to easy check
             * the correct answer. Each element in c will have the same
             * value as SIZE after the matmul operation.
             */
            a[i][j] = 1.0;
            b[i][j] = 1.0;
        }
}
void *multi_init_matrix(void *arg)
{
    int row = (int)arg;

    for (int j = 0; j < SIZE; j++)
    {
        /* Simple initialization, which enables us to easy check
         * the correct answer. Each element in c will have the same
         * value as SIZE after the matmul operation.
         */
        a[row][j] = 1.0;
        b[row][j] = 1.0;
    }
}


void *generator(void *params)
{
    struct threadArgs *args = (struct threadArgs *)params;

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
        {
            /* Simple initialization, which enables us to easy check
             * the correct answer. Each element in c will have the same
             * value as SIZE after the matmul operation.
             */
            if (args->id == 0)
                a[i][j] = 1.0;
            else
                b[i][j] = 1.0;
        }
}
static void matmul_seq()
{
    int i, j, k;

    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            c[i][j] = 0.0;
            for (k = 0; k < SIZE; k++)
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
        }
    }
}

void *multi(void *arg)
{
    int thread_id = (int)arg;
    int row = thread_id;
    for (int col = 0; col < SIZE; col++)
    {
        c[row][col] = 0.0;
        for (int k = 0; k < SIZE; k++)
        {
            c[row][col] += a[row][k] * b[k][col];
        }
    }
}

static void print_matrix(void)
{
    int i, j;

    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            printf(" %7.2f", c[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char **argv)
{
    pthread_t threads_0[SIZE];

    // one thread for each row
    for (int i = 0; i < SIZE; i++)
    {
        pthread_create(&threads_0[i], NULL, multi_init_matrix, (void *)(i));
    }

    // joining and waiting for all threads to complete
    for (int i = 0; i < SIZE; i++)
    {
        pthread_join(threads_0[i], NULL);
    }

    pthread_t threads[SIZE]; // i have 2 cores, 2 threads per core
    // this still only runs on one core though?

    // "one thread for each thread"
    for (int i = 0; i < SIZE; i++)
    {
        pthread_create(&threads[i], NULL, multi, (void *)(i));
    }

    // joining and waiting for all threads to complete
    for (int i = 0; i < SIZE; i++)
    {
        pthread_join(threads[i], NULL);
    }
    print_matrix();
}
