int CAPACITY = 10;

class CircularArrayQueue {

private:
	// private data member
    int size;
    int capacity;
    int front;
    int back;
    int* data;

public:
	CircularArrayQueue();
    ~CircularArrayQueue();
	bool isEmpty() const;
	void enqueue(int x);
	void dequeue();
	int peekFront() const;
};

CircularArrayQueue::CircularArrayQueue() {
    size = 0;
    capacity = CAPACITY;
    data = new int[CAPACITY];
    front = 0;
    back = 0;
}

CircularArrayQueue::~CircularArrayQueue() {
    delete[] data;
}

bool CircularArrayQueue::isEmpty() const {
    return (size <= 0);
}

void CircularArrayQueue::enqueue(int x)  {
    size++;
    data[back++] = x;
    if (back >= capacity) {
        back = back % capacity;
    }
}

void CircularArrayQueue::dequeue() {
    size--;
    if(front != back) front++;
    if (front >= capacity) {
        front = front % capacity;
    }
}

int CircularArrayQueue::peekFront() const {
    return data[front];
}