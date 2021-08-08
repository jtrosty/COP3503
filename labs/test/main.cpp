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
    *swapA = *swapB;
    *swapB = *swapA;
    cout << swapA << " " << swapB << endl;
}


int main(void) {
    int a = 10;
    int b = 20;
    swappyBoi(&a, &b);
    cout << a << " " << b << endl;

    Foo foo;
    cout << foo.SomeClassFunction().classValue << endl;
    auto var = 1;
    test myClass;
    second otherClass;
    otherClass.hello = 2;
    // See if I can check if the class objects are equal
    int test = 300;
    cout << "cout of the thign: " << otherClass.constTestClass(otherClass.hello) << endl;
    cout << otherClass.hello << endl;
    
    // See if the char* are equal
    if ( myClass.hello == otherClass.bye) {
        cout << " they are equal" << endl;
    }
    else {
        cout <<  "they are not equal" << endl;
    }
    


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