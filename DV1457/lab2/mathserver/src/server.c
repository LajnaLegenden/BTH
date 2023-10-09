#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <netinet/in.h> //structure for storing address information
#include <sys/socket.h> //for socket APIs
#include <errno.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
struct sharedMemoryStruct
{
    int pCount;
    pid_t pids[10];
};
#define SHMSIZE 128
#define SHM_R 0400
#define SHM_W 0200
#define RESPONSE_LIMIT 16384

volatile struct sharedMemoryStruct *sharedMemoryPointer = NULL;
int sharedMemoryId;

void getHelp(char *argv[])
{
    printf("Usage: %s [-h] [-p port]\n", argv[0]);
    printf("-h\tPrint help text\n");
    printf("-p\tListen to port number port\n");
}

// function to return substring takes string, pos, and length
char *getSubString(char *str, int pos, int length)
{
    char *subStr = malloc(sizeof(char) * (length + 1));
    int c = 0;

    while (c < length)
    {
        subStr[c] = str[pos + c];
        c++;
    }
    subStr[c] = '\0';
    return subStr;
}

void handle_sigint(int sig)
{
    printf("Caught signal %d\n", sig);
    // loop over all children and kill them
    for (int i = 0; i < sharedMemoryPointer->pCount; i++)
    {
        printf("Killing child %d\n", sharedMemoryPointer->pids[i]);
        kill(sharedMemoryPointer->pids[i], SIGKILL);
    }
    exit(0);
}

int main(int argc, char *argv[])
{

    signal(SIGINT, handle_sigint);

    int opt;
    int port; // Default port
    int portValid = 0;

    // get pwd
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("Current working dir: %s\n", cwd);
    // seed rgn
    srand(time(NULL));
    // create folder if not exists in pwd
    char *folderName = "computed_results";
    char *folderPath = malloc(sizeof(char) * (strlen(cwd) + strlen(folderName) + 2));
    strcpy(folderPath, cwd);
    strcat(folderPath, "/");
    strcat(folderPath, folderName);
    printf("Folder path: %s\n", folderPath);
    if (mkdir(folderPath, 0777) == -1)
    {
        printf("Folder already exists\n");
    }
    else
    {
        printf("Folder created\n");
    }

    while ((opt = getopt(argc, argv, "hp:")) != -1)
    {
        switch (opt)
        {
        case 'h':
            getHelp(argv);
            exit(EXIT_SUCCESS);
        case 'p':
            // if no port number is given, the default port number is 8080
            if (optarg == NULL)
            {
                fprintf(stderr, "Invalid port number\n");
                exit(EXIT_FAILURE);
            }

            port = atoi(optarg);
            if (port <= 0 || port > 65535)
            {
                fprintf(stderr, "Invalid port number\n");
                exit(EXIT_FAILURE);
            }
            portValid = 1;
            break;
        case '?':
            fprintf(stderr, "Usage: %s [-h] [-p port]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if (!portValid)
    {
        printf("Port number not specified\n");
        getHelp(argv);
        exit(EXIT_FAILURE);
    }
    // Your code to start the server with the specified options goes here
    printf("Port: %d\n", port);

    char *addr = NULL;
    sharedMemoryId = shmget(IPC_PRIVATE, SHMSIZE, IPC_CREAT | SHM_R | SHM_W);
    sharedMemoryPointer = (struct sharedMemoryStruct *)shmat(sharedMemoryId, addr, 0);

    int sd = socket(AF_INET, SOCK_STREAM, 0);

    // define server address
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
    servAddr.sin_addr.s_addr = INADDR_ANY;
    bind(sd, (struct sockaddr *)&servAddr, sizeof(servAddr)); // Bind socket to the specified IP and port
    int l = listen(sd, 1);
    printf("Listening on port %d\n", port);
    if (l == -1)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        int cd = accept(sd, NULL, NULL);

        // fork
        if (sharedMemoryPointer->pCount > 9)
        {
            printf("Maximum number of clients reached\n");
            continue;
        }
        pid_t pid = fork();
        sharedMemoryPointer->pids[sharedMemoryPointer->pCount++] = pid;

        // if child
        if (pid == 0)
        {
            printf("Client connected\n");
            while (1)
            {
                // receive data from client
                char strData[64];
                int nbytes = recv(cd, strData, sizeof(strData), 0);
                if (nbytes == -1)
                {
                    perror("recv");
                    exit(EXIT_FAILURE);
                }
                strData[nbytes] = '\0';

                // print received data
                if (nbytes > 0)
                {
                    printf("Received a message (%d bytes) from the client!\n\n", nbytes);
                    printf("----Message: %s\n", strData);
                    if (strncmp(strData, "exit", 4) == 0)
                    {
                        printf("Client has closed the connection\n");
                        close(cd);
                        break;
                    } // check if message starts with matinvpar
                    else if (strncmp(strData, "matinvpar", 9) == 0)
                    {
                        // generate 8 random letters
                        char *letters = "abcdefghijklmnopqrstuvwxyz";
                        char *randomLetters = (char *)malloc(sizeof(char) * 9); // Allocating space for 8 chars + 1 for '\0'
                        if (randomLetters == NULL)
                        {
                            perror("Failed to allocate memory for randomLetters");
                            exit(EXIT_FAILURE);
                        }

                        for (int i = 0; i < 8; i++)
                        {
                            randomLetters[i] = letters[rand() % 26];
                        }
                        randomLetters[8] = '\0'; // Null-terminate the string

                        printf("Client has requested matinvpar\n");
                        char command[128];
                        strcpy(command, "./matinv-par ");
                        strcat(command, getSubString(strData, 10, 128));
                        // output name
                        strcat(command, "> computed_results/");
                        strcat(command, randomLetters);
                        strcat(command, ".txt");
                        char buf[RESPONSE_LIMIT];
                        system(command);

                        // read file and send to client
                        char fileName[32];
                        strcpy(fileName, "computed_results/");
                        strcat(fileName, randomLetters);
                        strcat(fileName, ".txt");
                        printf("Opening file %s\n", fileName);

                        // read entire file to buffer
                        FILE *fp;
                        fp = fopen(fileName, "rb");
                        if (fp == NULL)
                        {
                            perror("Error while opening the file.\n");
                            exit(EXIT_FAILURE);
                        }
                        char *fileBuf = (char *)malloc(sizeof(char) * RESPONSE_LIMIT);
                        if (fileBuf == NULL)
                        {
                            perror("Failed to allocate memory for fileBuf");
                            exit(EXIT_FAILURE);
                        }

                        int i = 0;
                        char c;
                        while ((c = fgetc(fp)) != EOF && i < RESPONSE_LIMIT - 1) // Ensure not to overflow buffer
                        {
                            fileBuf[i++] = c;
                        }
                        fileBuf[i] = '\0';
                        fclose(fp);

                        printf("Sending file to client\n");

                        send(cd, fileBuf, RESPONSE_LIMIT, 0);

                        // Free allocated memory
                        free(randomLetters);
                        free(fileBuf);
                    }
                    else if (strncmp(strData, "kmeans", 7) == 0)
                    {
                        printf("Client has requested kmeans\n");
                        send(cd, "running kmeans", 15, 0);
                    }
                }
            }
            printf("Child process %d exiting\n", getpid());
            // remove pid from pids and shift all other pids
            for (int i = 0; i < sharedMemoryPointer->pCount; i++)
            {
                if (sharedMemoryPointer->pids[i] == getpid())
                {
                    printf("Removing pid %d\n", getpid());
                    for (int j = i; j < sharedMemoryPointer->pCount - 1; j++)
                    {
                        sharedMemoryPointer->pids[j] = sharedMemoryPointer->pids[j + 1];
                    }
                    sharedMemoryPointer->pCount--;
                    break;
                }
            }

            exit(0);
        }
    }

    return 0;
}