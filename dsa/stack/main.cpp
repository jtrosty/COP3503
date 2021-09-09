#include "stack.h" 
#include <iostream>
#include <stack>
#include <queue>
#include <list>
#include <vector>
#include <algorithm>
#include "CircularArrayQueue.h"
using std::sort;
using std::cout;
using std::endl;
using std::stack;
using std::queue;
using std::vector;

bool inLanguage(char* theString); // Used in stack question
bool checkValidity(queue<int> q);
/*
vector<int> twoSum(vector<int>& nums, int target) {
    vector<int> result;
    int size = nums.size();
    int complement;
    for (int i = 0; i < size; i++) {
        complement = target - nums.at(i);
        for (int j = i + 1; j < size; j++) { 
            if (nums.at(j) == complement){
                result.push_back(j);
                result.push_back(i);
                return result;
            }
        }
    }
}
*/

int findInList(std::list<int>& myList, int valueToFind) {
    std::list<int>::iterator iter;
    int index = 0;
    for (iter = myList.begin(); iter != myList.end(); iter++, index++) {
        if (*iter == valueToFind) return index;
    }
    return -1;
}

int main(void) {
    std::list<int> myList;
    myList.push_front(4);
    myList.push_front(3);
    myList.push_front(2);
    myList.push_front(1);
    cout << "Resut; " << findInList(myList, 0) << endl;
    
    cout << "##################################################" << endl;
    CircularArrayQueue test1;
    test1.enqueue(23);
    cout << "peek: " << test1.peekFront() << endl;
    cout << "empty:: " << test1.isEmpty() << endl;
    test1.dequeue();
    cout << "peek: " << test1.peekFront() << endl;
    cout << "empty:: " << test1.isEmpty() << endl;
    
    return 0;
}

bool checkValidity(queue<int> q) {
    // Return true if quese is empty. 
    int last;
    int sizeOfQueue = q.size();
    if (q.empty()) return true;
    else if (sizeOfQueue == 1) return true;
    do {
        last = q.front();
        q.pop();
        if (q.empty()) break;
        if (last > q.front()) return false;
    } while (!q.empty());

    return true;
}

bool inLanguage(char* theString) {
    stack<char> charStack;
    int length = 0;
    int isEqual = 0;
    char value = 0;

    // Determine Length of theString
    while (theString[length] != '\0') {
        charStack.push(theString[length]);
        length++;
    }
    // If the length is odd, the item fails
    if ((length % 2) == 1) return false;
    // Pop stack peeking at each item and add up the number of As and Bs
    while (!charStack.empty()) {
        value = charStack.top();
        charStack.pop();
        if (value == 'A') isEqual++;
        else if (value == 'B') isEqual--;
        else return false;
    }
    if (isEqual == 0) return true;
    else return false;
}