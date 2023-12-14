#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//Esta função lê o socket e retorna o status code da ultima linha da mensagem (funciona mesmo se so tiver uma linha)
int getLastLineStatusCode(char *buf){
    int a;
    char *pt;
    pt = strtok (buf,"\n");
    while (pt != NULL) {
        a = 0;
        a = atoi(pt);
        pt = strtok (NULL, "\n");
    }
    return a;
}

int getFilename(char *buf, char* filename){
    char *pt;
    pt = strtok (buf,"/");

    while (pt != NULL) {
        strcpy(filename, pt);
        pt = strtok (NULL, "/");
    }

    return 0;
}

int getPortNumber(char* buf){
    int numb[5] = {0};
    int i = 0;
    char *pt;
    pt = strtok (buf,",");
    pt = strtok (NULL,",");
    while (pt != NULL) {
        int a = atoi(pt);
        numb[i] = a;
        pt = strtok (NULL, ",");
        i++;
    }
    return (numb[3]*256 + numb[4]);
}

// Function to create a socket
int createSocket(const char *SERVER_ADDR, int SERVER_PORT) {
    int sockfd;
    struct sockaddr_in server_addr;

    printf("\n---------- Creating new connection... ----------\n");

    /* create the socket */
    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR); /* 32 bit Internet address network byte ordered */
    server_addr.sin_port = htons(SERVER_PORT);            /* server TCP port must be network byte ordered */

    /* open a TCP socket */
    if ((sockfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0)) < 0) {
        perror("socket()");
        return -1;
    }

    /* connect to the server */
    /*
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect()");
        close(sockfd);
        return -1;
    }
    */

    connect(sockfd, (struct sockaddre *)&server_addr, sizeof(server_addr));
    
    return sockfd;
}

// Function to handle errors
void handleTCPError(const char *functionName, const char *errorMessage, int sockfd, int sockfd2, FILE *fileptr) {
    fprintf(stderr, "Error in function %s: %s\n", functionName, errorMessage);

    if (sockfd2 > 0) {
        close(sockfd2);
    }

    if (sockfd > 0) {
        close(sockfd);
    }

    if (fileptr != NULL) {
        fclose(fileptr);
    }

    exit(EXIT_FAILURE);
}

// Function to create FTP connection
int createConnection(const char *SERVER_ADDR, int SERVER_PORT, const char *user, const char *passwd, const char *path) {
    FILE *fileptr = NULL;

    int sockfd = createSocket(SERVER_ADDR, SERVER_PORT);
    if (sockfd == -1) {
        handleTCPError("createSocket", "Failed to create socket", -1, -1, NULL);
    }

    int sockfd2 = 0;
    int STOP = 0, visited = 0, port = 0, download = 0;
    char userLogin[50], passwdLogin[50], retrvPath[50], filename[50];
    userLogin[0] = '\0';
    passwdLogin[0] = '\0';
    retrvPath[0] = '\0';

    // Build login and path strings
    snprintf(userLogin, sizeof(userLogin), "user %s\r\n", user);
    snprintf(passwdLogin, sizeof(passwdLogin), "pass %s\r\n", passwd);
    snprintf(retrvPath, sizeof(retrvPath), "retr %s\r\n", path);

    getFilename(path, filename);

    char buf[500] = {0}, buf2[500] = {0};

    size_t bytes, bytes2;

    // Main loop
    while (!STOP) {
        memset(buf, 0, sizeof(buf));
        bytes = read(sockfd, buf, sizeof(buf));

        if (download) {
            memset(buf2, 0, sizeof(buf2));
            bytes2 = read(sockfd2, buf2, sizeof(buf2));
            if (bytes2 != -1 && bytes2 != 0) {
                printf("\nbuf2:");
                for (size_t i = 0; i < bytes2; i++) {
                    printf("%c", buf2[i]);
                    fputc(buf2[i], fileptr);
                }
            }
        }

        if (bytes == -1 || bytes == 0) {
            continue;
        }

        printf("\n%s\n", buf);
        int sc = getLastLineStatusCode(buf);

        switch (sc) {
            case 220:
                if (visited) {
                    break;
                }
                visited = 1;
                printf("\n---------- Sending user... ---------\n");
                write(sockfd, userLogin, strlen(userLogin));
                break;

            case 331:
                printf("\n---------- Sending password... ----------\n");
                write(sockfd, passwdLogin, strlen(passwdLogin));
                break;

            case 230:
                printf("\n---------- Entering passive mode... ----------\n");
                write(sockfd, "pasv\r\n", 6);
                break;

            case 227:
                printf("\n---------- Calculating port number... ----------\n");
                port = getPortNumber(buf);
                printf("\nPort Calculated: %d\n", port);

                sockfd2 = createSocket(SERVER_ADDR, port);
                if (sockfd2 == -1) {
                    handleTCPError("createSocket", "Failed to create data socket", sockfd, -1, NULL);
                }

                printf("\n---------- Retrieving file... ----------\n");
                write(sockfd, retrvPath, strlen(retrvPath));
                break;

            case 150:
                printf("\n---------- Starting File Download... ----------\n");
                fileptr = fopen(filename, "w");
                if (fileptr == NULL) {
                    handleTCPError("fopen", "Failed to open file for writing", sockfd, sockfd2, NULL);
                }
                printf("\n--- Created file with name '%s' ---\n", filename);
                download = 1;
                break;

            case 226:
                while (1) {
                    memset(buf2, 0, sizeof(buf2));
                    bytes2 = read(sockfd2, buf2, sizeof(buf2));
                    if (bytes2 != -1 && bytes2 != 0) {
                        printf("\nbuf2:");
                        for (size_t i = 0; i < bytes2; i++) {
                            printf("%c", buf2[i]);
                            fputc(buf2[i], fileptr);
                        }
                        printf("\n");
                    } else {
                        break;
                    }
                }
                printf("\n---------- Ending File Download... ----------\n");
                download = 0;
                STOP = 1;
                printf("\n---------- Closing connection... ----------\n");
                write(sockfd, "quit\r\n", 6);
                break;

            default:
                printf("\n---------- Status code %d not recognized ----------\n", sc);
                handleTCPError("createConnection", "Unknown status code", sockfd, sockfd2, fileptr);
                break;
        }
    }

    fclose(fileptr);

    if (close(sockfd2) < 0) {
        perror("close()");
        handleTCPError("close", "Failed to close data socket", sockfd, -1, NULL);
    }

    if (close(sockfd) < 0) {
        perror("close()");
        handleTCPError("close", "Failed to close control socket", -1, sockfd2, fileptr);
    }

    return 0;
}

