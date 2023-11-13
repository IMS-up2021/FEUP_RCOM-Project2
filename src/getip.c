#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>


// Function to get IP address from the host
int getIP(char *host, char *IPaddress) {
    struct hostent *hostEntry;
    // Get host information
    if ((hostEntry = gethostbyname(host)) == NULL) {
        perror("gethostbyname");
        return -1;
    }
    // Extract the first IP address from the list
    struct in_addr *address = (struct in_addr *)hostEntry->h_addr;
    if (address == NULL) {
        fprintf(stderr, "Error: No IP address found for the host %s\n", host);
        return -1;
    }
    // Convert the IP address to string
    if (inet_ntop(AF_INET, address, IPaddress, INET_ADDRSTRLEN) == NULL) {
        perror("inet_ntop");
        return -1;
    }
    // Print host information
    printf("Host name  : %s\n", hostEntry->h_name);
    printf("IP Address : %s\n", IPaddress);

    return 0;
}
