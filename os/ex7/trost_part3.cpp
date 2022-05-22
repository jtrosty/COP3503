#include <stdio.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int* sort(int array[], int size) {
    int smallest = 0;
    for (int i = 0; i < size; i++) {
        smallest = i;
        for (int j = i + 1; j < size; j++) {
            if (array[j] < array[smallest]) smallest = j;
        }
        swap(&array[smallest], &array[i]);
    }
    return array;
}


int main(int argc, char* argv[]) {
    int bufferSize = 50;
    size_t maxRead = 22;
    int minArguments = 6;
    int numOfSuccess = 0;
    int numOfPipes = 4;
    int fiveInt[5];

    int fd[4][2];

    if (argc == minArguments) {
        for (int i = 0; i < 5; i++) {
            fiveInt[i] = atoi(argv[i + 1]);
        }
    }
    // read on the fd[x][0]
    // write on the fd[x][1]

    // Setup the 4 pipes
    for (int i = 0; i < numOfPipes; i++ ) {
        pipe(fd[i]);
    }

    int pid1 = fork();
    if (pid1 < 0) {
        return 1;
    }

    if (pid1 == 0) {
        close(fd[0][1]);
        close(fd[1][0]);
        close(fd[2][0]);
        close(fd[3][0]);
        close(fd[3][1]);

        int arrayOf5[5];
        read(fd[0][0], &arrayOf5, 5 * sizeof(arrayOf5[0])); 
        sort(arrayOf5, 5);
        
       // printf("\n array is: %i, %i, %i, %i, %i\n", arrayOf5[0], arrayOf5[1], arrayOf5[2], arrayOf5[3], arrayOf5[4]);
        
        if(write(fd[1][1], &arrayOf5, 5 * sizeof(arrayOf5[0])) < 0) {
            return 2;
        }
        if(write(fd[2][1], &arrayOf5, 5 * sizeof(arrayOf5[0])) < 0) {
            return 3;
        }
    
        close(fd[0][0]);
        close(fd[1][1]);
        close(fd[2][1]);

        return 0;
    }

    int pid2 = fork();
    if (pid2 < 0) {
        return 1;
    }
    if (pid2 == 0) {
        close(fd[0][0]);
        close(fd[0][1]);
        close(fd[1][1]);
        close(fd[2][0]);
        close(fd[2][1]);
        close(fd[3][0]);

        int child2Array[5];
        if (read(fd[1][0], &child2Array[0], 5 * sizeof(child2Array[0])) < 0 ) {
            return 9;
        }
        // find the median value
        //printf("\ child array got sorted is: %i, %i, %i, %i, %i\n", child2Array[0], child2Array[1], child2Array[2], child2Array[3], child2Array[4]);
        //printf("\nThe median is: %i\n", child2Array[2]);
        if (write(fd[3][1], &child2Array[2], sizeof(child2Array[3])) < 0) {
            return 4;
        }

        close(fd[1][0]);
        close(fd[3][1]);
        
        return 0;
    }

    // parent process
    close(fd[1][0]);
    close(fd[1][1]);
    close(fd[2][1]);
    close(fd[3][1]);
    int sorted[5];
    int median; 
    if (write(fd[0][1], &fiveInt, 5 * sizeof(fiveInt[0])) < 0) {
        return 5;
    }
    if (read(fd[2][0], &sorted, 5 * sizeof(sorted[0])) < 0 ) {
        return 6;
    }
    if (read(fd[3][0], &median, sizeof(int)) < 0 ) {
        return 7;
    }

    printf("\n parent prints the sorted array: %i, %i, %i, %i, %i\n", sorted[0], sorted[1], sorted[2], sorted[3], sorted[4]);
    printf(" Median value is: %i\n", median);


    close(fd[0][0]);
    close(fd[0][1]);
    close(fd[2][0]);
    close(fd[3][0]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
