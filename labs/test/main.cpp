#include <iostream>
#include <string.h>
#include <vector>
#include "other.h"
//using std::vector;
using std::cout;
using std::endl;
using std::string;

class second {
    public:
    second();
    char* bye;
    std::vector<test> vectOfTest;
};



second::second() {
    bye = "hello";
}
int main(void) {
    test myClass;
    second otherClass;
    // See if I can check if the class objects are equal
    
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