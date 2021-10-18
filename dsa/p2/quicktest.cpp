#include <iostream>

int main()
{
    int a = 0;
    int& ref = a;
    ref = 1;
    std::cout << a << ref;
    return 0;
}