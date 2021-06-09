#include <iostream>
#include <chrono>
#include "ABS.h"
#include "ABQ.h"
using namespace std;
//#include "leaker.h"


struct TestInputs {
    int N;
    float ScaleFactor;
}; 

int main() {
    
    struct TestInputs testInputs[5];
    testInputs[0].N = 10000000;
    testInputs[0].ScaleFactor = 1.5f;
    testInputs[1].N = 30000000;
    testInputs[1].ScaleFactor = 2.0f;
    testInputs[2].N = 50000000;
    testInputs[2].ScaleFactor = 3.0f;
    testInputs[3].N = 75000000;
    testInputs[3].ScaleFactor = 10.0f;
    testInputs[4].N = 100000000;
    testInputs[4].ScaleFactor = 100.0f;
    int numOfTests = 5;
    int N;
    float scaleFactor;


    // TEST WITH STACK ###################################### 
    // ######################################################
    
    cout << "TEST WITH STACK" << endl;
    for (int j = 0; j < numOfTests; ++j) {
        N = testInputs[j].N;
        scaleFactor = testInputs[j].ScaleFactor;
        
        ABS<int> intABS(2, scaleFactor);
        cout << "Test" << (j + 1) <<  ": " << endl;
        cout << "Scale: " << scaleFactor << " N: " << N << endl;

        auto start = chrono::high_resolution_clock::now();
        for (int i = 0; i < N; i++) {
            intABS.push(i);
        }
        for (int i = 0; i < N; i++) {
            intABS.pop();
        }
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> time = end - start;

        cout << "Sec: " << time.count() << endl;
        cout << "Resizes " << intABS.getTotalResizes() << endl;
    }
    
    // TEST WITH QUEUE #######################################
    // #######################################################
    cout << "TEST WITH QUEUE" << endl;
    for (int j = 0; j < numOfTests; ++j) {
        N = testInputs[j].N;
        scaleFactor = testInputs[j].ScaleFactor;
        
        ABQ<int> intABQ(2, scaleFactor);
        cout << "Test " << (j + 1) <<  ": " << endl;
        cout << "Scale: " << scaleFactor << " N: " << N << endl;

        auto start2 = chrono::high_resolution_clock::now();
        for (int i = 0; i < N; i++) {
            intABQ.enqueue(i);
        }
        for (int i = 0; i < N; i++) {
            cout << "\n" << intABQ.dequeue();
        }
        auto end2 = chrono::high_resolution_clock::now();
        chrono::duration<double> time = end2 - start2;

        cout << "Sec: " << time.count() << endl;
        cout << "Resizes " << intABQ.getTotalResizes() << endl;
    }
}