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


// Get buffer lenght
int getBufferLength(char* buffer, int maxSize) {
    for (int i = 0; i < maxSize; i++) {
        if (buffer[i] == '\n') {
            return i;
        }
    }
    return -1; // on fail
}

// Get status string
std::string getStatusString(int queueSize, int port) {
    std::string result = "Wall server running on port ";
    result.append(std::to_string(port));
    result.append(" with queue size ");
    result.append(std::to_string(queueSize));
    return result;
}


int main(int argc, char *argv[]) {
    int port = 5514;

    // Handle inputs *****************************
    switch (argc) {
        case 1:
            break;
        case 2:
            port = atoi(argv[1]);
            break;
        default:
            printf("Too many arguments, maintaining defaults\n");
            break;
    }


    // Build the server *****************************
   //
    // sa_familiy_t
    // in_port_t
    // struct in_addr => uint32_T address 
    int serverFD = -1;
    int backlog = 10;
    struct sockaddr_in address;
    serverFD = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET; // type sa_family_t
    address.sin_port = htons(port); // type in_port_t
    address.sin_addr.s_addr = htonl(INADDR_ANY); // uint32_t

    // error
    if (serverFD < 0) 
        printf("Error opening socket.");
    //printf("Socket open\n");
    
    // use bind to assign the socket
    if(bind(serverFD, (struct sockaddr*) &address, sizeof(address)) == -1) {
        // error
        printf("There has been a problem with bind\n");
    }
    //printf("Bind successful.\n");


    // Listen onto the socket
    if(listen(serverFD, backlog) == -1) {
        // error
        printf("There has been a problem with listen.\n");
    }
    //printf("Listening successful.\n");

    // Accept the client connection
    int clientFD = -1;
    struct sockaddr_in addressClient;
    socklen_t clientLength = sizeof(addressClient);
    clientFD = accept(serverFD, (struct sockaddr*)&addressClient, &clientLength);
    if(clientFD == -1) {
        // error
        printf("There has been a problem with accept.\n");
    }
    //printf("Client accepted.\n");


    // Initialize data structures for wall
    int readBufferSize = 100;
    char readBuffer[readBufferSize];
    const unsigned int MAX_LENGTH = 80;   
    char nameInput[MAX_LENGTH];
    char postInput[MAX_LENGTH];
    int success = 0;
    int lengthOfInput = 0;

    char* hello = "Welcome to the server running on REPTILIAN";
    read(clientFD, readBuffer, readBufferSize);
    printf("%s\n", readBuffer);
    bzero(readBuffer, readBufferSize);
    write(clientFD, hello, 43);
    
    close(clientFD);
    return 0;



    // Loop to maintain server
    while (1) {
        bzero(readBuffer, readBufferSize);

        read(clientFD, readBuffer, readBufferSize);
        
        printf("\nClient: %s\n", readBuffer);

        printf("To Client: ");

        bzero(readBuffer, readBufferSize);
        int i = 0;
        while ((readBuffer[i++] = getchar()) != '\n') {
            // nothing
        }
        readBuffer[i] = '\n';

        write(clientFD, readBuffer, readBufferSize);

        if (strncmp("quit", readBuffer, 4) == 0) {
            break;
        }
    }
    close(clientFD);

    return 0;
}
