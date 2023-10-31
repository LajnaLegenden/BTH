#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <netinet/in.h> //structure for storing address information
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> //for socket APIs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define RESPONSE_LIMIT 16384

int matSol = 1;
int kmeansSol = 1;

// function to trim a string
char *trim(char *str)
{
    char *end;

    // Trim leading space
    while (isspace((unsigned char)*str))
        str++;

    if (*str == 0) // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    // Write new null terminator
    *(end + 1) = 0;

    return str;
}

char **split_string_on_spaces(const char *str, int *count)
{
    int i, j, start;
    *count = 0;

    // First, count the number of words
    for (i = 0; str[i]; i++)
    {
        if (str[i] != ' ' && (i == 0 || str[i - 1] == ' '))
        {
            (*count)++;
        }
    }

    // Allocate memory for the result
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

int main(int argc, char *argv[])
{
    /**
     * Getopts does not support -ip, it only supports --ip
     * unix treats -ip as -i p
     * https://stackoverflow.com/questions/3975004/how-to-make-a-multi-character-parameter-in-unix-using-getopt
     */
    char *ip_address = NULL;
    int port = -1;

    int opt;
    int option_index = 0;

    struct option long_options[] = {
        {"ip", required_argument, NULL, 'i'},
        {"port", required_argument, NULL, 'p'},
        {NULL, 0, NULL, 0}};

    while ((opt = getopt_long(argc, argv, "i:p:", long_options, &option_index)) != -1)
    {
        switch (opt)
        {
        case 'i':
            ip_address = optarg;
            break;
        case 'p':
            port = atoi(optarg);
            break;
        case '?':
            fprintf(stderr, "Unknown option or missing argument: %s\n", argv[optind - 1]);
            return 1;
        }
    }

    // Check if both -i or --ip and -p options were provided
    if (ip_address == NULL || port == -1)
    {
        fprintf(stderr, "Usage: %s --ip|-i <IP_address> --port|-p <port_number>\n", argv[0]);
        return 1;
    }

    printf("IP Address: %s\n", ip_address);
    printf("Port: %d\n", port);

        char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("Current working dir: %s\n", cwd);
    // seed rgn
    srand(time(NULL));
    // create folder if not exists in pwd
    char *folderName1 = "results";
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

    // Your code to use ip_address and port for client functionality goes here

    // connect to socket at port

    // create socket

    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = inet_addr(ip_address);

    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        perror("Connection failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Connected to server\n");
    }

    char message[] = "Hello, server!";
    send(client_socket, message, sizeof(message), 0);

    while (1)
    {
        // listen for input
        char *input;
        size_t bufsize = 32;
        size_t characters;

        input = (char *)malloc(bufsize * sizeof(char));
        if (input == NULL)
        {
            perror("Unable to allocate buffer");
            exit(1);
        }

        printf("Type something: ");
        characters = getline(&input, &bufsize, stdin);
        trim(input);
        printf("%zu characters were read.\n", characters);
        printf("You typed: '%s'\n", input);

        if (strncmp(input, "matinvpar", 9) == 0)
        {
            printf("Requesting mathinvpar\n");
            send(client_socket, input, characters, 0);

            // revice data
            char buffer[4096];
            int nbytes = recv(client_socket, buffer, sizeof(buffer), 0);
            if (nbytes == -1)
            {
                perror("recv");
                exit(EXIT_FAILURE);
            }
            buffer[nbytes] = '\0';

            printf("Received a message (%d bytes) from the server!\n\n", nbytes);

            // write buffer to file
            FILE *fp;
            char filename[50];
            sprintf(filename, "results/matinv_client%d_soln%d.txt", getpid(), matSol++);
            printf("Writing to file %s\n", filename);
            fp = fopen(filename, "w");
            fprintf(fp, "%s", buffer);
            fclose(fp);
        }
        else if (strncmp(input, "kmeans", 5) == 0)
        {

            printf("Requesting kmeans\n");
            const char delimiter = ' '; // Delimiter is a space
            char fileName[32];
            int count;
            char **words = split_string_on_spaces(input, &count);

            if (words)
            {
                for (int i = 0; i < count; i++)
                {
                    if (strcmp(words[i], "-f") == 0)
                    {
                        strcpy(fileName, words[i + 1]);
                    }
                    free(words[i]);
                }
                free(words);
            }
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
            printf("File read successfully\n");
            printf("Sending file to server\n");
            // send input to server
            send(client_socket, input, characters, 0);

            char instruction[128];
            int nrbytes = recv(client_socket, instruction, sizeof(instruction), 0);
            if (nrbytes == -1)
            {
                perror("recv");
                exit(EXIT_FAILURE);
            }

            instruction[nrbytes] = '\0';

            printf("Received a message (%d bytes) from the server!\n\n", nrbytes);

            


            printf("Sending file to server\n");
            send(client_socket, fileBuf, RESPONSE_LIMIT, 0);
            // revice data
            char buffer[4096];
            int nbytes = recv(client_socket, buffer, sizeof(buffer), 0);
            if (nbytes == -1)
            {
                perror("recv");
                exit(EXIT_FAILURE);
            }
            buffer[nbytes] = '\0';

            printf("Received a message (%d bytes) from the server!\n\n", nbytes);

            // write buffer to file
           

            char filename[50];
            sprintf(filename, "results/kmeans_client%d_soln%d.txt", getpid(), matSol++);
            printf("Writing to file %s\n", filename);
            fp = fopen(filename, "w");
            fprintf(fp, "%s", buffer);
            fclose(fp);
        }
        else if (strncmp(input, "exit", 4) == 0)
        {
            printf("We have closed the connection\n");
            send(client_socket, input, characters, 0);
            break;
        }
    }
    close(client_socket);

    return 0;
}