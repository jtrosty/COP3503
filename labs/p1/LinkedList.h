#include <iostream>
#include <vector>
#include <stdexcept>
#include <stdbool.h>
using std::vector;
using std::cout;
using std::endl;
#include "leaker.h"

template<typename T>
class LinkedList {
unsigned int nodeCounter;

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
        void InsertAfter(Node* node, const T& data);
        void InsertBefore(Node* node, const T& data);
        void InsertAt(const T& data, unsigned int index);
        
        // Removal
        bool RemoveHead();
        bool RemoveTail();
        unsigned int Remove(const T& data);
        bool RemoveAt(unsigned int index);
        void Clear();

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
        void PrintForwardRecursive(const Node* node) const;
        void PrintReverseRecursive(const Node* node) const;

        int NodeCount();

        //Constructors
        LinkedList();
        void createFirstNode();
        //LinkedList(T _data);
        // Copy Constructor
        // LinkedList(const LinkedList<T>& other);
        LinkedList(const LinkedList<T>& other);
        // Overloaded Operators
        LinkedList<T>& operator=(const LinkedList<T>& other);
        bool operator==(const LinkedList<T>& rhs);
        T& operator[](unsigned int index);
        const T& operator[](unsigned int index) const;
        void copyHelper(const LinkedList<T>& other);
        // Destructor
        ~LinkedList();
};

// #####################################################
// ########## Constructors Destructors #################
// #####################################################

// Default Constructor
template<typename T>
LinkedList<T>::LinkedList() {
    head = nullptr; 
    tail = nullptr;
    nodeCounter = 0;
}

// TODO destory?
// Constructor first node helper
template<typename T>
void LinkedList<T>::createFirstNode() {
    head = new Node();
    head->next = nullptr;
    head->prev = nullptr;
    tail = head;

    nodeCounter = 0;
}

// Copy Constructor 
template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) {
    copyHelper(other);
}

// Copy Assignment Opeartors
template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
    copyHelper(other);
    return *this;
}

// Copy Assignment Opeartors
template<typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) {
    Node* tempThis = this->head;
    Node* tempRhs = rhs.head;
    if (rhs.nodeCounter != this->nodeCounter)
        return false;
    while (tempThis != nullptr) {
        if (tempThis->data != tempRhs->data) 
            return false;
        tempThis = tempThis->next;
        tempRhs = tempRhs->next;
    }
    return true;
}

// Copy Assit array
template<typename T>
void LinkedList<T>::copyHelper(const LinkedList& other) {
    head = nullptr; 
    tail = nullptr;
    nodeCounter = 0;

    Node* temp = other.head;
    while (temp != nullptr) {
        this->AddTail(temp->data);
        temp = temp->next;
    }

    // TODO delte this stuff
    /*
    this->head = new Node();
    this->head->prev = nullptr;
    this->head->data = other.head.data;
    this->nodeCounter = other.nodeCounter;
    Node* temp = other.head->next;
    while(temp != nullptr) {
        Node* newNode = new Node();
        newNode->data = temp->data;
        newNode->prev = temp->prev;
        newNode->next = temp->next;
        if (temp->next == nullptr) {
            this->tail = other.tail;
        }
        temp = temp->next;
    }
    */
}

// Destructor
template<typename T>
LinkedList<T>::~LinkedList() {
    Node* temp = this->head;
    /*
    while(temp != nullptr) {
        Node* next = temp->next;
        delete temp;
        temp = next;
    }
    */
    while(temp != nullptr) {
        delete temp;
        temp = temp->next;
    }
    //delete head;
    //delete tail;
}

// #####################################################
// ############## Insertion Operations #################
// #####################################################

// Add a head to the Linked list
template<typename T>
void LinkedList<T>::AddHead(T _data) {
    // A new node is not needed becasue the constructor made it
    if (nodeCounter == 0) {
        head = new Node;
        head->data = _data;
        tail = head;
        head->next = nullptr;
        head->prev = nullptr;
        tail->next = nullptr;
        tail->prev = nullptr;
    }
    else {
        //  A new node must be created
        Node* newNode = new Node;
        // Assign data to new node
        newNode->data = _data;
        newNode->next = head;
        newNode->prev = nullptr;
        head->prev = newNode;
        head = newNode; 
    }
    nodeCounter++;
}

template <typename T> 
void LinkedList<T>::AddTail(T _data) {
    // A new node is not needed becasue the constructor made it
    if (nodeCounter == 0) {
        tail = new Node;
        tail->data = _data;
        head = tail;
        head->next = nullptr;
        head->prev = nullptr;
        tail->next = nullptr;
        tail->prev = nullptr;
    }
    else {
        //  A new node must be created
        Node* newNode = new Node;

        newNode->data = _data;
        newNode->prev = tail;
        newNode->next = nullptr;
        tail->next = newNode;
        tail = newNode;
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
void LinkedList<T>::AddNodesTail(const T* _data, unsigned int _count) {
    for (unsigned int i = 0; i < _count; i++) 
        AddTail(_data[i]);
}

template <typename T>
void LinkedList<T>::InsertAfter(Node* _node, const T& _data) {
    Node* newNode = new Node();
    // setup new node
    newNode->data = _data;
    newNode->next = _node->next;
    newNode->prev = _node;
    // setup nodes on either side of newNode
    _node->next->prev = newNode;
    _node->next = newNode;
    nodeCounter++;
}

template <typename T>
void LinkedList<T>::InsertBefore(Node* _node, const T& _data) {
    Node* newNode = new Node();
    // Setup new node
    newNode->data = _data;
    newNode->next = _node;
    newNode->prev = _node->prev;
    // Setup nodes on either side of new node
    _node->prev->next = newNode;
    _node->prev = newNode;
    nodeCounter++;
}

template<typename T> 
void LinkedList<T>::InsertAt(const T& _data, unsigned int _index) {
    if (_index > nodeCounter || _index < 0) {
        throw std::out_of_range("That request is out of Array range.");
    }
    else if ( _index == 0) {
        this->AddHead(_data);
    }
    else if (_index == (nodeCounter)) {
        this->AddTail(_data);
    }
    else {
        Node* temp = head;
        for (unsigned int i = 1; i < _index; ++i) {
            temp = temp->next;
        }
        InsertAfter(temp, _data);
    }
}

// #####################################################
// ################ Removal Operations #################
// #####################################################
template <typename T>
bool LinkedList<T>::RemoveHead() {
    if (nodeCounter > 0) {
        Node* temp = head;
        temp = head->next;
        temp->prev = nullptr;
        delete head;
        head = temp;
        nodeCounter--;
        return true;
    }
    return false;
}

template <typename T>
bool LinkedList<T>::RemoveTail() {
    if (nodeCounter > 0) {
        Node* temp = tail;
        temp = tail->prev;
        temp->next = nullptr;
        delete tail;
        tail = temp;
        nodeCounter--;
        return true;
    }
    return false;
}

template <typename T> 
bool LinkedList<T>::RemoveAt(unsigned int index) {
    if (index >= nodeCounter) {
        return false;
    }
    else if (index == 0) {
        return RemoveHead();
    }
    else if (index == (nodeCounter - 1))
    {
        return RemoveTail();
    }
    else {
        Node* temp = head;
        for (unsigned int i = 0; i < index; i++) {
            temp = temp->next;
        }
        if (temp->prev != nullptr) 
            temp->prev->next = temp->next;
        if (temp->next != nullptr) 
            temp->next->prev = temp->prev;

        delete temp;
        nodeCounter--;
        return true;
    }
}

template <typename T>
unsigned int LinkedList<T>::Remove(const T& _data) {
    unsigned int numNodesRemoved = 0;
    unsigned int index = 0;
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == _data) {
            RemoveAt(index);
            numNodesRemoved++;
        }
        else {
            index++;
        }
        temp = temp->next;
    }
    return numNodesRemoved;
}

template <typename T>
void LinkedList<T>::Clear() {
    Node* temp = head;
    while (temp != nullptr) {
        delete temp;
        temp = temp->next;
    }
    head = nullptr;
    tail = nullptr;
    nodeCounter = 0;
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

template<typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* _node) const {
    if (_node == nullptr) {}
    else {
        cout << _node->data << endl;
        PrintForwardRecursive(_node->next);
    }
}

template<typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* _node) const {
    if (_node == nullptr) {}
    else {
        cout << _node->data << endl;
        PrintReverseRecursive(_node->prev);
    }
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
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& _data) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == _data) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

// CONSTANT Find
template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& _data) const {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == _data) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

// Find All
template<typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == value) {
            outData.push_back(temp); 
        }
        temp = temp->next;
    }
}

// Return head
template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() {
    return head;
}

// Return Head Constant
template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const {
    return head;
}

// Return Tail
template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {
    return tail;
}
// Return Tail Constant
template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const {
    return tail;
}

// Get Node
template<typename T> 
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {
    if (index >= nodeCounter) {
        throw std::out_of_range("That request is out of Array range.");
    }
    Node* temp = head;
    for (unsigned int i = 0; i < index; i++) {
        temp = temp->next;
    }
    return temp;
}

// Get Node Constant
template<typename T> 
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {
    if (index >= nodeCounter) {
        throw std::out_of_range("That request is out of Array range.");
    }
    Node* temp = head;
    for (unsigned int i = 0; i < index; i++) {
        temp = temp->next;
    }
    return temp;
}

// Operator[] overload
template<typename T>
T& LinkedList<T>::operator[](unsigned int index) {
    if (index >= nodeCounter) {
        throw std::out_of_range("That request is out of Array range.");
    }
    Node* temp = head;
    for (unsigned int i = 1; i <= index; i++) {
        temp = temp->next;
    }
    return temp->data;
}

// Operator[] overload constant
template<typename T>
const T& LinkedList<T>::operator[](unsigned int index) const {
    if (index >= nodeCounter) {
        throw std::out_of_range("That request is out of Array range.");
    }
    Node* temp = head;
    for (unsigned int i = 1; i <= index; i++) {
        temp = temp->next;
    }
    return temp->data;
}