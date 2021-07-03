#include <iostream>
using std::cout;
using std::endl;


void passPointer(int* rhs) {
    *rhs += 1;
}

int main(void) {
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

    return 0;
}