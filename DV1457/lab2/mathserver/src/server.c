#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>

void getHelp(char *argv[])
{
    printf("Usage: %s [-h] [-p port]\n", argv[0]);
    printf("-h\tPrint help text\n");
    printf("-p\tListen to port number port\n");
}

int main(int argc, char *argv[])
{
    int opt;
    int port; // Default port
    int portValid = 0;

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

    // Rest of your server code

    return 0;
}