#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>
#include <queue>

int main (int argc, char *argv[]) {
    int port;

    // Handle inputs *****************************
    switch (argc) {
        case 1:
            break;
        case 2:
            port = atoi(argv[1]);
            break;
        default:
            printf("Too many arguments\n");
            break;
    }

    // Make the client socket
    int clientSocketFD = -1;
    struct sockaddr_in address;
    clientSocketFD = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET; // type sa_family_t
    address.sin_port = htons(port); // type in_port_t
    address.sin_addr.s_addr = htonl(INADDR_ANY); // uint32_t

    if (clientSocketFD == -1) {
        printf("Error opening socket.\n");
    }

    // Connect socket to server port
    if (connect(clientSocketFD, (struct sockaddr*)&address, sizeof(address)) != 0 ) {
        printf("Connection with port failed");
        return 1;
    }


    // Talk to the server
    int bufferSize = 100;
    char buffer[bufferSize];

    char* intro = "Jonathan Trost:6736-9531";

    write(clientSocketFD, intro, 25);
    read(clientSocketFD, buffer, bufferSize);
    printf("\n%s\n", buffer);
    bzero(buffer, bufferSize);

    close(clientSocketFD);
}
