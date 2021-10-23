#include <iostream>

class HashTable {
    public:
        struct Node {
            int data;
            Node* next;
            Node() : data(0xf0000000), next(nullptr) {}
            Node(int value) : data(value), next(nullptr) {}
            Node& operator=(Node& node) {
                this->data = node.data;
                this->next = node.next;
                return *this;
            }
        };

        HashTable();
        ~HashTable();
        HashTable& operator=(HashTable& hash);

        void insert(int data); 
        char remove(int data); 
        void print();

        char traverse(int keyToSearch);

    private:
        int size;
        Node** table;

        void rehash();
        int getHashIndex(int key);

};

///////////////////////////////////////////////////////
//             Constructors and Destructors

HashTable::HashTable() {
    size = 10;
    table = new Node*[size];
    for (int i = 0; i < size; i++) {
        table[i] = nullptr;
    }
}

HashTable::~HashTable() {
    for (int i = 0; i < size; i++) {
        Node* prev;
        prev = table[i];
        if (table[i] != nullptr) {
            Node* next = prev->next;
            delete prev;
            prev = next;
            next = next->next;
        }
    }
    delete[] table;
}

///////////////////////////////////////////////////////
//             Overloaded Operator
HashTable& HashTable::operator=(HashTable& hashTable) {

}

///////////////////////////////////////////////////////
//             Insert

int HashTable::getHashIndex(int key) {
    return key % size;
}

void HashTable::insert(int data) {
    int key = getHashIndex(data);
    if (table[key] == nullptr) {
        table[key]->data = data;
    }
    else {
        int counter = 0;
        Node* temp = table[key];
        Node* newNode = new Node(data);
        while (temp != nullptr) {
            temp = temp->next;
            counter++;
        }
        temp = newNode;
        if (counter > 10) rehash();
    }
}
void HashTable::rehash() {
    int newSize = size * 4;
    Node** newTable = new Node*[newSize];
    for (int i = 0; i < newSize; i++) {
        newTable[i] = nullptr;
    }
    int oldSize = size;

    Node** oldTable = table;
    table = newTable;
    size = newSize;

    for (int i = 0; i < oldSize; i++) {
        if (oldTable[i] == nullptr) {}
        else {
            Node* temp = oldTable[i];
            Node* newTableTemp;
            // Traverse through old hash table
            while (temp != nullptr) {
                int key = getHashIndex(temp->data);
                if (table[key] == nullptr) table[key] = temp;
                else {
                    newTableTemp = table[key];
                    while (newTableTemp != nullptr) 
                        { newTableTemp = newTableTemp->next; }
                    newTableTemp = temp;
                }
                table[getHashIndex(temp->data)] = temp;
                temp->next;
            } 
        } 
    }
    delete[] oldTable;
}

///////////////////////////////////////////////////////
//             Remove
char HashTable::remove(int data) {
    int key = getHashIndex(data);
    Node* prev = nullptr;
    Node* temp = table[key];
    while (temp != nullptr) {
        if (temp->data == data) {
            if (prev == nullptr) table[key] = temp->next;
            else                 prev->next = temp->next;
            delete temp;
        }
        prev = temp;
        temp = temp->next;
    }
} 

///////////////////////////////////////////////////////
//             Traverse
char HashTable::traverse(int keyToSearch) {
    for(int i = 0; i < size; i++) {
        Node* temp = table[i];
        while (temp != nullptr) {
            if (temp->data == keyToSearch) return 1;
            temp = temp->next;
        }
    }
    return 0;
}

///////////////////////////////////////////////////////
//             Print
void HashTable::print() {
    for(int i = 0; i < size; i++) {
        Node* temp = table[i];
        while (temp != nullptr) {
            std::cout << temp->data << ", ";
        }
        std::cout << std::endl;
    }
}