#include <stdio.h>
#include <iostream>
using std::cin;
using std::cout;
// This is a test of the push
// I was able to make changes on home PC and upload to git
int absInt(int x) {
    if (x < 0) return -x;
    else return x;
}

void halfASquare(int numOfHash) {
    for(int i = numOfHash; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            cout << "#";
        }
        cout << "\n";
    }
}

void pyramidHash(int width) {
    for (int i = 1 - width; i < width; i++) {
        int iAbs = absInt(i);
        for (int j = 0; j < (width - iAbs); j++) {
            cout << "#";
        } 
        cout<< "\n";
    }
}

void invertedPyramid(int size) {
    // Pg 53 Exercise 2-1
    int startOfHash = 0;
    int endOfHash = size - 1;
    for (int j = 0; j < size; j += 2) {
        for (int i = 0; i < size; i++ ) {
            if (i < startOfHash || i > endOfHash) 
                cout << " ";
            else cout << "#";
        }
        cout << "\n";
        startOfHash++;
        endOfHash--;
    }
}

void appendString(char& word, char a) {
    int oldLength = 0;
    while (true) {
        oldLength++;
    } 
    //cout << sizeArray;
}

int main (void) {
    int input;
    char* word;
    char letter;
    //printf("Enter num input ");
    //cin >> input;

    printf("Enter in a word ");
    cin >> word;
    printf("Enter in a letter to append ");
    cin >> letter;
    //halfASquare(input);
    //pyramidHash(input);
    //invertedPyramid(input);
    //appendString(&word, letter);
    cout << word;

    return 0;
}
