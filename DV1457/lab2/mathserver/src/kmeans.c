#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#define MAX_POINTS 4096
#define PATH_MAX 1024
#define MAX_CLUSTERS 32
#define CORES 8
#define SHMSIZE 128
#define SHM_R 0400
#define SHM_W 0200
typedef struct point
{
    float x;     // The x-coordinate of the point
    float y;     // The y-coordinate of the point
    int cluster; // The cluster that the point belongs to
} point;

struct sharedMemoryStruct
{
    bool someChange[CORES];
};

volatile struct sharedMemoryStruct *sharedMemoryPointer = NULL;
int sharedMemoryId;
int N;                       // number of entries in the data
int k;                       // number of centroids
point data[MAX_POINTS];      // Data coordinates
point cluster[MAX_CLUSTERS]; // The coordinates of each cluster center (also called centroid)

void read_data()
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    char *folderName = "mathserver/objects/kmeans-data.txt";
    char *folderPath = malloc(sizeof(char) * (strlen(cwd) + strlen(folderName) + 2));
    strcpy(folderPath, cwd);
    strcat(folderPath, "/");
    strcat(folderPath, folderName);
    N = 1797;
    k = 9;
    FILE *fp = fopen(folderPath, "r");
    if (fp == NULL)
    {
        perror("Cannot open the file");
        exit(EXIT_FAILURE);
    }

    // Initialize points from the data file
    float temp;
    for (int i = 0; i < N; i++)
    {
        fscanf(fp, "%f %f", &data[i].x, &data[i].y);
        data[i].cluster = -1; // Initialize the cluster number to -1
    }
    printf("Read the problem data!\n");
    // Initialize centroids randomly
    srand(0); // Setting 0 as the random number generation seed
    for (int i = 0; i < k; i++)
    {
        int r = rand() % N;
        cluster[i].x = data[r].x;
        cluster[i].y = data[r].y;
    }
    fclose(fp);
}

int get_closest_centroid(int i, int k)
{
    /* find the nearest centroid */
    int nearest_cluster = -1;
    double xdist, ydist, dist, min_dist;
    min_dist = dist = INT_MAX;
    for (int c = 0; c < k; c++)
    { // For each centroid
        // Calculate the square of the Euclidean distance between that centroid and the point
        xdist = data[i].x - cluster[c].x;
        ydist = data[i].y - cluster[c].y;
        dist = xdist * xdist + ydist * ydist; // The square of Euclidean distance
        // printf("%.2lf \n", dist);
        if (dist <= min_dist)
        {
            min_dist = dist;
            nearest_cluster = c;
        }
    }
    // printf("-----------\n");
    return nearest_cluster;
}

bool assign_clusters_to_points()
{
    printf("assign_clusters_to_points\n");
    int old_cluster = -1, new_cluster = -1;

    // how much of n in each core
    int n_per_core = N / CORES;
    int start = 0;
    printf("n_per_core = %d\n", n_per_core);
    // set all someChange to false
    // Initialize shared memory pointer
    sharedMemoryPointer = (sharedMemoryStruct *)shmat(sharedMemoryId, NULL, 0);
    if (sharedMemoryPointer == (void *)-1)
    {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < CORES; i++)
    {
        printf("set all someChange to false %i\n", i);
        sharedMemoryPointer->someChange[i] = false;
    }
    printf("set all someChange to false\n");

    for (int i = 0; i < CORES; i++)
    {
        printf("forking %d\n", i);
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            printf("child process %d\n", i);
            // child process
            int end = start + n_per_core;
            if (i == CORES - 1)
            {
                end = N;
            }
            for (int j = start; j < end; j++)
            {
                old_cluster = data[j].cluster;
                new_cluster = get_closest_centroid(j, k);
                data[j].cluster = new_cluster; // Assign a cluster to the point j
                if (old_cluster != new_cluster)
                {
                    sharedMemoryPointer->someChange[i] = true;
                }
            }
            exit(EXIT_SUCCESS);
        }
        else
        {
            // parent process
            start += n_per_core;
        }
    }
    // handle something changed
    // implement shm

    // wait for all child processes to finish
    int status;
    for (int i = 0; i < CORES; i++)
    {
        wait(&status);
    }
    // if any of the cores changed something, return true
    for (int i = 0; i < CORES; i++)
    {
        if (sharedMemoryPointer->someChange[i] == true)
        {
            return true;
        }
    }
    return false;
}

void update_cluster_centers()
{
    /* Update the cluster centers */
    int c;
    int count[MAX_CLUSTERS] = {0}; // Array to keep track of the number of points in each cluster
    point temp[MAX_CLUSTERS] = {0.0};

    for (int i = 0; i < N; i++)
    {
        c = data[i].cluster;
        count[c]++;
        temp[c].x += data[i].x;
        temp[c].y += data[i].y;
    }
    for (int i = 0; i < k; i++)
    {
        cluster[i].x = temp[i].x / count[i];
        cluster[i].y = temp[i].y / count[i];
    }
}

int kmeans(int k)
{
    char *addr = NULL;
    sharedMemoryId = shmget(IPC_PRIVATE, SHMSIZE, IPC_CREAT | SHM_R | SHM_W);
    sharedMemoryPointer = (struct sharedMemoryStruct *)shmat(sharedMemoryId, addr, 0);


    bool somechange;
    int iter = 0;
    do
    {
        printf("Iteration no. %d\n", iter);
        iter++; // Keep track of number of iterations
        somechange = assign_clusters_to_points();
        printf("somechange = %d\n", somechange);
        update_cluster_centers();
    } while (somechange);
    printf("Number of iterations taken = %d\n", iter);
    printf("Computed cluster numbers successfully!\n");
}

void write_results()
{
    FILE *fp = fopen("kmeans-results.txt", "w");
    if (fp == NULL)
    {
        perror("Cannot open the file");
        exit(EXIT_FAILURE);
    }
    else
    {
        for (int i = 0; i < N; i++)
        {
            fprintf(fp, "%.2f %.2f %d\n", data[i].x, data[i].y, data[i].cluster);
        }
    }
    printf("Wrote the results to a file!\n");
}

int main()
{
    read_data();
    kmeans(k);
    write_results();
}