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

// return substring
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

char **split_string_on_spaces(const char *str, int *count)
{
    int i, j, start;
    *count = 0;

    // count the number of words
    for (i = 0; str[i]; i++)
    {
        if (str[i] != ' ' && (i == 0 || str[i - 1] == ' '))
        {
            (*count)++;
        }
    }

    // allocate memory for the result
    char **result = (char **)malloc((*count) * sizeof(char *));
    if (!result)
    {
        return NULL; // Memory allocation failed
    }

    j = 0;
    for (i = 0; str[i];)
    {
        if (str[i] != ' ')
        {
            start = i;
            while (str[i] && str[i] != ' ')
                i++;

            result[j] = (char *)malloc(i - start + 1);
            if (!result[j])
            {
                // Memory allocation failed, free previously allocated memory
                for (--j; j >= 0; j--)
                {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }

            strncpy(result[j], str + start, i - start);
            result[j][i - start] = '\0'; // Null-terminate the string
            j++;
        }
        else
        {
            i++;
        }
    }

    return result;
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
    char *folderName1 = "computed_results";
    char *folderPath1 = malloc(sizeof(char) * (strlen(cwd) + strlen(folderName1) + 2));
    strcpy(folderPath1, cwd);
    strcat(folderPath1, "/");
    strcat(folderPath1, folderName1);
    printf("Folder path: %s\n", folderPath1);
    if (mkdir(folderPath1, 0777) == -1)
    {
        printf("Folder already exists\n");
    }
    else
    {
        printf("Folder created\n");
    }

    char *folderName2 = "working_files";
    char *folderPath2 = malloc(sizeof(char) * (strlen(cwd) + strlen(folderName2) + 2));
    strcpy(folderPath2, cwd);
    strcat(folderPath2, "/");
    strcat(folderPath2, folderName2);
    printf("Folder path: %s\n", folderPath2);
    if (mkdir(folderPath2, 0777) == -1)
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
                char strData[32];
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
                        strcpy(command, "./mathserver/matinv-par ");
                        strcat(command, getSubString(strData, 10, 128));
                        // output name
                        strcat(command, "> computed_results/");
                        strcat(command, randomLetters);
                        strcat(command, ".txt");
                        char buf[RESPONSE_LIMIT];
                        printf("Running command: %s\n", command);
                        system(command);

                        printf("Sleeping for 1 second\n");
                        sleep(1);

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

                        // print fileBuf
                        printf("Sending 326");
                        send(cd, fileBuf, 4096, 0);

                        // Free allocated memory
                        free(randomLetters);
                        free(fileBuf);
                    }
                    else if (strncmp(strData, "kmeans", 6) == 0)
                    {
                        // This section of code handles the kmeans request from the client
                        printf("Client has requested kmeans\n");

                        // Send the client an "INPUT" message
                        printf("Sending 339");
                        send(cd, "INPUT", 6, 0);

                        // Allocate memory for 8 random letters
                        char *letters = "abcdefghijklmnopqrstuvwxyz";
                        char *randomLetters = (char *)malloc(sizeof(char) * 9);
                        if (randomLetters == NULL)
                        {
                            perror("Failed to allocate memory for randomLetters");
                            exit(EXIT_FAILURE);
                        }

                        // Generate 8 random letters
                        for (int i = 0; i < 8; i++)
                        {
                            randomLetters[i] = letters[rand() % 26];
                        }
                        randomLetters[8] = '\0'; // Null-terminate the string

                        // Receive file from client
                        char fileBuf[RESPONSE_LIMIT];
                        int nbytes = recv(cd, fileBuf, sizeof(fileBuf), 0);
                        if (nbytes == -1)
                        {
                            perror("recv");
                            exit(EXIT_FAILURE);
                        }
                        fileBuf[nbytes] = '\0';
                        printf("File received from client\n");

                        // Write file to disk
                        printf("Writing file to disk\n");
                        FILE *fp;
                        char workingFileName[64];

                        // Split the input string
                        int count;
                        char **words = split_string_on_spaces(strData, &count);

                        if (words)
                        {
                            for (int i = 0; i < count; i++)
                            {
                                if (strcmp(words[i], "-f") == 0)
                                {
                                    strcpy(workingFileName, words[i + 1]);
                                }
                                free(words[i]);
                            }
                            free(words);
                        }

                        fp = fopen(workingFileName, "w");
                        fprintf(fp, "%s", fileBuf);
                        fclose(fp);

                        // Generate 8 new random letters
                        printf("Saved file to %s\n", workingFileName);
                        for (int i = 0; i < 8; i++)
                        {
                            randomLetters[i] = letters[rand() % 26];
                        }
                        randomLetters[8] = '\0'; // Null-terminate the string

                        // Build the command to run kmeans
                        char command[256];
                        strcpy(command, "./mathserver/kmeans ");
                        strcat(command, getSubString(strData, 7, 256));
                        char buf[RESPONSE_LIMIT];

                        // Run kmeans
                        system(command);

                        // Read the output file into a buffer
                        char outPutFileName[32];
                        strcpy(outPutFileName, "kmeans-results.txt");
                        printf("Opening file %s\n", outPutFileName);

                        FILE *fp2;
                        fp2 = fopen(outPutFileName, "rb");
                        if (fp2 == NULL)
                        {
                            perror("Error while opening the file.\n");
                            exit(EXIT_FAILURE);
                        }
                        char *fileBuffer = (char *)malloc(sizeof(char) * RESPONSE_LIMIT);
                        if (fileBuffer == NULL)
                        {
                            perror("Failed to allocate memory for fileBuf");
                            exit(EXIT_FAILURE);
                        }

                        int i = 0;
                        char c;
                        while ((c = fgetc(fp)) != EOF && i < RESPONSE_LIMIT - 1) // Ensure not to overflow buffer
                        {
                            fileBuffer[i++] = c;
                        }
                        fileBuffer[i] = '\0';
                        fclose(fp2);

                        // Send the output file to the client
                        printf("Sending file to client\n");
                        printf("Sending 442");
                        send(cd, fileBuffer, RESPONSE_LIMIT, 0);
                        system("rm kmeans-results.txt");

                        // Free allocated memory
                        free(randomLetters);
                        free(fileBuffer);
                    }
                    else
                    {
                        printf("Invalid command: %s \n", strData);
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