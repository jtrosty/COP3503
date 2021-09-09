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

float interQuartile(Node* head) {
    Node* first;
    Node* median;
    Node* third;
    Node* fastNode;
    int size = 4; // ASSUME THE LINKED LIST SUPPLIED HAS MIN SIZE OF 4
    int shiftNode = 0;
    float divideby2 = 2.0f;

    // Problem statements says a head will have at least 4 values, the following
    // code will set up the initial conditiosn of 
    // 1   2   3   4
    //   ^   ^   ^
    //   Q1  Q2  Q3
    first    = head;
    median   = head->next;
    third    = head->next->next;
    fastNode = head->next->next->next;

    // with initial conditions set, the logic to handle and remaining size of list
    while (fastNode != NULL) {
        shiftNode = (size % 4);
        // First shifts 1 out of every 4 node changes of the final node 
        if (shiftNode == 2) first = first->next;
        // Median, shifts every other node change for the final node
        if (shiftNode == 1 || shiftNode == 3) median = median->next;
        // thrid, shifts 3 out of 4 node shifts of the final node
        if (shiftNode != 0) third = third->next;
        fastNode = fastNode->next;
        size++;
    }

/*
    Code used for testing and trouble shooting
    cout << endl;
    cout << "first " << first->value << endl;
    cout << "median " << median->value << endl;
    cout << "thrid " << third->value << endl;
    cout << "size " << size << endl;
    cout << "Shift " << shiftNode << endl;
    */

    if (shiftNode == 2 || shiftNode == 3) {
        return float(third->value - first->value);
    }
    else {
        float result;
        result = ((float)first->value + (float)first->next->value) / divideby2;
        result = (((float)third->value + (float)third->next->value) / divideby2) - result;
        return result;
    }
    return -1.0;
}

int main (void) {
    cout << "hello world" << endl;
    Node* node0 = new Node;
    node0->value = 1;
    node0->next = NULL;
    node0 = add(node0, 1, 2);
    node0 = add(node0, 2, 3);
    node0 = add(node0, 3, 4);
    //node0 = add(node0, 4, 5);
    //node0 = add(node0, 5, 6);
    //node0 = add(node0, 6, 7);
    //node0 = add(node0, 7, 8);
    //node0 = add(node0, 8, 9);
    cout << "Test 1,2,3,4: " << find(node0, 6) << endl;

    //printNodes(add(node0, 5, 9));
    cout << endl;
    cout << "Test Post add" << find(node0, 9) << endl;
    printNodes(node0);
    cout << endl;
    cout << "IQR " << interQuartile(node0) << endl;
    cout << "print nodes: ";
    printNodes(node0);


    return 0;
}