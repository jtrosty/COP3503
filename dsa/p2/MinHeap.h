
class MinHeap {
    private:
    int* heap;
    int size;
    int capacity;
    int resizeFactor = 2;

    char resizeSmaller();
    char resizeLarger();

    char heapifyUp(int index);
    char heapifyDown(int index);

    public:


    MinHeap();

    char insert(int value);

    char extractMin();

    char deleteValue();

    void traversal();

};


////////////////////////////////////////////////////////////////////////
//                  Constructors

MinHeap::MinHeap() {
    size = 0;
    heap = nullptr;
}

////////////////////////////////////////////////////////////////////////
//                  Insert

char MinHeap::insert(int value) {
    int initialSize = 10;
    if (heap == nullptr) {
        heap = new int(initialSize);
        capacity = initialSize;
        heap[0] = value;
        size++;
    }
    else {
        heap[size - 1] = value;
        heapifyUp(size);
        size++;
    }

    // Check if a resize is requried
    if (size == capacity)       resizeLarger();
    if (size == (capacity / 4)) resizeSmaller();

    return 1;
}

////////////////////////////////////////////////////////////////////////
//                  Resize Functions

char MinHeap::resizeLarger() {
    int* newHeap = new int(capacity * 2);
    for (int i = 0; i < size; i++) {
        newHeap[i] = heap[i];
    }
    delete[] heap;
    heap = newHeap;
    return 1;
}

char MinHeap::resizeSmaller() {
    int* newHeap = new int(capacity / 2);
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


