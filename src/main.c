#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientTCP.c"
#include "download.c"
#include "getip.c"

// Function to print usage information
void printUsage(const char *programName) {
    fprintf(stderr, "Usage: %s <URL to deconstruct>\n"
                    "URL should be as follows: ftp://[<user>:<password>@]<host>/<url-path>\n", programName);
    exit(EXIT_FAILURE);
}

// Function to handle errors
void handleError(const char *functionName, const char *errorMessage) {
    fprintf(stderr, "Error in function %s: %s\n", functionName, errorMessage);
    exit(EXIT_FAILURE);
}

// Main function  
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printUsage(argv[0]);
    }

    char host[strlen(argv[1])], path[strlen(argv[1])], IPaddress[15] = "", user[strlen(argv[1])], password[strlen(argv[1])], dummy[strlen(argv[1])];

    // Get details from the URL
    if (getDetails(argc, argv, path, host, user, password, dummy) != 0) {
        handleError("getDetails", "Failed to get details from URL");
    }

    printf("\n");

    // Get IP address from the host
    if (getIP(host, IPaddress) != 0) {
        handleError("getIP", "Failed to get IP address from host");
    }

    printf("\n");

    // Create connection using FTP
    if (createConnection(IPaddress, 21, user, password, path) != 0) {
        handleError("createConnection", "Failed to create FTP connection");
    }

    printf("\n");

    return 0;
}
