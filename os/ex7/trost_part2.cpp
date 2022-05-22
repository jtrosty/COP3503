#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


int main(void) {
    int bufferSize = 50;
    size_t maxRead = 22;
    int numOfSuccess = 0;
    char* buffer = new char[bufferSize];
    char* dirFifo = "PipePart2";
    mkfifo(dirFifo, 0666);
    int fd = open(dirFifo, O_RDONLY);

    while(read(fd, buffer, maxRead) != -1) {
        // TODO delete
        //printf("\nThe buffer: %s\n", buffer);
        //printf("array 11 is: %c\n", buffer[10]);
        if (buffer[10] == 's')
            numOfSuccess++;
        else break;
    } 
    printf("Successes: %i\n", numOfSuccess);

    close(fd);
    delete[] buffer;
}
