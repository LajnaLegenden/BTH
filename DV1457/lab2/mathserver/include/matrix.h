#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/wait.h>


#define THREADS 4
#define MAX_SIZE 4096
typedef double matrix[MAX_SIZE][MAX_SIZE];

struct MatrixSolver
{
    
}

extern const struct MatrixSolver {
			struct MatrixSolver (*new)(double real, double imag);
		} MatrixSolver;