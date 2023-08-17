#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define NUM_PROFS 5
struct threadArgs
{
    unsigned int id;
    char name[10];
};
struct fork
{
    int id;
    int owner;
};
// array of names
char names[NUM_PROFS][10] = {"Betty", "Fredde", "Torre", "Tompa", "Henke"};
// array of forks
struct fork forks[NUM_PROFS];

void *professor(void *params)
{
    struct threadArgs *args = (struct threadArgs *)params;
    printf("[%s]: Good Morning my dear students\n", args->name);
    fflush(stdout);
    while (1)
    {
        // Let the professors think a random time between one and five seconds
        sleep(rand() % 5 + 1);
        while (forks[args->id].owner != -1)
        {
            printf("[%s]: Im tried taking the stick ID:[%i] but it was in use\n", args->name, args->id);
            usleep(2000 * 1000);
        }
        // take left stick
        printf("[%s]: Im taking my left stick ID:[%i]\n", args->name, args->id);
        forks[args->id].owner = args->id;
        // thinkg 2 -8
        sleep(rand() % 6 + 2);
        // take right stick
        int rightId = (args->id + 1) % NUM_PROFS;
        int tries = 0;
        while (forks[rightId].owner != -1)
        {
            tries++;
            if (tries == 10)
                break;
            printf("[%s]: Im tried taking the stick ID:[%i] but it was in use\n", args->name, args->id);
            usleep(2000 * 1000);
        }
        if (tries == 10)
        {
            printf("[%s]: Im putting down my chopsticks since i cannot have 2 ID:[%i]\n", args->name, args->id);
            forks[args->id].owner = -1;
        }
        else
        {

            printf("[%s]: Im taking my right stick ID:[%i]\n", args->name, rightId);
            forks[rightId].owner = args->id;
            // eat
            printf("[%s]: Im eating\n", args->name);

            sleep(rand() % 5 + 5);
            printf("[%s]: Im putting down my chopsticks ID:[%i,%i]\n", args->name, args->id, rightId);
            forks[args->id].owner = -1;
            forks[rightId].owner = -1;
        }
    }
    free(args);
}
int main(int argc, char **argv)
{
    pthread_t *children;     // dynamic array of child threads
    struct threadArgs *args; // argument buffer
    unsigned int numThreads = NUM_PROFS;
    srand(time(NULL));
    // create forks
    for (int i = 0; i < NUM_PROFS; i++)
    {
        forks[i].id = i;
        forks[i].owner = -1;
    }

    children = malloc(numThreads * sizeof(pthread_t)); // allocate array of handles
    for (unsigned int id = 0; id < numThreads; id++)
    {
        // create threads
        args = malloc(sizeof(struct threadArgs));
        args->id = id;
        // Clear name
        memset(args->name, 0, 10 * (sizeof args->name[0]));
        strcpy(args->name, names[id]);
        pthread_create(&(children[id]), // our handle for the child
                       NULL,            // attributes of the child
                       professor,       // the function it should run
                       (void *)args);   // args to that function
    }
    printf("I am the parent (main) thread.\n");
    for (unsigned int id = 0; id < numThreads; id++)
    {
        pthread_join(children[id], NULL);
    }
    free(children); // deallocate array
    return 0;
}
