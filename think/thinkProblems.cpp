#include <iostream>
#include <ctype.h>
#include <stdlib.h>
using namespace std;
// This is a test of the push
//
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
void swapChar(char *v, int i, int j) {
    char tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
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

// Modify word[] to have another letter
 char* appendString(char *pWord, char a) {
    // find length of string
    int length = 0;
    while (pWord[length] != '\0') {
        length++;
    }
    //cout << "length: " << length;
    char* result = new char[length + 1];
    for (int i = 0; i < length; i++) {
        result[i] = pWord[i];
    } 
    result[length] = a;
    result[length + 1] = '\0';
    //cout << "append String function: " << result;
    return result;
}

/* This concantenates b onto a, a is made longer. */
char* concantenate(char *a, char *b) {
    int lengthA = 0;
    int lengthB = 0;
    while (a[lengthA] != '\0') {
        lengthA++;
    }
    while (b[lengthB] != '\0') {
        lengthB++;
    }
    char* result = new char[lengthA + lengthB + 1];
    
    for(int i = 0; i < lengthA; i++) {
        result[i] = a[i];
    }
    for(int j = 0; j < lengthB; j++) {
        result[lengthA + j] = b[j];
    }
    result[lengthA + lengthB] = '\0';
    //cout << "\n concantenate function: " << result;
    return result;
}

/* Atoi: convert s to integer; version 2 */
int atoi(char s[]) {
    int i , n , sign;

    for (i = 0; isspace(s[i]); i++)  /*skips white space */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')  /* Skip sign */
        i++;
    for (n = 0; isdigit(s[i]); i ++) 
        n = 10 * n + (s[i] - '0');
    return sign * n;

}

/* shellsort: sort v[0]...v[n-1] into increasing order */
void shellsort(int v[], int n) {
    int gap, i, j, temp;

    for( gap = n/2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i++) {
            for (j = i - gap; j >= 0 && v[j] > v [j + gap]; j -= gap) {
                temp = v[j];
                v[j] = v[j + gap];
                v[j + gap] = temp;
            }
        }
    }
}

int main (void) {
    int input;
    char word[] = {"link"};
    char name[] = {"zelda"};
    char* lastName;
    // lastName = "triforce";
    char letter = 'j';
    //printf("Enter num input ");
    //cin >> input;
    char word2[] = {"-782"};

    /* printf("Enter in a word ");
    cin >> word;
    printf("Enter in a letter to append ");
    cin >> letter;
    */

    //halfASquare(input);
    //pyramidHash(input);
    //invertedPyramid(input);
    //appendString(&word, letter);
    //appendString(&word, letter);
    //swapChar(word, 0, 1);
    cout << "\n";
    cout << "Append: " << appendString(word, letter) << "\n";
    cout << "concantenate: "<< concantenate(word, name) << "\n";
    cout << "You successfully complied with g++";

    int userNum = 0;
    int userNum2 = 0;  

    cout << "Enter integer:" << endl;
    cin >> userNum;

    cout << "You entered: " << userNum << endl;
    cout << userNum << " squared is " << userNum * userNum << endl;
    cout << "And " << userNum << " cubed is " << userNum * userNum * userNum << "!!" << endl;

    cout << "Enter another integer: " << endl;
    cin >> userNum2;
    cout << userNum << " + " << userNum2 << " is " << (userNum + userNum2) << endl;
    cout << userNum << " * " << userNum2 << " is " << (userNum * userNum2) << endl;

    return 0;
}
