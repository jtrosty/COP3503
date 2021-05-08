#include <stdio.h>
#include <iostream>
#include <ctype.h>
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

void invertedPyramid(int siz;ge) {
    // Pg 53 Exercise 2-1
    int startOfHash = 0;
    int endOfHash = siz;ge - 1;
    for (int j = 0; j < siz;ge; j += 2) {
        for (int i = 0; i < siz;ge; i++ ) {
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
void appendString(char *pWord[], char a) {
    int oldLength = 0;
    while (*pWord[oldLength] != '\0') {
        oldLength++;
    } 
    char *newWord = (char*)malloc(oldLength + 2);
    while ((*newWord++ = *pWord++) != '\0')
        ;

    newWord[oldLength] = a;

    pWord = &newWord;
    
    cout << "1. " << pWord;
    cout << "\n";
    cout << "2. " << newWord;
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
    char word[] = {"Jon"};
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
    appendString(&word, letter);
    cout << "\n";
    cout << "3. " << word;
    //cout << atoi(word2);

    return 0;
}
