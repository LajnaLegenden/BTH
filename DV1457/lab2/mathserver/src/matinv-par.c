/***************************************************************************
 *
 * Sequential version of Matrix Inverse
 * An adapted version of the code by Håkan Grahn
 ***************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 4096
#define CORES 8
typedef double matrix[MAX_SIZE][MAX_SIZE];

int N;            /* matrix size		*/
int maxnum;       /* max number of element*/
char *Init;       /* matrix init type	*/
int PRINT;        /* print switch		*/
matrix A;         /* matrix A		*/
matrix I = {0.0}; /* The A inverse matrix, which will be initialized to the identity matrix */
#include <pthread.h>

typedef struct
{
    int start_row;
    int end_row;
    int p;
    matrix *A;
    matrix *I;
} ThreadData;

/* forward declarations */
void find_inverse(void);
void Init_Matrix(void);
void Print_Matrix(matrix M, char name[]);
void Init_Default(void);
int Read_Options(int, char **);

int main(int argc, char **argv)
{
    printf("Matrix Inverse\n");
    int i, timestart, timeend, iter;

    Init_Default();           /* Init default values	*/
    Read_Options(argc, argv); /* Read arguments	*/
    Init_Matrix();            /* Init the matrix	*/
    find_inverse();

    if (PRINT == 1)
    {
        // Print_Matrix(A, "End: Input");
        Print_Matrix(I, "Inversed");
    }
}
#include <sys/shm.h>
#include <sys/wait.h>
typedef struct
{
    int start_row;
    int end_row;
    int pivot;
} thread_arg;

void *thread_function(void *void_arg)
{
    thread_arg *arg = (thread_arg *)void_arg;
    int start_row = arg->start_row;
    int end_row = arg->end_row;
    int pivot = arg->pivot;
    int col;

    double multiplier;
    for (int row = start_row; row < end_row; row++)
    {
        if (row != pivot)
        {
            multiplier = A[row][pivot];
            for (col = 0; col < N; col++)
            {
                A[row][col] -= A[pivot][col] * multiplier;
                I[row][col] -= I[pivot][col] * multiplier;
            }
            assert(A[row][pivot] == 0.0);
        }
    }
    return NULL;
}

void find_inverse()
{
    int row, col, p;
    double pivalue;
    const int num_threads = 4; // For example, using 4 threads
    pthread_t threads[num_threads];
    thread_arg args[num_threads];

    for (p = 0; p < N; p++)
    {
        pivalue = A[p][p];
        for (col = 0; col < N; col++)
        {
            A[p][col] /= pivalue;
            I[p][col] /= pivalue;
        }
        assert(A[p][p] == 1.0);

        int rows_per_thread = N / num_threads;
        for (int i = 0; i < num_threads; i++)
        {
            args[i].start_row = i * rows_per_thread;
            args[i].end_row = (i == num_threads - 1) ? N : (i + 1) * rows_per_thread;
            args[i].pivot = p;
            pthread_create(&threads[i], NULL, thread_function, &args[i]);
        }

        for (int i = 0; i < num_threads; i++)
        {
            pthread_join(threads[i], NULL);
        }
    }
}

void Init_Matrix()
{
    int row, col;

    // Set the diagonal elements of the inverse matrix to 1.0
    // So that you get an identity matrix to begin with
    for (row = 0; row < N; row++)
    {
        for (col = 0; col < N; col++)
        {
            if (row == col)
                I[row][col] = 1.0;
        }
    }

    printf("\nsize      = %dx%d ", N, N);
    printf("\nmaxnum    = %d \n", maxnum);
    printf("Init	  = %s \n", Init);
    printf("Initializing matrix...");

    if (strcmp(Init, "rand") == 0)
    {
        for (row = 0; row < N; row++)
        {
            for (col = 0; col < N; col++)
            {
                if (row == col) /* diagonal dominance */
                    A[row][col] = (double)(rand() % maxnum) + 5.0;
                else
                    A[row][col] = (double)(rand() % maxnum) + 1.0;
            }
        }
    }
    if (strcmp(Init, "fast") == 0)
    {
        for (row = 0; row < N; row++)
        {
            for (col = 0; col < N; col++)
            {
                if (row == col) /* diagonal dominance */
                    A[row][col] = 5.0;
                else
                    A[row][col] = 2.0;
            }
        }
    }

    printf("done \n\n");
    if (PRINT == 1)
    {
        Print_Matrix(A, "Begin: Input");
        Print_Matrix(I, "Begin: Inverse");
    }
}

void Print_Matrix(matrix M, char name[])
{
    int row, col;

    printf("%s Matrix:\n", name);
    for (row = 0; row < N; row++)
    {
        for (col = 0; col < N; col++)
            printf(" %5.2f", M[row][col]);
        printf("\n");
    }
    printf("\n\n");
}

void Init_Default()
{
    N = 5;
    Init = "fast";
    maxnum = 15.0;
    PRINT = 1;
}

int Read_Options(int argc, char **argv)
{
    char *prog;

    prog = *argv;
    while (++argv, --argc > 0)
        if (**argv == '-')
            switch (*++*argv)
            {
            case 'n':
                --argc;
                N = atoi(*++argv);
                break;
            case 'h':
                printf("\nHELP: try matinv -u \n\n");
                exit(0);
                break;
            case 'u':
                printf("\nUsage: matinv [-n problemsize]\n");
                printf("           [-D] show default values \n");
                printf("           [-h] help \n");
                printf("           [-I init_type] fast/rand \n");
                printf("           [-m maxnum] max random no \n");
                printf("           [-P print_switch] 0/1 \n");
                exit(0);
                break;
            case 'D':
                printf("\nDefault:  n         = %d ", N);
                printf("\n          Init      = rand");
                printf("\n          maxnum    = 5 ");
                printf("\n          P         = 0 \n\n");
                exit(0);
                break;
            case 'I':
                --argc;
                Init = *++argv;
                break;
            case 'm':
                --argc;
                maxnum = atoi(*++argv);
                break;
            case 'P':
                --argc;
                PRINT = atoi(*++argv);
                break;
            default:
                printf("%s: ignored option: -%s\n", prog, *argv);
                printf("HELP: try %s -u \n\n", prog);
                break;
            }
}