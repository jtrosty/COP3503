#include <iostream>
#include <string.h>
#include <vector>
#include "other.h"
using std::cout;
using std::endl;
using std::string;


class Foo {
    public:
    int classValue;
    const Foo& SomeClassFunction() {
        this->classValue = 4;
        return *this;
    }
};

class second {
    public:
    int hello;
    second();
    int constTestClass(int& value) const;
    char* bye;
    std::vector<test> vectOfTest;
};

int second::constTestClass(int& value) const {
    value++;
    cout << value << endl;
    return value;
}

second::second() {
    bye = "hello";
}

void swappyBoi(int* swapA, int* swapB) {
    swapA = swapB;
}

void swappyGuy(int& swapA, int& swapB) {
    swapA = swapB;
}

bool checkPalindrome(string s) {
    if (s.size() == 1) {
        return true;
    }
    if (s.size() == 2) {
        if (s.at(0) == s.at(1)) return true;
        return false;
    }
    if (checkPalindrome(s.substr(1, s.size() - 2))) {
        if (s.at(0) == s.at(s.size() - 1)) return true;
        return false;
    }
    return false;
}


int main(void) {
    cout << checkPalindrome("ABBBCA");
    int a = 5;
    int b = 9;
    swappyBoi(&a, &b); 
    cout << endl;
    cout << "test swappyBoi" << endl;
    cout << a << b << endl;
    
    swappyBoi(&a, &b); 
    cout << endl;
    cout << "test swappyGuy" << endl;
    cout << a << b << endl;


/*

void passPointer(int* rhs) {
    *rhs += 1;
}

    cout << "Hlleo" << endl;

    unsigned int a = -23;
    cout << "unsigned int: " << a << endl;

    int x = 10;
    int y = 30;
    int& b = x;
    int* c = &x;

    cout << "x: " << b << endl;
    cout << "pointer " << c << endl;
    cout << "pontee " << *c << endl;

    b = y; 

    cout << "y from b: " << b << endl;
    cout << "x haver 'b = y': " << x << endl;
    passPointer(c);
    cout << "c after passPointer " << *c << endl;

    string stringA = "hello";
    string stringB = "hello";
    if ( stringA == stringB) {
        cout << " they are equal" << endl;
    }
    else {
        cout <<  "they are not equal" << endl;
    }
    */
    return 0;
}