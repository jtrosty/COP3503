
class Stack_LL {

public:

    class Node {
        public:
        int data;
        Node* next;
        Node(int val) {data = val; next = nullptr;}
        Node(int val, Node* node) {data = val; next = node;};
    };

	Stack_LL();
	~Stack_LL();

	bool isEmpty() const;
	void push(int newItem);
	void pop();
	int peek() const;
private:
    Node* topPtr;
	// topPtr points to the top element of the stack
};

Stack_LL::Stack_LL() {
    topPtr = nullptr;
}

Stack_LL::~Stack_LL() {
    // Acts like a recursive funciton deleting each node until isEmpty is true. 
    if (isEmpty()) {}
    else {
        while (!isEmpty()) {
            pop();
        }
    }
}

bool Stack_LL::isEmpty() const {
    return (topPtr == nullptr);
}

void Stack_LL::push(int newItem) {
    // Handle 2 cases, if list is empty or not. 
    if (isEmpty()) {
        Node* newNode = new Node(newItem);
        topPtr = newNode;
    }
    else {
        Node* newNode = new Node(newItem, topPtr);
        topPtr = newNode;
    }
}

void Stack_LL::pop() {
    if (!isEmpty()) {
        // If not empty, hold onto the next pointer, and assign it to topPtr after deleting data at topPtr
        Node* temp = topPtr->next;
        delete topPtr;
        topPtr = temp;
    }
}

int Stack_LL::peek() const {
    if (!isEmpty()) {
        return topPtr->data;
    }
    else {
        return -1;
    }
}