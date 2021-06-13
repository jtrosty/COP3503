#include <iostream>
#include <vector>
#include <stdexcept>
using std::vector;
using std::cout;
using std::endl;
#include "leaker.h"

template<typename T>
class LinkedList {
int nodeCounter;

    public:
        //template<typename T>
        struct Node {
            T data;
            Node* next;
            Node* prev;
        };
        Node* head;
        Node* tail;
        
        // Insertions
        void AddHead(T _data);
        void AddTail(T _data);
        void AddNodesHead(const T* _data, unsigned int _count);
        void AddNodesTail(const T* _data, unsigned int _count);

        // Accessors
        Node* Head();
        const Node* Head() const;
        Node* Tail();
        const Node* Tail() const;
        Node* GetNode(unsigned int index);
        const Node* GetNode(unsigned int index) const;
        Node* Find(const T& data);
        const Node* Find(const T& data) const;
        void FindAll(vector<Node*>& outData, const T& value) const;

        /*==== Behaviors ======*/
        void PrintForward() const;
        void PrintReverse() const;

        int NodeCount();

        //Constructors
        LinkedList();
        LinkedList(T _data);
        // Copy Constructor
        LinkedList(LinkedList& other);
        LinkedList(const LinkedList& other);
        LinkedList& operator=(const LinkedList& other);
        void copyHelper(const LinkedList& other);
        // Destructor
        ~LinkedList();
};

// #####################################################
// ########## Constructors Destructors #################
// #####################################################

// Default Constructor
template<typename T>
LinkedList<T>::LinkedList() {
    head = new Node();
    head->next = nullptr;
    head->prev = nullptr;
    tail = head;

    nodeCounter = 0;
}
// Copy Constructor 
template<typename T>
LinkedList<T>::LinkedList(const LinkedList& other) {
    copyHelper(other);
}

// Copy Assignment Opeartors
template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
    copyHelper(other);
    return *this;
}

// Copy Assit array
template<typename T>
void LinkedList<T>::copyHelper(const LinkedList& other) {
    head = other.head;
    nodeCounter = other.nodeCounter;
    Node* temp = other.head->next;
    while(temp != nullptr) {
        Node* newNode = new Node();
        newNode->prev = temp->prev;
        newNode->next = temp->next;
        temp = temp->next;
    }
}

// Destructor
template<typename T>
LinkedList<T>::~LinkedList() {
    Node* temp = head;
    while(temp != nullptr) {
        Node* next = temp->next;
        delete temp;
        temp = next;
    }
}

// #####################################################
// ############## Insertion Operations #################
// #####################################################

// Add a head to the Linked list
template<typename T>
void LinkedList<T>::AddHead(T _data) {
    // A new node is not needed becasue the constructor made it
    if (nodeCounter == 0) {
        head->data = _data;
        head->data = _data;
    }
    else {
        //  A new node must be created
        Node* newNode = new Node;
        // When the first node is made, the tail is assigned the pointer to the first node.
        if (nodeCounter == 0) {
            tail = newNode;
        }
        // Assign data to new node
        newNode->data = _data;
        newNode->next = head;
        // Link the oldHead to the new head
        head->prev = newNode;
        //Transfer the crown 
        head = newNode; 
    }
    nodeCounter++;
}

// Executes the add head for all arrays. 
template <typename T>
void LinkedList<T>::AddNodesHead(const T* _data, unsigned int _count) {
    for (int i = _count - 1; i >= 0; i--)
        AddHead(_data[i]);
}

template <typename T> 
void LinkedList<T>::AddTail(T _data) {
    // A new node is not needed becasue the constructor made it
    if (nodeCounter == 0) {
        tail->data = _data;
        head->data = _data;
    }
    else {
        //  A new node must be created
        Node* newNode = new Node;
        if (nodeCounter == 0) 
            head = newNode;

        newNode->data = _data;
        newNode->prev = tail;
        newNode->next = nullptr;
        tail->next = newNode;
        tail = newNode;
    }
    nodeCounter++;
}

template <typename T> 
void LinkedList<T>::AddNodesTail(const T* _data, unsigned int _count) {
    for (unsigned int i = 0; i < _count; i++) 
        AddTail(_data[i]);
}

// #####################################################
// ################ Behaviors ##########################
// #####################################################

// Print data from front to back
template <typename T>
void LinkedList<T>::PrintForward() const {
    Node* temp = head;
    // TODO cout << "head " << head << endl;
    while(temp->next != nullptr) {
        cout << temp->data << endl;
        temp = temp->next;
    }
    cout << temp->data << endl;
}
// Print data from back to front
template<typename T>
void LinkedList<T>::PrintReverse() const {
    Node* temp = tail;
    while(temp->prev != nullptr) {
        cout << temp->data << endl;
        temp = temp->prev;
    }
    cout << temp->data << endl;
}

// #####################################################
// ################ Accessors ##########################
// #####################################################

// Returns the number of nodes
template<typename T> 
int LinkedList<T>::NodeCount() {
    return nodeCounter; 
}

// Find
template<typename T>
LinkedList<T>::Node* LinkedList<T>::Find(const T& _data) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == _data) {
            return temp;
        }
    }
    return nullptr;
}

// CONSTANT Find
template<typename T>
const LinkedList<T>::Node* LinkedList<T>::Find(const T& _data) const {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == _data) {
            return temp;
        }
    }
    return nullptr;
}

// Find All
template<typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == value) {
            outData.add(temp); 
        }
    }
}

// Return head
template<typename T>
LinkedList<T>::Node* LinkedList<T>::Head() {
    return head;
}

// Return Head Constant
template<typename T>
const LinkedList<T>::Node* LinkedList<T>::Head() const {
    return head;
}

// Return Tail
template<typename T>
LinkedList<T>::Node* LinkedList<T>::Tail() {
    return tail;
}

// Return Tail Constant
template<typename T>
const LinkedList<T>::Node* LinkedList<T>::Tail() const {
    return tail;
}

// Get Node
template<typename T> 
LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {
    if (index > nodeCounter) {
        throw out_of_range();
    }
    Node* temp = head;
    for (unsigned int = 0; i = index; i++) {
        temp = temp->next;
    }
    return temp;
}

// Get Node Constant
template<typename T> 
const LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {
    if (index > nodeCounter) {
        throw out_of_range();
    }
    Node* temp = head;
    for (unsigned int = 0; i = index; i++) {
        temp = temp->next;
    }
    return temp;
}