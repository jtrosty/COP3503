
class MinHeap {
    private:

    // Resize functions
    char resizeSmaller();
    char resizeLarger();

    // Heapify
    char heapifyUp(int index);
    char heapifyDown(int index);

    public:
    int* heap;
    int size;
    int capacity;
    int resizeFactor = 2;


    MinHeap();
    ~MinHeap();

    char insert(int value);

    int extractMin();

    char deleteValue();

    void traversal();

    void printHeap();

};


////////////////////////////////////////////////////////////////////////
//                  Constructors and Destructor

MinHeap::MinHeap() {
    size = 0;
    int initialCapacity = 10;
    capacity = initialCapacity;
    heap = new int[initialCapacity];
}

MinHeap::~MinHeap() {
    if (heap == nullptr) {}
    else delete[] heap;
}

////////////////////////////////////////////////////////////////////////
//                  Insert

char MinHeap::insert(int value) {
    if (size == 0) {
        heap[size] = value;
        size++;
    }
    else {
        size++;
        heap[size - 1] = value;
        heapifyUp(size - 1);
    }

    // Check if a resize is requried
    if (size == capacity - 1)   resizeLarger();

    return 1;
}

////////////////////////////////////////////////////////////////////////
//                  Extract Min

int MinHeap::extractMin() {
    if (size > 0) {
        int result = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
        return result;
    }
    if (size == (capacity / 4)) resizeSmaller();
    else return -1;
}

////////////////////////////////////////////////////////////////////////
//                  Resize Functions

char MinHeap::resizeLarger() {
    capacity = capacity * 2;
    int* newHeap = new int[capacity];
    for (int i = 0; i < size; i++) {
        newHeap[i] = heap[i];
    }
    delete[] heap;
    heap = newHeap;
    printHeap();
    return 1;
}

char MinHeap::resizeSmaller() {
    int* newHeap = new int[capacity / 2];
    for (int i = 0; i < size; i++) {
        newHeap[i] = heap[i];
    }
    delete[] heap;
    heap = newHeap;
    return 1;
}

////////////////////////////////////////////////////////////////////////
//                  Heapify Functions

char MinHeap::heapifyUp(int index) {
    int parent = (index - 1) / 2;
    int temp = -1;

    while (heap[index] < heap[parent]) {
        temp = heap[index];
        heap[index] = heap[parent];
        heap[parent] = temp;

        // break out if we traded out the root
        if (parent == 0) break;
        
        // adjust index for going up
        index = parent;
        parent = (index - 1) /2;
    }

    return 1;
}

char MinHeap::heapifyDown(int index) {
    int child1 = (2 * index) + 1;
    int child2 = (2 * index) + 2;
    int temp = -1;

    while (child1 < size) {
        // Case of the last item being a leaf with no sibling
        if (size - 1 == child1) {
            if (heap[index] > heap[child1]) {
                temp = heap[index];
                heap[index] = heap[child1];
                heap[child1] = temp;
                index = child1;
            }
        } 
        else if (heap[index] > heap[child1] || heap[index] > heap[child2]) {
            if (heap[child1] < heap[child2]) {
                temp = heap[index];
                heap[index] = heap[child1];
                heap[child1] = temp;
                index = child1;
            }
            else {
                temp = heap[index];
                heap[index] = heap[child2];
                heap[child2] = temp;
                index = child2;
            }
        }
        child1 = (index * 2) + 1;
        child2 = (index * 2) + 2;
    }
    return 1;
}

////////////////////////////////////////////////////////////////////////
//                  Print Functions

void MinHeap::printHeap() {
    if (size > 0) {
        for (int i = 0; i < size; i++) {
            if (i == size-1) std::cout << heap[i] << std::endl;
            else std::cout << heap[i] << ", ";
        }
    }
}