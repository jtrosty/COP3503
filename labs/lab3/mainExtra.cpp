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
    bool TEST_ABS = false;
    bool TEST_ABQ = false;
    bool outToTextFile = true;
    float timeResultsABS[25];
    int resizeResultsABS[25];
    float timeResultsABQ[25];
    int resizeResultsABQ[25];
    int indexABS = 0;
    int indexABQ = 0;
    
    // ######################################################
    cout << "TEST WITH STACK" << endl;
    for (int k = 0; k < numOfTests; ++k) {
        // TEST WITH STACK #####################################
        // #####################################################
        for (int j = 0; j < numOfTests; ++j) { //TODO must change
            N = testInputs[j].N;
            scaleFactor = testInputs[k].ScaleFactor;
            ABS<int> intABS(2, scaleFactor);
            if (TEST_ABS) {
                /*
                for (int i = 0; i < N; i++) {
                    intABS.push(i);
                    intABS.test_DEBUG();
                }
                cout << "success push" << endl;
                for (int i = 0; i < N; i++) {
                    //cout << intABS.pop() << " ";
                    intABS.pop();
                    intABS.test_DEBUG();
                }
                cout << "success" << endl;
                */
            } 
            else {
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

                cout << "Sec: " << endl << time.count() << endl;
                cout << "Resizes " << endl << intABS.getTotalResizes() << endl;
                timeResultsABS[indexABS] = time.count();
                resizeResultsABS[indexABS] = intABS.getTotalResizes();
                indexABS++;
            }
        }
        
        // TEST WITH QUEUE #######################################
        // #######################################################
        cout << "TEST WITH QUEUE" << endl;
        for (int j = 0; j < numOfTests; ++j) {
            N = testInputs[j].N;
            scaleFactor = testInputs[k].ScaleFactor;
            
            ABQ<int> intABQ(2, scaleFactor);
            if (TEST_ABQ) {
                for (int i = 0; i < N; i++) {
                    intABQ.enqueue(i);
                }
                cout << "success push" << endl;
                for (int i = 0; i < N; i++) {
                    cout << intABQ.dequeue() << " ";
                }
                cout << endl;
                cout << "success" << endl;
            } 
            else {
                cout << "Test Queue " << (j + 1) <<  ": " << endl;
                cout << "Scale: " << scaleFactor << " N: " << N << endl;

                auto start2 = chrono::high_resolution_clock::now();
                for (int i = 0; i < N; i++) {
                    intABQ.enqueue(i);
                }
                for (int i = 0; i < N; i++) {
                    intABQ.dequeue();
                }
                auto end2 = chrono::high_resolution_clock::now();
                chrono::duration<double> time2 = end2 - start2;

                cout << "Sec: " << time2.count() << endl;
                cout << "Resizes " << intABQ.getTotalResizes() << endl;
                timeResultsABQ[indexABQ] = time2.count();
                resizeResultsABQ[indexABQ] = intABQ.getTotalResizes();
                indexABQ++;
            }
        }
    }
    
    if (outToTextFile) {
        freopen("testResultsABS.txt", "w", stdout);
        for (int tracker = 0; tracker <= indexABS; tracker++) {
            cout << timeResultsABS[tracker] << endl;
        }
        cout << "break" << endl;
        for (int tracker = 0; tracker <= indexABS; tracker++) {
            cout << resizeResultsABS[tracker] << endl;
        }
        cout << "done" << endl;
    }
    
    
    if (outToTextFile) {
        cout << "index " << indexABQ << endl;
        freopen("testResultsABQ.txt", "w", stdout);
        for (int tracker = 0; tracker <= indexABQ; tracker++) {
            cout << timeResultsABQ[tracker] << endl;
        }
        cout << "break" << endl;
        for (int tracker = 0; tracker <= indexABQ; tracker++) {
            cout << resizeResultsABQ[tracker] << endl;
        }
        cout << "done" << endl;
        fclose(stdout);
    }
}