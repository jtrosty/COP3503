#include <iostream>
#include <list>
using std::cout;
using std::endl;

class Node {
    public:
        int value;
        Node* next = NULL;
};

int findInList(std::list<int>& myList, int valueToFind) {
    std::list<int>::iterator iter;
    int index = 0;
    for (iter = myList.begin(); iter != myList.end(); iter++, index++)     {
        if (*iter == valueToFind) return index;
    }
    return -1;
}

int find(Node* node, int valueInput) {
    int valueNotFound = -1;
    Node* temp = node;
    int index = 0;

    do {
        if(temp->value == valueInput) return index;
        temp = temp->next;
        index++;
    } while (temp != NULL);

    return valueNotFound;
}

Node* add(Node* head, int index, int valueInput) {
    Node* current = head;
    // Make the new node
    Node* newNode = new Node;
    newNode->value = valueInput;

    // Handles if inserting at head
    if (index == 0) {
        newNode->next = head;
        head = newNode;
        return head;
    }
    
    // Most common case, adding at any other index, For loops gets to the index-1
    // Get to the index
    for (int i = 0; i < index - 1; i++) {
        if(current->next == NULL) return NULL;
        else current = current->next;
    }

    // insert new node, if handles addind node in middle of LL
    if (current->next != NULL) {
        newNode->next = current->next;
    }
    // Handles case of adding node at end
    else {
        newNode->next = NULL;
    }
    current->next = newNode;

    return head;
}

float median(Node* head) {
    float result = 0;
    int size = 1;
    Node* temp = head;
    Node* medianNode = head;
    int evenCase = -1;
    int oddCase = -1;

    // TODO: 
    // So the way it works, the median tracker node only moves forward if the temp node
    // modes to a odd node, this ensures that the medianNode stays at the mid point (round down)
    // between the start and were the temp node is. 
    // We do not know the length of the list. 
    while (temp->next != NULL) {
        // Even size
        /*
        if (size % 2 == 0) {
            evenSize = medianNode->next->value;
        }
        */
        // Odd size
        if (size == 1) {
            evenCase = medianNode->value;
            oddCase = medianNode->next->value;
        }
        else if (size % 2 == 1) {
            medianNode = medianNode->next;
            evenCase = medianNode->value;
            oddCase = medianNode->next->value;
        }
        // Increment the linked list
        size++;
        temp = temp->next;
    }
    cout << endl;
    cout << "Odd: " << oddCase << endl;
    cout << "Even: " << evenCase << endl;
    cout << "Size: " << size << endl;

    if (head->next == NULL) return head->value;
    else if (size % 2 == 0) 
        return (float)((float)oddCase + (float)(evenCase))/2.0f;
    else 
        return (float)oddCase;
}

void printNodes(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        cout << temp->value << ", ";
        temp = temp->next;
    }
}

int main (void) {
    cout << "hello world" << endl;
    Node* node0 = new Node;
    Node* node1 = new Node;
    Node* node2 = new Node;
    Node* node3 = new Node;
    Node* node4 = new Node;
    node0->value = 5;
    node0->next = NULL;
    node0 = add(node0, 0, 4);
    node0 = add(node0, 0, 3);
    node0 = add(node0, 0, 2);
    node0 = add(node0, 0, 1);
    cout << "Test 1,2,3,4: " << find(node0, 6) << endl;

    //printNodes(add(node0, 5, 9));
    cout << endl;
    cout << "Test Post add" << find(node0, 9) << endl;
    printNodes(node0);
    cout << endl;
    cout << "Test Median " << median(node0) << endl;
    cout << "print nodes: ";
    printNodes(node0);


    return 0;
}