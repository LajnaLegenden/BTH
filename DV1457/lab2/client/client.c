#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>

int main(int argc, char *argv[]) {
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
        {NULL, 0, NULL, 0}
    };

    while ((opt = getopt_long(argc, argv, "i:p:", long_options, &option_index)) != -1) {
        switch (opt) {
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
    if (ip_address == NULL || port == -1) {
        fprintf(stderr, "Usage: %s --ip|-i <IP_address> --port|-p <port_number>\n", argv[0]);
        return 1;
    }

    printf("IP Address: %s\n", ip_address);
    printf("Port: %d\n", port);

    // Your code to use ip_address and port for client functionality goes here

    return 0;
}
