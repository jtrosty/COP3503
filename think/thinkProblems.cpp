#include <stdio.h>
#include <iostream>
using std::cin;
using std::cout;

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

int main (void) {
    int input;
    printf("Enter num input ");
    cin >> input;

    //halfASquare(input);
    pyramidHash(input);

    return 0;
}
