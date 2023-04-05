#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PROFESSORS 5
#define THINKING_TIME_RANGE 5
#define EATING_TIME_RANGE 5

// One stick per professor
sem_t chopsticks[NUM_PROFESSORS];
// Solve deadlock by limiting the number of professors that can eat at the same time
sem_t max_professors;
const char *professor_names[] = {"Betty", "Fredde", "Torre", "Tompa", "Henke"};

void *professor(void *arg)
{
    int id = *((int *)arg);
    free(arg);

    while (1)
    {
        // think
        int thinking_time = rand() % THINKING_TIME_RANGE + 1;
        printf("%s: thinking for %d seconds\n", professor_names[id], thinking_time);
        sleep(thinking_time);
        
        // wait for a free chopstick
        sem_wait(&max_professors); 
        
        // pick up left chopstick
        printf("%s: trying to pick up left chopstick\n", professor_names[id]);
        sem_wait(&chopsticks[id]);
        printf("%s: picked up left chopstick\n", professor_names[id]);
        sleep(rand() % 7 + 2);

        // pick up right chopstick
        printf("%s: trying to pick up right chopstick\n", professor_names[id]);
        sem_wait(&chopsticks[id + 1 % NUM_PROFESSORS]);
        printf("%s: picked up right chopstick\n", professor_names[id]);

        sem_post(&max_professors);
        // eat
        int eating_time = rand() % EATING_TIME_RANGE + 5;
        printf("%s: eating for %d seconds\n", professor_names[id], eating_time);
        sleep(eating_time);

        // put down chopsticks
        sem_post(&chopsticks[id]);
        sem_post(&chopsticks[id + 1 % NUM_PROFESSORS]);
        printf("%s: put down all my chopstick\n", professor_names[id]);
    }
}

int main()
{
    srand(time(NULL));

    for (int i = 0; i < NUM_PROFESSORS; ++i)
    {
        sem_init(&chopsticks[i], 0, 1);
    }
    sem_init(&max_professors, 0, NUM_PROFESSORS - 1);

    pthread_t threads[NUM_PROFESSORS];
    for (int i = 0; i < NUM_PROFESSORS; ++i)
    {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&threads[i], NULL, professor, id);
    }

    for (int i = 0; i < NUM_PROFESSORS; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < NUM_PROFESSORS; ++i)
    {
        sem_destroy(&chopsticks[i]);
    }
    sem_destroy(&max_professors);

    return 0;
}