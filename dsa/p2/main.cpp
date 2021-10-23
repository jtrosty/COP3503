#pragma comment(linker, "/STACK:4000000")
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include "Random.h"
using std::ofstream;

#include "HashTable.h"
#include "MinHeap.h"
using std::cout;
using std::endl;
using std::cin;
using std::freopen;

void createInputFiles(int size);
double runtTestHeap(char testToRun, MinHeap& heap);
double emptyHeap(char testToRubn, MinHeap& heap);
double traverseHeap(MinHeap& heap);
int* generateRandomArray(int size);
void printResults(double* inResults, double* traversalTimes, double* outResults, char structureUsed);

int main (void) {
    char run = 1;
    MinHeap testHeap;

    char input = 0;
    std::string value;
    std::string streamInput;

    double* inTimes = new double[9];
    double* traversalTimes = new double[9];
    double* outTimes = new double[9];

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
                HashTable testHash;
                testHash.insert(1);
                testHash.print();
                testHash.insert(9);
                testHash.insert(12);
                testHash.print();
                break;
            }
            case '2': {
                createInputFiles(10);
                for(int i = 1; i <= 9; i++) {
                    if(testHeap.isEmpty()) {
                        inTimes[i] = runtTestHeap(i, testHeap);
                        traversalTimes[i] = traverseHeap(testHeap);
                        outTimes[i] = emptyHeap(i, testHeap);
                    }
                }
                printResults(inTimes, traversalTimes, outTimes, 1);

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
                generateRandomArray(10);
                break;
            }
            case '6': {
                cout << "Time to fill: " << runtTestHeap(1, testHeap);
                cout << endl;
                break;
            }
            case '7': {
                double result = emptyHeap(1, testHeap);
                
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
/////////////////////////////////////////////////////////////////////////////////
//                  Print results of all data

void printResults(double* inResults, double* traversalTimes, double* outResults, char structureUsed) {
    cout << " Resut for ";
    if (structureUsed == 1) cout << "Minimum Heap" << endl;
    else cout << "hash Table" << endl;
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


double traverseHeap(MinHeap& heap) {
    auto start = std::chrono::high_resolution_clock::now();
    heap.search(-1);
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
    std::string outName;
    switch(testToRun) {
        case 1: { outName = "data/out_sm_as.txt"; break; }
        case 2: { outName = "data/out_me_as.txt"; break; }
        case 3: { outName = "data/out_la_as.txt"; break; }
        case 4: { outName = "data/out_sm_ds.txt"; break; }
        case 5: { outName = "data/out_me_ds.txt"; break; }
        case 6: { outName = "data/out_la_ds.txt"; break; }
        case 7: { outName = "data/out_sm_ra.txt"; break; }
        case 8: { outName = "data/out_me_ra.txt"; break; }
        case 9: { outName = "data/out_la_ra.txt"; break; }
    }

    std::ofstream outPutFile;
    auto start = std::chrono::high_resolution_clock::now();
    outPutFile.open(outName);
    while(!heap.isEmpty()) {
        outPutFile << heap.extractMin() << ", ";
    }
    outPutFile.close();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time = end - start;
    //cout << "Time to empty: " << time.count() << endl;
    return time.count();
}

///////////////////////////////////////////////////////////////////////////////
//               Empty heap test
double runtTestHeap(char testToRun, MinHeap& heap) {
    std::ifstream infile;
    std::string inputData = "";
    std::string streamInput;
    switch(testToRun) {
        case 1: { inputData = "data/sm_as_in.txt"; break; }
        case 2: { inputData = "data/me_as_in.txt"; break; }
        case 3: { inputData = "data/la_as_in.txt"; break; }
        case 4: { inputData = "data/sm_ds_in.txt"; break; }
        case 5: { inputData = "data/me_ds_in.txt"; break; }
        case 6: { inputData = "data/la_ds_in.txt"; break; }
        case 7: { inputData = "data/sm_ra_in.txt"; break; }
        case 8: { inputData = "data/me_ra_in.txt"; break; }
        case 9: { inputData = "data/la_ra_in.txt"; break; }
    }

    auto start = std::chrono::high_resolution_clock::now();
    infile.open(inputData, std::ifstream::in);

    if (infile.is_open()) {
        while(!infile.eof()) {
            std::getline(infile, streamInput, ',');
            if (!streamInput.empty()) heap.insert(std::stoi(streamInput));
        }
        bool good = infile.good();
        bool eofbit = infile.eof();
        bool fail = infile.fail();
        bool bad = infile.bad();
        infile.close();
    }
    else cout << "DIDDN'T OPEN TEST: " << testToRun << endl;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time = end - start;
    //cout << "Time to fill: " << time.count() << endl;

    return time.count();
}

///////////////////////////////////////////////////////////////////////////////
//               Create 9 test files to input small, medium, and large files in
//               3 formats, ascending, descending, and random.

void createInputFiles(int size) {
    int bigSize = size * 10;
    int reallyBigSize = size * 100;
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
    for (int i = size; i > 0; i--) {
        if (i == 1) outPutFile << i; 
        else outPutFile << i << ", ";
    }
    outPutFile.close();
   
    outPutFile.open("data/me_ds_in.txt");
    for (int i = bigSize; i > 0; i--) {
        if (i == 1) outPutFile << i; 
        else outPutFile << i << ", ";
    }
    outPutFile.close();

    outPutFile.open("data/la_ds_in.txt");
    for (int i = reallyBigSize; i > 0; i--) {
        if (i == 1) outPutFile << i; 
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