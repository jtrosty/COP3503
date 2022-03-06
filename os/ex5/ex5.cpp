#include <thread>
#include <iostream>
#include <stdlib.h>

void guessNumber(int threadID, int value) {
    while ((rand() % 9999) != value) {}
    printf("Thread %i completed.\n", threadID);
}

int main(int argc, char *argv[]) {
    int value = 0;
    
    if (argc = 2) {
        value = std::stoi(argv[1]);
    }
    else {
        printf("Please only input 1 numbers");
    }

    //std::thread myThread[] = new std::thread[10];
    std::thread myThread[10];

    for (int i = 0; i < 10; i++) 
        myThread[i] = std::thread(guessNumber, i, value);
    
    // end
    for (int i = 0; i < 10; i++) 
        myThread[i].join();

    printf("All threads have finished finding numbers.\n");

    return 0;
}
