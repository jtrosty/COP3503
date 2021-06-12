#include <iostream>
#include "LinkedList.h"
using std::endl;
using std::cout;
#include "leaker.h"

int main() {
    LinkedList<int> intList; 
    int number = 6;
    int testInt[] = {22, 23, 24, 25, 26};
    int testCount = ((sizeof(testInt))/sizeof(testInt[0]));

    for (int i = 0; i < number; i++) {
        intList.AddTail(i);
    }
    cout << "node count: " << intList.NodeCount() << endl;
    intList.AddNodesTail(testInt, testCount);
    cout << "node count: " << intList.NodeCount() << endl;
    intList.PrintForward();
    intList.PrintReverse();

    return 0;
}
