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
        void deleteHashTable(Node** oldTable);
        HashTable& operator=(HashTable& hash);

        void insert(int data); 
        void insert(Node* node); 
        char remove(int data); 
        char removeAll(); 
        void print();
        char isEmpty();

        char traverse(int keyToSearch);

    private:
        int capacity;
        int size;
        Node** table;
        enum Resize { bigger, smaller};

        void rehash(Resize choice, int factor);
        int getHashIndex(int key);

};

///////////////////////////////////////////////////////
//             Constructors and Destructors

HashTable::HashTable() {
    capacity = 10;
    size = 0;
    table = new Node*[capacity];
    for (int i = 0; i < capacity; i++) {
        table[i] = nullptr;
    }
}

HashTable::~HashTable() {
    deleteHashTable(table);
}

void HashTable::deleteHashTable(Node** oldTable) {
    for (int i = 0; i < capacity; i++) {
        Node* prev;
        prev = oldTable[i];
        if (oldTable[i] != nullptr) {
            Node* next = prev->next;
            delete prev;
            while (next != nullptr) {
                prev = next;
                next = next->next;
                delete prev;
            }
        }
    }
    delete[] oldTable;
}

///////////////////////////////////////////////////////
//             Overloaded Operator
HashTable& HashTable::operator=(HashTable& hashTable) {

}

///////////////////////////////////////////////////////
//             Insert

int HashTable::getHashIndex(int key) {
    return key % capacity;
}

void HashTable::insert(int data) {
    int key = getHashIndex(data);
    if (table[key] == nullptr) {
        Node* newNode = new Node(data);
        table[key] = newNode;
    }
    else {
        int counter = 0;
        Node* temp = table[key];
        Node* newNode = new Node(data);
        while (temp->next != nullptr) {
            temp = temp->next;
            counter++;
        }
        temp->next = newNode;
        if (counter > 4) rehash(bigger, 4);
    }
    size++;
}

/***** NOT USED ***********/
void HashTable::insert(Node* node) {
    int key = getHashIndex(node->data);
    if (table[key] == nullptr) {
        table[key] = node;
    }
    else {
        int counter = 0;
        Node* temp = table[key];
        while (temp->next != nullptr) {
            temp = temp->next;
            counter++;
        }
        temp->next = node;
    }
}

///////////////////////////////////////////////////////
//             Rehash

void HashTable::rehash(Resize choice, int factor) {
    int newCapacity;
    if (choice == bigger) newCapacity = capacity * factor; 
    else newCapacity = capacity / factor;

    Node** newTable = new Node*[newCapacity];
    for (int i = 0; i < newCapacity; i++) {
        newTable[i] = nullptr;
        size = 0;
    }
    int oldCapacity = capacity;

    Node** oldTable = table;
    table = newTable;
    capacity = newCapacity;

    for(int i = 0; i < oldCapacity; i++) {
        Node* temp = oldTable[i];
        while (temp != nullptr) {
            insert(temp->data);
            temp = temp->next;
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
            size--;
            if ((size < (capacity / 4)) && size > 5) rehash(smaller, 2);
            return 1;
        }
        prev = temp;
        temp = temp->next;
    }
    return 0;
} 

char HashTable::removeAll() {
    int initialSize = size;
    for (int i = 0; i < initialSize; i++) remove(i);
}

///////////////////////////////////////////////////////
//             Traverse
char HashTable::traverse(int keyToSearch) {
    for(int i = 0; i < capacity; i++) {
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
    int counter = 0;
    for(int i = 0; i < capacity; i++) {
        Node* temp = table[i];
        while (temp != nullptr) {
            std::cout << temp->data << ", ";
            counter++;
            temp = temp->next;
        }
    }
    std::cout << std::endl << "total size " << size << " counter " << counter << std::endl;
}

///////////////////////////////////////////////////////
//           is  Empty
char HashTable::isEmpty() {
    if (size <= 0) return 1;
    else return 0;
}