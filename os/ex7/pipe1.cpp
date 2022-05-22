#include <stdio.h>

int main(void) {
    int bufferSize = 50;
    size_t maxRead = 25;
    int numOfSuccess = 0;
    char* buffer = new char[bufferSize];

    while(getline(&buffer, &maxRead, stdin) != EOF) {
        // TODO delete
        // printf("%s/n", buffer);
        // printf("array 11 is: %c/n", buffer[10]);
        if (buffer[10] == 's')
            numOfSuccess++;
    } 
    printf("Successes: %i\n", numOfSuccess);

    delete[] buffer;
}
