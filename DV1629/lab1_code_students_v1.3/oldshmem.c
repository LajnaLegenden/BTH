#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <stdbool.h> // Header-file for boolean data-type.
#define SHMSIZE 128
#define SHM_R 0400
#define SHM_W 0200

#define NUM_ITEMS 10
#define LIMIT 100

struct sharedMemoryStruct
{
    int buffer[NUM_ITEMS];
    bool empty[NUM_ITEMS];
};

// takes in index, sharedMemoryPointer
int read(int index, volatile struct sharedMemoryStruct *sharedMemoryPointer, pid_t processId)
{
    printf("[PID:%d]Receiving %d\n", processId, sharedMemoryPointer->buffer[index]);
    fflush(stdout);
    sharedMemoryPointer->empty[index] = true;
    usleep((rand() % 19 + 2) * 100 * 1000);
    return sharedMemoryPointer->buffer[index];
}

// write function takes in index, sharedMemoryPointer, and value
void write(int index, volatile struct sharedMemoryStruct *sharedMemoryPointer, int value, pid_t processId)
{
    printf("[PID:%d]Sending %d\n", processId, value);
    fflush(stdout);
    sharedMemoryPointer->buffer[index] = value;
    sharedMemoryPointer->empty[index] = false;
    usleep((rand() % 4 + 1) * 100 * 1000);
}

int main(int argc, char **argv)
{

    volatile struct sharedMemoryStruct *sharedMemoryPointer = NULL;
    char *addr = NULL;
    pid_t processId = -1;
    int parrentCouter = 0, childCounter = 0, sharedMemoryId = -1, childIndex = 0, parrentIndex = 0;
    struct shmid_ds *shm_buf;

    // seed random
    srand(time(NULL));
    /* allocate a chunk of shared memory */
    sharedMemoryId = shmget(IPC_PRIVATE, SHMSIZE, IPC_CREAT | SHM_R | SHM_W);
    sharedMemoryPointer = (struct sharedMemoryStruct *)shmat(sharedMemoryId, addr, 0);

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        sharedMemoryPointer->empty[i] = true;
    }

    processId = fork();
    if (processId != 0)
    {
        int counter = 0;
        while (true)
        {
            // while any of the empty is false
            for (int i = 0; i < NUM_ITEMS; i++)
            {
                if (sharedMemoryPointer->empty[i] == true)
                {
                    write(i, sharedMemoryPointer, counter, processId);
                    if (counter == LIMIT)
                    {
                        shmdt(addr);
                        shmctl(sharedMemoryId, IPC_RMID, shm_buf);
                        exit(0);
                    }
                    counter++;
                }
            };
        }
    }
    else
    {
        /* here's the child, acting as consumer */
        while (true)
        {
            // while any of the empty is false
            for (int i = 0; i < NUM_ITEMS; i++)
            {
                if (sharedMemoryPointer->empty[i] == false)
                {
                    int res = read(i, sharedMemoryPointer, processId);
                    if (res == LIMIT)
                    {
                        shmdt(addr);
                        shmctl(sharedMemoryId, IPC_RMID, shm_buf);
                        exit(0);
                    }
                }
            };
        }
    }
}
