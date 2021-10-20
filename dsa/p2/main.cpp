#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <fstream>
using std::ofstream;

#include "MinHeap.h"
using std::cout;
using std::endl;
using std::cin;
using std::freopen;

void createInputFiles();

int main (void) {
    char run = 1;
    MinHeap testHeap;
    testHeap.insert(10);
    testHeap.insert(2);
    testHeap.insert(80);
    testHeap.insert(40);


    char input = 0;

    while (run != 0) {
        
        // Menu
        cout << "Menu: " << endl;
        cout << "1: " << endl;

        // User input
        cin >> input;

        // Logic
        switch(input) {
            case '1': {
                createInputFiles();
                break;
            }
            case 'q': {
                run = 0;
                break;
            }
        }
    }

    return 0;
}

/*
    auto start = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> time = end - start;
*/

void createInputFiles() {
    int size = 1000;

    // Ascending files
    if (freopen("data/sm_as.txt", "w", stdout)) {
        for (int i = 0; i < size; i++) {
            cout << i << ", ";
        }
    }
    else {
        cout << "did not work" << endl;
    }
    fclose(stdout);

    freopen("data/me_as.txt", "w", stdout);
    for (int i = 0; i < size * 10; i++) {
        cout << i << ", ";
    }
    fclose(stdout);

    freopen("data/la_as.txt", "w", stdout);
    for (int i = 0; i < size * 100; i++) {
        cout << i << ", ";
    }
    fclose(stdout);

    // Descending Files
    freopen("data/sm_ds.txt", "w", stdout);
    for (int i = size; i > 0; i--) {
        cout << i << ", ";
    }
    fclose(stdout);

    freopen("data/me_ds.txt", "w", stdout);
    for (int i = size * 10; i > 0; i--) {
        cout << i << ", ";
    }
    fclose(stdout);

    freopen("data/la_ds.txt", "w", stdout);
    for (int i = size * 100; i > 0; i--) {
        cout << i << ", ";
    }
    fclose(stdout);

}