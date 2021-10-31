#include <iostream>
#include <string>
#include <map>
#include <stack>
using namespace std;
/*
0
1
true
1
0
false
Commencing stress test...
10000
10000
0
*/
string findTheDigits(string x, string y); 
map<int,stack<string>> createMap(string arr[], int len);
bool isPresent(map<int,stack<string>> obj, string value);

//////////////////////////////////////////////////////////////
//         Set and Maps 10.2.1 Implement an unordered set

class unorderedSet {
private:
    int numOfElements;
    int capacity;
    enum resize {bigger, smaller};

    struct Node {
        int data;
        Node* next;
        Node(int value) { data = value; next = nullptr;}
    };

    int getHashKey(int val) {
        return val % capacity;
    }

    Node** table;

public:
    unorderedSet() {
        numOfElements = 0;
        capacity = 10;
        table = new Node*[capacity];
        for (int i = 0; i < capacity; i++) table[i] = nullptr;
    }

    void insert(int val) {
        if (search(val) != nullptr) return;
        int key = getHashKey(val);
        Node* newNode = new Node(val);
        numOfElements++;
        if (table[key] == nullptr) {
            table[key] = newNode;
        }
        else {
            Node* temp = table[key];
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        if (numOfElements > capacity ) rehash(bigger);
    }

    Node* search(int val) {
        int key = getHashKey(val);
        if (table[key] == nullptr) return nullptr;
        Node* temp = table[key];
        while (temp != nullptr) {
            if (temp->data == val) return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    bool has(int val) {
        return (search(val) != nullptr);
    }

    void rem(int val) {
        int key = getHashKey(val);
        Node* prev = nullptr;
        Node* temp = table[key];
        while (temp != nullptr) {
            if (temp->data == val) {
                if (prev == nullptr) table[key] = temp->next;
                else                prev->next = temp->next;
                delete temp;
                numOfElements--;
                return;
            }
            prev = temp;
            temp = temp->next;
        }
        if ((numOfElements < (capacity / 4)) && capacity > 10) rehash(smaller);
    }

    int size() {
        return numOfElements;
    }

    void rehash(resize direction) {
        Node** oldTable = table;
        int oldCapacity = capacity;
        int oldSize = numOfElements;
        numOfElements = 0;
        if (direction == bigger) {
            capacity = 2 * capacity;
            Node** newTable = new Node*[capacity];
            table = newTable;
        }
        else if (direction == smaller) {
            capacity = capacity / 2 ;
            Node** newTable = new Node*[capacity];
            table = newTable;
        }
        for (int i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }

        // Fill in new hash table
        Node* temp;
        for (int i = 0; i < oldCapacity; i++) {
            temp = oldTable[i];
            while (temp != nullptr) {
                insert(temp->data);
                temp = temp->next;
            }
        }
        // Delete data for old table
        for (int i = 0; i < oldCapacity; i++) {
            if (oldTable[i] == nullptr) {}
            else {
                Node* temp = oldTable[i];
                Node* prev;
                while (temp != nullptr) {
                    prev = temp;
                    temp = temp->next;
                    delete prev;
                }
            }
        }
        delete[] oldTable;
    }
};

//////////////////////////////////////////////////////////////
//                 Main 

int main(void) {
    unorderedSet test;
    int num = 20;
    for (int i = 0; i < num; i++) {
        test.insert(i);
    }
    cout << test.has(66666) << endl;
    cout << test.size() << endl;;
    for (int i = 0; i < num; i++) {
        test.rem(i);
    }
    cout << "empty " << test.size() << endl;
    return 0;
}


//////////////////////////////////////////////////////////////
//               Set and Maps 10.1.1 Map of Names

// Main test cases
/*
    string cases[] = {"Apple", "Microsoft", "Google", "Facebook", "Netflix", "Rat", "Maple", ""};
    int num = 7;
    map<int, stack<string>> tset = createMap(cases, num);
    cout << isPresent(tset, "") << endl;
    //cout << isPresent(tset, "Jon") << endl;
    //cout << isPresent(tset, "Apple") << endl;
    //cout << isPresent(tset, "Neftlix") << endl;
    //cout << isPresent(tset, "Neftlix") << endl;
    */
map<int,stack<string>> createMap(string arr[], int len)
{
    int length;

    map<int, stack <string>> result;
    for (int i = 0; i < len; i++) {
        length = arr[i].size();
        if (result.find(length) == result.end()) {
            stack <string> newStack;
            newStack.push(arr[i]);
            result.emplace(length, newStack);
        }
        else {
            result.at(length).push(arr[i]);
        }
    }
    return result;
}

bool isPresent(map<int,stack<string>> obj, string value)
{
    //your code here
    int length = value.size();
    if (obj.find(length) == obj.end()) return false;
    while (!obj.at(length).empty()) {
        if (obj.at(length).top() == value) return true;
        else                               obj.at(length).pop();
    }
    return false;
}
//////////////////////////////////////////////////////////////
//            Sets and Maps 10.2.5      

string findTheDigits(string x, string y) {
	// Write your code here
    map<char, int> additionalDigits;
    map<char, int>::iterator iter;

    char ASCII0 = 48;
    for (char i = ASCII0; i <= ASCII0 + 9; i++) {
        additionalDigits.emplace(i, 0);
    }

    for (int i = 0; i < y.size(); i++) {
        additionalDigits.at(y.at(i))++;
    }

    for (int i = 0; i < x.size(); i++) {
        additionalDigits.at(x.at(i))--;
    }

    string result;

    for (iter = additionalDigits.begin(); iter != additionalDigits.end(); iter++) {
        for (int i = 0; i < iter->second; i++) result.push_back(iter->first);
    }
    
	return result;
}