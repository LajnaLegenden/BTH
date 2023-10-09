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

int matSol = 1;
int kmeansSol = 1;

//function to trim a string
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
    } else {
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

            //write buffer to file
            FILE *fp;
            //filename should be matinv_client1_soln(matSol++).txt

            char filename[50];
            sprintf(filename, "matinv_client%d_soln%d.txt", getpid(), matSol++);
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
