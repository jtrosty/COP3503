#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
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

    char input = 0;
    std::string value;
    std::ifstream infile;
    std::string streamInput;

    while (run != 0) {
        
        // Menu
        cout << "Menu: " << endl;
        cout << "1: Generate input files for test" << endl;
        cout << "2. Run Ascending test" << endl;
        cout << "3. input value and print heap" << endl;
        cout << "4. Extract min" << endl;
        cout << "5. Ascending into heap" << endl;

        // User input
        cin >> input;

        // Logic
        switch(input) {
            case '1': {
                createInputFiles();
                break;
            }
            case '2': {

                break;
            }
            case '3': {
                cin >> value;
                testHeap.insert(std::stoi(value));
                testHeap.printHeap();
                break;
            }
            case '4': {
                cout << testHeap.extractMin() << endl;
                break;
            }
            case '5': {
                auto start = std::chrono::high_resolution_clock::now();
                infile.open("data/sm_as.txt", std::ifstream::in);
                while(!infile.eof()) {
                    std::getline(infile, streamInput, ',');
                    testHeap.insert(std::stoi(streamInput));
                }
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> time = end - start;
                cout << "Time: " << time.count() << endl;
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
    int bigSize = size * 10;
    int reallyBigSize = size * 100;

    // Ascending files
    if (freopen("data/sm_as.txt", "w", stdout)) {
        for (int i = 0; i < size; i++) {
            if (i == size -1) cout << i; 
            else cout << i << ", ";
        }
    }
    else {
        cout << "did not work" << endl;
    }
    fclose(stdout);

    freopen("data/me_as.txt", "w", stdout);
    for (int i = 0; i < bigSize; i++) {
        if (i == bigSize -1) cout << i; 
        else cout << i << ", ";
    }
    fclose(stdout);

    freopen("data/la_as.txt", "w", stdout);
    for (int i = 0; i < reallyBigSize; i++) {
        if (i == reallyBigSize -1) cout << i; 
        else cout << i << ", ";
    }
    fclose(stdout);

    // Descending Files
    freopen("data/sm_ds.txt", "w", stdout);
    for (int i = size; i > 0; i--) {
        if (i == 1) cout << i; 
        else cout << i << ", ";
    }
    fclose(stdout);

    freopen("data/me_ds.txt", "w", stdout);
    for (int i = bigSize; i > 0; i--) {
        if (i == 1) cout << i; 
        else cout << i << ", ";
    }
    fclose(stdout);

    freopen("data/la_ds.txt", "w", stdout);
    for (int i = reallyBigSize; i > 0; i--) {
        if (i == 1) cout << i; 
        else cout << i << ", ";
    }
    fclose(stdout);

}