#pragma comment(linker, "/STACK:4000000")
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <fstream>
#include <set>
#include <string>
#include <random>
#include <ctime>
using std::ofstream;

using std::cout;
using std::endl;
using std::cin;
using std::freopen;

//////////////////////////////////////////////////////////////////////
//                                MIN HEAP CLASS
/////////////////////////////////////////////////////////////////////


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

    char deleteValue(int value);
    char deleteIndex(int index); 

    void traversal();

    void printHeap();
    void traversalOfMinHeap(std::ofstream& outfile); 
    int search(int itemToFind);

    char isEmpty();
};



//////////////////////////////////////////////////////////////////////
//                                HASH TABLE CLASS
/////////////////////////////////////////////////////////////////////


class HashTable {
    public:
        struct Node {
            int data;
            Node* next;
            Node() : data(0xf0000000), next(nullptr) {}
            Node(int value) : data(value), next(nullptr) {}
            Node& operator=(Node& node) {
                this->data = node.data;
                this->next = node.next;
                return *this;
            }
        };

        HashTable();
        ~HashTable();
        void deleteHashTable(Node** oldTable);
        HashTable& operator=(HashTable& hash);

        void insert(int data); 
        void insert(Node* node); 
        char remove(int data); 
        char removeAll(); 
        void print(std::ofstream& outFile);

        char isEmpty();

        char traverse(int keyToSearch);

    private:
        int capacity;
        int size;
        float loadFactor;
        Node** table;
        enum Resize { bigger, smaller};

        void rehash(Resize choice, int factor);
        int getHashIndex(int key);

};
//////////////////////////////////////////////////////////////////////
//                                RANDOM CLASS
/////////////////////////////////////////////////////////////////////
class Random
{
	static std::mt19937 random;
public:
	// One instance of x, all instances share this variable
	static int x;
	static int Int(int min, int max);
};

// Static variables must be redeclared in global space
std::mt19937 Random::random(time(0));
int Random::x = 100;

void createInputFiles(int size, int bigSize, int reallyBigSize);
double fillHeap(char testToRun, MinHeap& heap);
double fillHashTable(char testToRun, HashTable& table);
double emptyHashTable(char testToRun, HashTable& table); 
double emptyHeap(char testToRubn, MinHeap& heap);
double traverseHeap(MinHeap& heap, char testRun);
double traverseHash(HashTable& table, char testRun); 
int* generateRandomArray(int size);
void printResults(double* inResults, double* traversalTimes, double* outResults, char structureUsed);
std::string getFileName(char testToRun); 
std::string getFileOutputName(char testToRun); 

int main (void) {
    char run = 1;
    HashTable testHash;
    MinHeap testHeap;
    std::set <int> s;

    int size = 1000;
    int bigSize = 10 * size;
    int reallyBigSize = 10 * bigSize;

    char input = 0;
    std::string value;
    std::string streamInput;

    double* inTimesHeap        = new double[10];
    double* traversalTimesHeap = new double[10];
    double* outTimesHeap       = new double[10];

    double* inTimesHash        = new double[10];
    double* traversalTimesHash = new double[10];
    double* outTimesHash       = new double[10];
    double startValue = -1.0f;

    for (int i = 0; i < 10; i++) {
        inTimesHeap[i]        = startValue;
        traversalTimesHeap[i] = startValue;
        outTimesHeap[i]       = startValue;
        inTimesHash[i]        = startValue;
        traversalTimesHash[i] = startValue;
        outTimesHash[i]       = startValue;
    }

    while (run != 0) {
        
        // Menu
        //cout << "Menu: " << endl;
        //cout << "1. Create input and run all tests" << endl;
        //cout << "q  - Quit the program." << endl;
        cout << "Program is automatically running" << endl;

        // User input
        //cin >> input;
        input = '1';
        int numOfTests = 9;

        // Logic
        switch(input) {
            case '1': {
                createInputFiles(size, bigSize, reallyBigSize);

                // Min Heap
                for(int i = 1; i <= numOfTests; i++) {
                    if(testHeap.isEmpty()) {
                        inTimesHeap[i] = fillHeap(i, testHeap)            * 1000.0f;
                        traversalTimesHeap[i] = traverseHeap(testHeap, i) * 1000.0f;
                        outTimesHeap[i] = emptyHeap(i, testHeap)          * 1000.0f;
                    }
                }

                // Hast Table
                for(int i = 1; i <= numOfTests; i++) {
                    if(testHash.isEmpty()) {
                        inTimesHash[i] = fillHashTable(i, testHash)        * 1000.0f;
                        traversalTimesHash[i] = traverseHash(testHash, i)  * 1000.0f;
                        outTimesHash[i] = emptyHashTable(i, testHash)      * 1000.0f;
                    }
                }

                printResults(inTimesHeap, traversalTimesHeap, outTimesHeap, 1);
                printResults(inTimesHash, traversalTimesHash, outTimesHash, 2);
                std::ofstream outFile;
                outFile.open("results.csv", std::ofstream::out);
                for (int i = 0; i < 10; i++) {
                    outFile << inTimesHeap[i]        << ", ";
                    outFile << traversalTimesHeap[i] << ", ";
                    outFile << outTimesHeap[i]       << ", ";
                    outFile << inTimesHash[i]        << ", ";
                    outFile << traversalTimesHash[i] << ", ";
                    outFile << outTimesHash[i]       << ", ";
                    outFile << endl;
                }
                outFile.close();
                run = 0;

                break;
            }
            case '3': { // used for testing
                cin >> value;
                testHeap.insert(std::stoi(value));
                testHeap.printHeap();
                break;
            }
            case '4': { // used for testing
                cout << testHeap.extractMin() << endl;
                break;
            }
            case 'q': { // used to extit while loop
                run = 0;
                break;
            }
        }
    }
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////
//                  Print results of all data

void printResults(double* inResults, double* traversalTimes, double* outResults, char structureUsed) {
    cout << " Resut for ";
    if (structureUsed == 1) cout << "Minimum Heap" << endl;
    else cout << "Hash Table" << endl;
    cout << "Small  Ascending In:  " << inResults[1] << " | traversal: " << traversalTimes[1] << " | Small  Ascending out:  " << outResults[1] << endl;
    cout << "Small  Descending In: " << inResults[4] << " | traversal: " << traversalTimes[4] << " | Small  descending out: " << outResults[4] << endl;
    cout << "Small  Random In:     " << inResults[7] << " | traversal: " << traversalTimes[7] << " | Small  Random out:     " << outResults[7] << endl;
    cout << "Medium Ascending In:  " << inResults[2] << " | traversal: " << traversalTimes[2] << " | Medium Ascending out:  " << outResults[2] << endl;
    cout << "Medium Descending In: " << inResults[5] << " | traversal: " << traversalTimes[5] << " | Medium descending out: " << outResults[5] << endl;
    cout << "Medium Random In:     " << inResults[8] << " | traversal: " << traversalTimes[8] << " | Medium Random out:     " << outResults[8] << endl;
    cout << "Large  Ascending In:  " << inResults[3] << " | traversal: " << traversalTimes[3] << " | Large  Ascending out:  " << outResults[3] << endl;
    cout << "Large  Descending In: " << inResults[6] << " | traversal: " << traversalTimes[6] << " | Large  descending out: " << outResults[6] << endl;
    cout << "Large  Random In:     " << inResults[9] << " | traversal: " << traversalTimes[9] << " | Large  Random out:     " << outResults[9] << endl;
}

/////////////////////////////////////////////////////////////////////////////////
//                 Travese the 2 data structurs 

double traverseHeap(MinHeap& heap, char testRun) {
    std::ofstream outFile;
    std::string outName = "";
    testRun += 47;
    outName = outName + "data/" + testRun  + "_out_heap.txt";

    auto start = std::chrono::steady_clock::now();

    outFile.open(outName, std::ofstream::out);
    heap.traversalOfMinHeap(outFile);
    outFile.close();
    
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> time = end - start;
    //cout << "Time to empty: " << time.count() << endl;
    return time.count();
}

double traverseHash(HashTable& table, char testRun) {
    std::ofstream outFile;
    std::string outName = "";
    testRun += 47;
    outName = outName + "data/" + testRun + "_out_hash.txt";

    auto start = std::chrono::steady_clock::now();

    outFile.open(outName, std::ofstream::out);
    table.print(outFile);
    outFile.close();

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> time = end - start;
    //cout << "Time to empty: " << time.count() << endl;
    return time.count();
}

////////////////////////////////////////////////////////////////////////////////
//   Generates a Random Array, first a array of 1 to size is created. Then
//   the array is loop through once and a random index remaining in the 
//   array is used to swap with the current index in the loop.
int* generateRandomArray(int size) {
    Random rand;
    int* resultArray = new int[size];
    for (int i = 0; i < size; i++) {
        resultArray[i] = i;
    }
    for (int i = 0; i < size; i++) {
        int swapIndex = rand.Int(i, size - 1);
        int temp = resultArray[swapIndex];
        resultArray[swapIndex] = resultArray[i];
        resultArray[i] = temp;
    }
    //for (int i = 0; i < size; i++) {
    //    cout << resultArray[i] << ", ";
    //}
    return resultArray;
}

///////////////////////////////////////////////////////////////////////////////
//               Empty heap test
double emptyHeap(char testToRun, MinHeap& heap) {
    std::string inputFile = getFileName(testToRun);
    std::ifstream file;
    std::string streamInput;

    auto start = std::chrono::steady_clock::now();
    file.open(inputFile);
    while(!file.eof()) {
        std::getline(file, streamInput, ',');
        heap.deleteValue(std::stoi(streamInput));
    }
    file.close();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> time = end - start;
    //cout << "Time to empty: " << time.count() << endl;
    return time.count();
}

///////////////////////////////////////////////////////////////////////////////
//               Empty HashTable test
double emptyHashTable(char testToRun, HashTable& table) {
    std::string inputFile = getFileName(testToRun);

    std::ifstream file;
    std::string streamInput;
    auto start = std::chrono::steady_clock::now();
    file.open(inputFile);
    while(!file.eof()) {
        std::getline(file, streamInput, ',');
        table.remove(std::stoi(streamInput));
    }
    file.close();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> time = end - start;
    //cout << "Time to empty: " << time.count() << endl;
    return time.count();
}

///////////////////////////////////////////////////////////////////////////////
//               Insert heap test
double fillHeap(char testToRun, MinHeap& heap) {
    std::ifstream infile;
    std::string streamInput;
    std::string inputData = getFileName(testToRun);

    auto start = std::chrono::steady_clock::now();
    infile.open(inputData, std::ifstream::in);

    if (infile.is_open()) {
        while(!infile.eof()) {
            std::getline(infile, streamInput, ',');
            if (!streamInput.empty()) heap.insert(std::stoi(streamInput));
        }
        infile.close();
    }
    else cout << "DIDDN'T OPEN TEST: " << testToRun << endl;
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> time = end - start;
    //cout << "Time to fill: " << time.count() << endl;

    return time.count();
}

///////////////////////////////////////////////////////////////////////////////
//               Insert HashTable test
double fillHashTable(char testToRun, HashTable& table) {
    std::ifstream infile;
    std::string streamInput;
    std::string inputData = getFileName(testToRun);

    auto start = std::chrono::steady_clock::now();
    infile.open(inputData, std::ifstream::in);

    if (infile.is_open()) {
        while(!infile.eof()) {
            std::getline(infile, streamInput, ',');
            if (!streamInput.empty()) table.insert(std::stoi(streamInput));
        }
        infile.close();
    }
    else cout << "DID NOT OPEN TEST: " << testToRun << endl;
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> time = end - start;

    return time.count();
}
///////////////////////////////////////////////////////////////////////////////
//               Create 9 test files to input small, medium, and large files in
//               3 formats, ascending, descending, and random.

void createInputFiles(int size, int bigSize, int reallyBigSize) {
    int* randomArray;
    std::ofstream outPutFile;

    // Ascending files
    outPutFile.open("data/sm_as_in.txt");
    for (int i = 0; i < size; i++) {
        if (i == size - 1) outPutFile << i; 
        else outPutFile << i << ", ";
    }
    outPutFile.close();

    outPutFile.open("data/me_as_in.txt");
    for (int i = 0; i < bigSize; i++) {
        if (i == bigSize - 1) outPutFile << i; 
        else outPutFile << i << ", ";
    }
    outPutFile.close();

    outPutFile.open("data/la_as_in.txt");
    for (int i = 0; i < reallyBigSize; i++) {
        if (i == reallyBigSize - 1) outPutFile << i; 
        else outPutFile << i << ", ";
    }
    outPutFile.close();

    outPutFile.open("data/sm_ds_in.txt");
    for (int i = size - 1; i >= 0; i--) {
        if (i == 0) outPutFile << i; 
        else outPutFile << i << ", ";
    }
    outPutFile.close();
   
    outPutFile.open("data/me_ds_in.txt");
    for (int i = bigSize - 1; i >= 0; i--) {
        if (i == 0) outPutFile << i; 
        else outPutFile << i << ", ";
    }
    outPutFile.close();

    outPutFile.open("data/la_ds_in.txt");
    for (int i = reallyBigSize - 1; i >= 0; i--) {
        if (i == 0) outPutFile << i; 
        else outPutFile << i << ", ";
    }
    outPutFile.close();

    outPutFile.open("data/sm_ra_in.txt");
    randomArray = generateRandomArray(size);
    for (int i = 0; i < size; i++) {
        if (i == size - 1) outPutFile << randomArray[i]; 
        else outPutFile << randomArray[i] << ", ";
    }
    outPutFile.close();
    delete[] randomArray;

    outPutFile.open("data/me_ra_in.txt");
    randomArray = generateRandomArray(bigSize);
    for (int i = 0; i < bigSize; i++) {
        if (i == bigSize - 1) outPutFile << randomArray[i]; 
        else outPutFile << randomArray[i] << ", ";
    }
    outPutFile.close();
    delete[] randomArray;

    outPutFile.open("data/la_ra_in.txt");
    randomArray = generateRandomArray(reallyBigSize);
    for (int i = 0; i < reallyBigSize; i++) {
        if (i == reallyBigSize - 1) outPutFile << randomArray[i]; 
        else outPutFile << randomArray[i] << ", ";
    }
    outPutFile.close();
    delete[] randomArray;
}

//////////////////////////////////////////////////////////////////////
//                   Helper function, get file name
std::string getFileName(char testToRun) {
    switch(testToRun) {
        case 1: { return "data/sm_as_in.txt"; break; }
        case 2: { return "data/me_as_in.txt"; break; }
        case 3: { return "data/la_as_in.txt"; break; }
        case 4: { return "data/sm_ds_in.txt"; break; }
        case 5: { return "data/me_ds_in.txt"; break; }
        case 6: { return "data/la_ds_in.txt"; break; }
        case 7: { return "data/sm_ra_in.txt"; break; }
        case 8: { return "data/me_ra_in.txt"; break; }
        case 9: { return "data/la_ra_in.txt"; break; }
    }
    // Failed to return
    return "";
}

std::string getFileOutputName(char testToRun) {
    switch(testToRun) {
            case 1: { return "data/out_sm_as.txt"; break; }
            case 2: { return "data/out_me_as.txt"; break; }
            case 3: { return "data/out_la_as.txt"; break; }
            case 4: { return "data/out_sm_ds.txt"; break; }
            case 5: { return "data/out_me_ds.txt"; break; }
            case 6: { return "data/out_la_ds.txt"; break; }
            case 7: { return "data/out_sm_ra.txt"; break; }
            case 8: { return "data/out_me_ra.txt"; break; }
            case 9: { return "data/out_la_ra.txt"; break; }
    }
    return "";
}

//////////////////////////////////////////////////////////////////////
//                                RANDOM CLASS
/////////////////////////////////////////////////////////////////////
int Random::Int(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);

	return dist(random);
}

//////////////////////////////////////////////////////////////////////
//                                HASH TABLE CLASS DEFINITION
/////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////
//             Constructors and Destructors

HashTable::HashTable() {
    capacity = 10;
    size = 0;
    loadFactor = 1.0f; 
    table = new Node*[capacity];
    for (int i = 0; i < capacity; i++) {
        table[i] = nullptr;
    }
}

HashTable::~HashTable() {
    deleteHashTable(table);
}

void HashTable::deleteHashTable(Node** oldTable) {
    for (int i = 0; i < capacity; i++) {
        Node* prev;
        prev = oldTable[i];
        if (oldTable[i] != nullptr) {
            Node* next = prev->next;
            delete prev;
            while (next != nullptr) {
                prev = next;
                next = next->next;
                delete prev;
            }
        }
    }
    delete[] oldTable;
}

///////////////////////////////////////////////////////
//             Insert Functions and their support
int HashTable::getHashIndex(int key) {
    return key % capacity;
}

void HashTable::insert(int data) {
    int key = getHashIndex(data);
    if (table[key] == nullptr) {
        Node* newNode = new Node(data);
        table[key] = newNode;
    }
    else {
        int counter = 0;
        Node* temp = table[key];
        Node* newNode = new Node(data);
        while (temp->next != nullptr) {
            temp = temp->next;
            counter++;
        }
        temp->next = newNode;
        if ((float)size / (float)capacity > loadFactor) rehash(bigger, 2);
    }
    size++;
}

/***** NOT USED ***********/
void HashTable::insert(Node* node) {
    int key = getHashIndex(node->data);
    if (table[key] == nullptr) {
        table[key] = node;
    }
    else {
        int counter = 0;
        Node* temp = table[key];
        while (temp->next != nullptr) {
            temp = temp->next;
            counter++;
        }
        temp->next = node;
    }
}

///////////////////////////////////////////////////////
//             Rehash

void HashTable::rehash(Resize choice, int factor) {
    int newCapacity;
    if (choice == bigger) newCapacity = capacity * factor; 
    else newCapacity = capacity / factor;

    Node** newTable = new Node*[newCapacity];
    for (int i = 0; i < newCapacity; i++) {
        newTable[i] = nullptr;
        size = 0;
    }
    int oldCapacity = capacity;

    Node** oldTable = table;
    table = newTable;
    capacity = newCapacity;

    for(int i = 0; i < oldCapacity; i++) {
        Node* temp = oldTable[i];
        while (temp != nullptr) {
            insert(temp->data);
            temp = temp->next;
        }
    }
    delete[] oldTable;
}

///////////////////////////////////////////////////////
//             Remove
char HashTable::remove(int data) {
    int key = getHashIndex(data);
    Node* prev = nullptr;
    Node* temp = table[key];
    while (temp != nullptr) {
        if (temp->data == data) {
            if (prev == nullptr) table[key] = temp->next;
            else                 prev->next = temp->next;
            delete temp;
            size--;
            if ((size < (capacity / 4)) && size > 5) rehash(smaller, 2);
            return 1;
        }
        prev = temp;
        temp = temp->next;
    }
    return 0;
} 

char HashTable::removeAll() {
    int initialSize = size;
    for (int i = 0; i < initialSize; i++) remove(i);
    return 1;
}

///////////////////////////////////////////////////////
//             Traverse
char HashTable::traverse(int keyToSearch) {
    for(int i = 0; i < capacity; i++) {
        Node* temp = table[i];
        while (temp != nullptr) {
            if (temp->data == keyToSearch) return 1;
            temp = temp->next;
        }
    }
    return 0;
}

///////////////////////////////////////////////////////
//             Print
void HashTable::print(std::ofstream& outFile) {
    int counter = 0;
    for(int i = 0; i < capacity; i++) {
        Node* temp = table[i];
        while (temp != nullptr) {
            outFile << temp->data << ", ";
            counter++;
            temp = temp->next;
        }
    }
    //std::cout << std::endl << "total size " << size << " counter " << counter << std::endl;
}

///////////////////////////////////////////////////////
//           is  Empty
char HashTable::isEmpty() {
    if (size <= 0) return 1;
    else return 0;
}

//////////////////////////////////////////////////////////////////////
//                                MIN HEAP CLASS DEFINITION
/////////////////////////////////////////////////////////////////////

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
//                  Delete Value
char MinHeap::deleteIndex(int index) {
    if (size >= 0 && index < size) {
        heap[index] = heap[size - 1];
        size--;
        heapifyDown(index);
        if ((size <= (capacity / 4)) && (size != 0)) resizeSmaller();
        return 1;
    }
    else return 0;
}

char MinHeap::deleteValue(int value) {
    int index = search(value);
    if (index >= 0 && index < size) 
        return deleteIndex(index);
    return 0;
}

////////////////////////////////////////////////////////////////////////
//                  Extract Min
int MinHeap::extractMin() {
    int result;
    if (size >= 0) {
        result = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
        if ((size <= (capacity / 4)) && (size != 0)) resizeSmaller();
        return result;
    }
    else return result;
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
    return 1;
}

char MinHeap::resizeSmaller() {
    capacity = capacity / 2;
    int* newHeap = new int[capacity];
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

    while ((child1 < size) && (heap[index] > heap[child1] || heap[index] > heap[child2])) {
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

////////////////////////////////////////////////////////////////////////
//                  Traverse Heaps
void MinHeap::traversalOfMinHeap(std::ofstream& outFile) {
    if (size > 0) {
        for (int i = 0; i < size; i++) {
            if (i == size-1) outFile << heap[i] << std::endl;
            else outFile << heap[i] << ", ";
        }
    }
}

////////////////////////////////////////////////////////////////////////
//                  Traverse Heaps
int MinHeap::search(int itemToFind) {
    if (size > 0) {
        for (int i = 0; i < size; i++) {
            if (heap[i] == itemToFind)  return i;
        }
    }
    return -1;
}

////////////////////////////////////////////////////////////////////////
//                  Empty Functions
char MinHeap::isEmpty() {
    if (size <= 0) return 1;
    else return 0;
}