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

int	N;		/* matrix size		*/
int	maxnum;		/* max number of element*/
char* Init;		/* matrix init type	*/
int	PRINT;		/* print switch		*/
matrix	A;		/* matrix A		*/
matrix I = {0.0};  /* The A inverse matrix, which will be initialized to the identity matrix */

/* forward declarations */
void find_inverse(void);
void Init_Matrix(void);
void Print_Matrix(matrix M, char name[]);
void Init_Default(void);
int Read_Options(int, char**);

int
main(int argc, char** argv)
{
    printf("Matrix Inverse\n");
    int i, timestart, timeend, iter;

    Init_Default();		/* Init default values	*/
    Read_Options(argc, argv);	/* Read arguments	*/
    Init_Matrix();		/* Init the matrix	*/
    find_inverse();

    if (PRINT == 1)
    {
        //Print_Matrix(A, "End: Input");
        Print_Matrix(I, "Inversed");
    }
}
#include <sys/shm.h>
#include <sys/wait.h>

void find_inverse()
{
    int row, col, p; 
    double pivalue; 
    //flush std
    fflush(stdout);
    fflush(stderr);
    // Create shared memory segments for matrices A and I
    int shmid_A = shmget(IPC_PRIVATE, sizeof(matrix), IPC_CREAT | 0666);
    int shmid_I = shmget(IPC_PRIVATE, sizeof(matrix), IPC_CREAT | 0666);
    matrix* shmA = (matrix*)shmat(shmid_A, NULL, 0);
    matrix* shmI = (matrix*)shmat(shmid_I, NULL, 0);

    // Copy data to shared memory
    memcpy(shmA, &A, sizeof(matrix));
    memcpy(shmI, &I, sizeof(matrix));

    for (p = 0; p < N; p++) { 
        pivalue = (*shmA)[p][p];
        for (col = 0; col < N; col++)
        {
            (*shmA)[p][col] = (*shmA)[p][col] / pivalue; 
            (*shmI)[p][col] = (*shmI)[p][col] / pivalue; 
        }
        assert((*shmA)[p][p] == 1.0);

        int num_processes = CORES; // Number of child processes to create
        for (int proc = 0; proc < num_processes; proc++) {
            pid_t pid = fork();
            if (pid == 0) { // Child process
                int start_row = (N / num_processes) * proc;
                int end_row = (proc == num_processes - 1) ? N : (N / num_processes) * (proc + 1);
                double multiplier;
                for (row = start_row; row < end_row; row++) {
                    if (row != p) 
                    {
                        multiplier = (*shmA)[row][p];
                        for (col = 0; col < N; col++)
                        {
                            (*shmA)[row][col] = (*shmA)[row][col] - (*shmA)[p][col] * multiplier; 
                            (*shmI)[row][col] = (*shmI)[row][col] - (*shmI)[p][col] * multiplier; 
                        }      
                        assert((*shmA)[row][p] == 0.0);
                    }
                }
                shmdt(shmA);
                shmdt(shmI);
                exit(0); // Child process ends
            }
        }

        // Parent waits for all child processes to finish
        for (int proc = 0; proc < num_processes; proc++) {
            wait(NULL);
        }
    }

    // Copy data back from shared memory
    memcpy(&A, shmA, sizeof(matrix));
    memcpy(&I, shmI, sizeof(matrix));

    // Detach and delete shared memory
    shmdt(shmA);
    shmdt(shmI);
    shmctl(shmid_A, IPC_RMID, NULL);
    shmctl(shmid_I, IPC_RMID, NULL);
}


void
Init_Matrix()
{
    int row, col;

    // Set the diagonal elements of the inverse matrix to 1.0
    // So that you get an identity matrix to begin with
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (row == col)
                I[row][col] = 1.0;
        }
    }

    printf("\nsize      = %dx%d ", N, N);
    printf("\nmaxnum    = %d \n", maxnum);
    printf("Init	  = %s \n", Init);
    printf("Initializing matrix...");

    if (strcmp(Init, "rand") == 0) {
        for (row = 0; row < N; row++) {
            for (col = 0; col < N; col++) {
                if (row == col) /* diagonal dominance */
                    A[row][col] = (double)(rand() % maxnum) + 5.0;
                else
                    A[row][col] = (double)(rand() % maxnum) + 1.0;
            }
        }
    }
    if (strcmp(Init, "fast") == 0) {
        for (row = 0; row < N; row++) {
            for (col = 0; col < N; col++) {
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

void
Print_Matrix(matrix M, char name[])
{
    int row, col;

    printf("%s Matrix:\n", name);
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++)
            printf(" %5.2f", M[row][col]);
        printf("\n");
    }
    printf("\n\n");
}

void
Init_Default()
{
    N = 5;
    Init = "fast";
    maxnum = 15.0;
    PRINT = 1;
}

int
Read_Options(int argc, char** argv)
{
    char* prog;

    prog = *argv;
    while (++argv, --argc > 0)
        if (**argv == '-')
            switch (*++ * argv) {
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