#include <iostream>
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
        
        void AddHead(T _data);
        void AddTail(T _data);
        void AddNodesHead(const T* _data, unsigned int _count);
        void AddNodesTail(const T* _data, unsigned int _count);

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

    tail = new Node();
    tail->next = nullptr;
    tail->prev = nullptr;

    nodeCounter = 0;
}

/*
template<typename T>
LinkedList<T>::LinkedList(T _data) {
    head = new Node(_data);
    head->next = nullptr;
    head->data = _data;
    nodeCounter = 1;
}
*/

// Copy Constructor 
/*
template<typename T>
LinkedList<T>::LinkedList(const LinkedList& other) {
    Node temp;
    head = other.head;
    
    while(->next != nullptr) {
        cout << head.data << endl;
    }
    head.data = other.head.data;
    nodeCounter = other.nodeCounter;
}
*/
/*
// Copy Assignment Operator 
template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
    head = other.head;
    while(->next != nullptr) {
        cout << head.data << endl;
    }
    head.data = other.head.data;
    nodeCounter = other.nodeCounter;
    return *this;
}
*/
template<typename T>
LinkedList<T>::~LinkedList() {
    Node* temp = head;
    delete head;
    while(temp != nullptr) {
        delete temp->next;
        delete temp->prev;
        temp = temp->next;
    }
    delete tail;
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
        tail = newNode;
    }
    nodeCounter++;
}

template <typename T> 
void LinkedList<T>::AddNodesTail(const T* _data, unsigned int _count) {
    for (int i = 0; i < _count; i++) 
        AddTail(_data[i]);
}

// #####################################################
// ################ Behaviors ##########################
// #####################################################

// Print data from front to back
template <typename T>
void LinkedList<T>::PrintForward() const {
    Node* temp = head;
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

// Returns the number of nodes
template<typename T> 
int LinkedList<T>::NodeCount() {
    return nodeCounter; 
}
