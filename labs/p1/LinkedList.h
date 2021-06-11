#include <iostream>
using std::cout;
using std::endl;

template<typename T>
class LinkedList {

    int nodeCounter;

    public:
        struct Node {
            Node next;
            T* data;
        };
        Node head;
        
        void AddHead(T data);
        void AddTail(T data);
        void AddNodesHead(T data);
        void AddNodesTail(T data);

        /*==== Behaviors ======*/
        void PrintForward() const;
        void PrintReverse() const;

        int getNodeCount();

        LinkedList();
        LinkedList(T _data);
        ~LinkedList();
};

template<typename T>
LinkedList<T>::LinkedList() {
    Node head = new Node;
    head.next = nullptr;
}

template<typename T>
LinkedList<T>::LinkedList(T _data) {
    Node head = new Node;
    head.next = nullptr;
    head.data = _data;
}

// #####################################################
// ############## Insertion Operations #################
// #####################################################
template<typename T>
void LinkedList<T>::AddHead(T _data) {
    Node newNode = new Node;
    newNode.data = _data;
    newNode.next = head;
    head = newNode; 
}

// #####################################################
// ################ Behaviors ##########################
// #####################################################
template<typename T>
void LinkedList<T>::PrintForward() const {
    Node temp;
    temp = head;
    while(temp.next != nullptr) {
        cout << head.data << endl;
    }
}
