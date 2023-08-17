#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h>   /* For O_* constants */
#include <stdbool.h> // Header-file for boolean data-type.
#include <unistd.h>
#include <pthread.h>

#define SHMSIZE 128
#define SHM_R 0400
#define SHM_W 0200

#define NUM_ITEMS 10
#define LIMIT 100

const char *semName1 = "read";
const char *semName2 = "write";

struct sharedMemoryStruct
{
    int buffer[NUM_ITEMS];
};

// takes in index, sharedMemoryPointer
int _read(int index, volatile struct sharedMemoryStruct *sharedMemoryPointer, pid_t processId)
{
    printf("[PID:%d]Receiving %d\n", processId, sharedMemoryPointer->buffer[index]);
    fflush(stdout);
    // sharedMemoryPointer->empty[index] = true;
    usleep((rand() % 19 + 2) * 100 * 1000);
    return sharedMemoryPointer->buffer[index];
}

// write function takes in index, sharedMemoryPointer, and value
void _write(int index, volatile struct sharedMemoryStruct *sharedMemoryPointer, int value, pid_t processId)
{
    printf("[PID:%d]Sending %d\n", processId, value);
    fflush(stdout);
    sharedMemoryPointer->buffer[index] = value;
    usleep((rand() % 4 + 1) * 100 * 1000);
}

int main(int argc, char **argv)
{
    // cleanup
    sem_unlink(semName1);
    sem_unlink(semName2);

    sem_t *sem_read = sem_open(semName1, O_CREAT, O_RDWR, 0);
    sem_t *sem_write = sem_open(semName2, O_CREAT, O_RDWR, 0);
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
        sem_post(sem_write);
    }

    processId = fork();
    if (processId != 0)
    {
        int counter = 0;
        while (true)
        {
            // Send ints to trough the shared memory buffer to the child syncing with semaphores
            sem_wait(sem_write);
            _write(parrentIndex, sharedMemoryPointer, counter, processId);
            sem_post(sem_read);
            parrentIndex = (parrentIndex + 1) % NUM_ITEMS;
            counter++;
            if (counter == LIMIT)
            {
                break;
            }
        }
    }
    else
    {
        /* here's the child, acting as consumer */
        while (true)
        {
            // recive its trough buffer of NUM_ITEMS syncing using semaphores

            sem_wait(sem_read);
            _read(childIndex, sharedMemoryPointer, processId);
            childCounter++;
            childIndex = (childIndex + 1) % NUM_ITEMS;
            sem_post(sem_write);
            if (childCounter == LIMIT)
            {
                break;
            }
        }
    }
}
