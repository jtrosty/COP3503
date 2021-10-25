#pragma comment(linker, "/STACK:4000000")
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <fstream>
#include <set>
#include <string>
#include "Random.h"
using std::ofstream;

#include "HashTable.h"
#include "MinHeap.h"
using std::cout;
using std::endl;
using std::cin;
using std::freopen;

void createInputFiles(int size, int bigSize, int reallyBigSize);
double fillHeap(char testToRun, MinHeap& heap);
double fillHashTable(char testToRun, HashTable& table);
double emptyHashTable(char testToRun, HashTable& table); 
double emptyHeap(char testToRubn, MinHeap& heap);
double traverseHeap(MinHeap& heap);
double traverseHash(HashTable& table); 
int* generateRandomArray(int size);
void printResults(double* inResults, double* traversalTimes, double* outResults, char structureUsed);
std::string getFileName(char testToRun); 
std::string getFileOutputName(char testToRun); 

int main (void) {
    char run = 1;
    HashTable testHash;
    MinHeap testHeap;
    std::set <int> s;

    int size = 100;
    int bigSize = 10 * size;
    int reallyBigSize = 10 * bigSize;

    char input = 0;
    std::string value;
    std::string streamInput;

    double* inTimesHeap        = new double[10];
    double* traversalTimesHeap = new double[10];
    double* outTimesHeap       = new double[10];

    double* inTimesHash        = new double[10];
    double* traversalTimesHash = new double[10];
    double* outTimesHash       = new double[10];
    double startValue = -1.0f;

    for (int i = 0; i < 10; i++) {
        inTimesHeap[i]        = startValue;
        traversalTimesHeap[i] = startValue;
        outTimesHeap[i]       = startValue;
        inTimesHash[i]        = startValue;
        traversalTimesHash[i] = startValue;
        outTimesHash[i]       = startValue;
    }

    while (run != 0) {
        
        // Menu
        cout << "Menu: " << endl;
        cout << "1. Create input and run all tests" << endl;
        cout << "q  - Quit the program." << endl;

        // User input
        cin >> input;
        int numOfTests = 1;

        // Logic
        switch(input) {
            case '1': {
                createInputFiles(size, bigSize, reallyBigSize);

                // Min Heap
                for(int i = 1; i <= numOfTests; i++) {
                    if(testHeap.isEmpty()) {
                        inTimesHeap[i] = fillHeap(i, testHeap)           * 1.0f;
                        traversalTimesHeap[i] = traverseHeap(testHeap) * 1.0f;
                        outTimesHeap[i] = emptyHeap(i, testHeap)         * 1.0f;
                    }
                }

                // Hast Table
                for(int i = 1; i <= numOfTests; i++) {
                    if(testHash.isEmpty()) {
                        inTimesHash[i] = fillHashTable(i, testHash)      * 1.0f;
                        traversalTimesHash[i] = traverseHash(testHash) * 1.0f;
                        outTimesHash[i] = emptyHashTable(i, testHash)    * 1.0f;
                    }
                }

                printResults(inTimesHeap, traversalTimesHeap, outTimesHeap, 1);
                printResults(inTimesHash, traversalTimesHash, outTimesHash, 2);
                break;
            }
            case '3': { // used for testing
                cin >> value;
                testHeap.insert(std::stoi(value));
                testHeap.printHeap();
                break;
            }
            case '4': { // used for testing
                cout << testHeap.extractMin() << endl;
                break;
            }
            case 'q': { // used to extit while loop
                run = 0;
                break;
            }
        }
    }
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////
//                  Print results of all data

void printResults(double* inResults, double* traversalTimes, double* outResults, char structureUsed) {
    cout << " Resut for ";
    if (structureUsed == 1) cout << "Minimum Heap" << endl;
    else cout << "Hash Table" << endl;
    cout << "Small  Ascending In:  " << inResults[1] << " | traversal: " << traversalTimes[1] << " | Small  Ascending out:  " << outResults[1] << endl;
    cout << "Small  Descending In: " << inResults[4] << " | traversal: " << traversalTimes[4] << " | Small  descending out: " << outResults[4] << endl;
    cout << "Small  Random In:     " << inResults[7] << " | traversal: " << traversalTimes[7] << " | Small  Random out:     " << outResults[7] << endl;
    cout << "Medium Ascending In:  " << inResults[2] << " | traversal: " << traversalTimes[2] << " | Medium Ascending out:  " << outResults[2] << endl;
    cout << "Medium Descending In: " << inResults[5] << " | traversal: " << traversalTimes[5] << " | Medium descending out: " << outResults[5] << endl;
    cout << "Medium Random In:     " << inResults[8] << " | traversal: " << traversalTimes[8] << " | Medium Random out:     " << outResults[8] << endl;
    cout << "Large  Ascending In:  " << inResults[3] << " | traversal: " << traversalTimes[3] << " | Large  Ascending out:  " << outResults[3] << endl;
    cout << "Large  Descending In: " << inResults[6] << " | traversal: " << traversalTimes[6] << " | Large  descending out: " << outResults[6] << endl;
    cout << "Large  Random In:     " << inResults[9] << " | traversal: " << traversalTimes[9] << " | Large  Random out:     " << outResults[9] << endl;
}

/////////////////////////////////////////////////////////////////////////////////
//                 Travese the 2 data structurs 

double traverseHeap(MinHeap& heap) {
    auto start = std::chrono::high_resolution_clock::now();
    heap.traversalOfMinHeap();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time = end - start;
    //cout << "Time to empty: " << time.count() << endl;
    return time.count();
}

double traverseHash(HashTable& table) {
    auto start = std::chrono::high_resolution_clock::now();
    table.print();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time = end - start;
    //cout << "Time to empty: " << time.count() << endl;
    return time.count();
}

////////////////////////////////////////////////////////////////////////////////
//   Generates a Random Array, first a array of 1 to size is created. Then
//   the array is loop through once and a random index remaining in the 
//   array is used to swap with the current index in the loop.
int* generateRandomArray(int size) {
    Random rand;
    int* resultArray = new int[size];
    for (int i = 0; i < size; i++) {
        resultArray[i] = i;
    }
    for (int i = 0; i < size; i++) {
        int swapIndex = rand.Int(i, size - 1);
        int temp = resultArray[swapIndex];
        resultArray[swapIndex] = resultArray[i];
        resultArray[i] = temp;
    }
    //for (int i = 0; i < size; i++) {
    //    cout << resultArray[i] << ", ";
    //}
    return resultArray;
}

///////////////////////////////////////////////////////////////////////////////
//               Empty heap test
double emptyHeap(char testToRun, MinHeap& heap) {
    std::string inputFile = getFileName(testToRun);
    std::ifstream file;
    std::string streamInput;

    auto start = std::chrono::high_resolution_clock::now();
    file.open(inputFile);
    while(!file.eof()) {
        std::getline(file, streamInput, ',');
        heap.deleteValue(std::stoi(streamInput));
    }
    file.close();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> time = end - start;
    //cout << "Time to empty: " << time.count() << endl;
    return time.count();
}

///////////////////////////////////////////////////////////////////////////////
//               Empty HashTable test
double emptyHashTable(char testToRun, HashTable& table) {
    std::string inputFile = getFileName(testToRun);

    std::ifstream file;
    std::string streamInput;
    auto start = std::chrono::high_resolution_clock::now();
    file.open(inputFile);
    while(!file.eof()) {
        std::getline(file, streamInput, ',');
        table.remove(std::stoi(streamInput));
    }
    file.close();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> time = end - start;
    //cout << "Time to empty: " << time.count() << endl;
    return time.count();
}

///////////////////////////////////////////////////////////////////////////////
//               Insert heap test
double fillHeap(char testToRun, MinHeap& heap) {
    std::ifstream infile;
    std::string streamInput;
    std::string inputData = getFileName(testToRun);

    auto start = std::chrono::high_resolution_clock::now();
    infile.open(inputData, std::ifstream::in);

    if (infile.is_open()) {
        while(!infile.eof()) {
            std::getline(infile, streamInput, ',');
            if (!streamInput.empty()) heap.insert(std::stoi(streamInput));
        }
        infile.close();
    }
    else cout << "DIDDN'T OPEN TEST: " << testToRun << endl;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> time = end - start;
    //cout << "Time to fill: " << time.count() << endl;

    return time.count();
}

///////////////////////////////////////////////////////////////////////////////
//               Insert HashTable test
double fillHashTable(char testToRun, HashTable& table) {
    std::ifstream infile;
    std::string streamInput;
    std::string inputData = getFileName(testToRun);

    auto start = std::chrono::high_resolution_clock::now();
    infile.open(inputData, std::ifstream::in);

    if (infile.is_open()) {
        while(!infile.eof()) {
            std::getline(infile, streamInput, ',');
            if (!streamInput.empty()) table.insert(std::stoi(streamInput));
        }
        infile.close();
    }
    else cout << "DID NOT OPEN TEST: " << testToRun << endl;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> time = end - start;

    return time.count();
}
///////////////////////////////////////////////////////////////////////////////
//               Create 9 test files to input small, medium, and large files in
//               3 formats, ascending, descending, and random.

void createInputFiles(int size, int bigSize, int reallyBigSize) {
    int* randomArray;
    std::ofstream outPutFile;

    // Ascending files
    outPutFile.open("data/sm_as_in.txt");
    for (int i = 0; i < size; i++) {
        if (i == size - 1) outPutFile << i; 
        else outPutFile << i << ", ";
    }
    outPutFile.close();

    outPutFile.open("data/me_as_in.txt");
    for (int i = 0; i < bigSize; i++) {
        if (i == bigSize - 1) outPutFile << i; 
        else outPutFile << i << ", ";
    }
    outPutFile.close();

    outPutFile.open("data/la_as_in.txt");
    for (int i = 0; i < reallyBigSize; i++) {
        if (i == reallyBigSize - 1) outPutFile << i; 
        else outPutFile << i << ", ";
    }
    outPutFile.close();

    outPutFile.open("data/sm_ds_in.txt");
    for (int i = size - 1; i >= 0; i--) {
        if (i == 0) outPutFile << i; 
        else outPutFile << i << ", ";
    }
    outPutFile.close();
   
    outPutFile.open("data/me_ds_in.txt");
    for (int i = bigSize - 1; i >= 0; i--) {
        if (i == 0) outPutFile << i; 
        else outPutFile << i << ", ";
    }
    outPutFile.close();

    outPutFile.open("data/la_ds_in.txt");
    for (int i = reallyBigSize - 1; i >= 0; i--) {
        if (i == 0) outPutFile << i; 
        else outPutFile << i << ", ";
    }
    outPutFile.close();

    outPutFile.open("data/sm_ra_in.txt");
    randomArray = generateRandomArray(size);
    for (int i = 0; i < size; i++) {
        if (i == size - 1) outPutFile << randomArray[i]; 
        else outPutFile << randomArray[i] << ", ";
    }
    outPutFile.close();
    delete[] randomArray;

    outPutFile.open("data/me_ra_in.txt");
    randomArray = generateRandomArray(bigSize);
    for (int i = 0; i < bigSize; i++) {
        if (i == bigSize - 1) outPutFile << randomArray[i]; 
        else outPutFile << randomArray[i] << ", ";
    }
    outPutFile.close();
    delete[] randomArray;

    outPutFile.open("data/la_ra_in.txt");
    randomArray = generateRandomArray(reallyBigSize);
    for (int i = 0; i < reallyBigSize; i++) {
        if (i == reallyBigSize - 1) outPutFile << randomArray[i]; 
        else outPutFile << randomArray[i] << ", ";
    }
    outPutFile.close();
    delete[] randomArray;
}

//////////////////////////////////////////////////////////////////////
//                   Helper function, get file name
std::string getFileName(char testToRun) {
    switch(testToRun) {
        case 1: { return "data/sm_as_in.txt"; break; }
        case 2: { return "data/me_as_in.txt"; break; }
        case 3: { return "data/la_as_in.txt"; break; }
        case 4: { return "data/sm_ds_in.txt"; break; }
        case 5: { return "data/me_ds_in.txt"; break; }
        case 6: { return "data/la_ds_in.txt"; break; }
        case 7: { return "data/sm_ra_in.txt"; break; }
        case 8: { return "data/me_ra_in.txt"; break; }
        case 9: { return "data/la_ra_in.txt"; break; }
    }
    // Failed to return
    return "";
}

std::string getFileOutputName(char testToRun) {
    switch(testToRun) {
            case 1: { return "data/out_sm_as.txt"; break; }
            case 2: { return "data/out_me_as.txt"; break; }
            case 3: { return "data/out_la_as.txt"; break; }
            case 4: { return "data/out_sm_ds.txt"; break; }
            case 5: { return "data/out_me_ds.txt"; break; }
            case 6: { return "data/out_la_ds.txt"; break; }
            case 7: { return "data/out_sm_ra.txt"; break; }
            case 8: { return "data/out_me_ra.txt"; break; }
            case 9: { return "data/out_la_ra.txt"; break; }
    }
    return "";
}
