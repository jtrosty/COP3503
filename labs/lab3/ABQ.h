#pragma once
#include <iostream>
#include <exception>
using std::cout;
using std::runtime_error;
using std::endl;

template <typename T>
class ABQ {

//############### Class Variables ##################
//##################################################
    unsigned int _actualSize;
    unsigned int _maxCapacity;

    unsigned int _first;

    T* _theData;
    const float _scaleFactor = 2.0f;
    
    void resizeLarger();
    void resizeSmaller();
    ABQ& copy(const ABQ& other); // private copy funciton for copy constructor and copy assignment. 

//################ Public  #############################
//######################################################
    public: 

    ABQ();
    ABQ(int capacity);
    ABQ(const ABQ& other);
    ABQ& operator=(const ABQ& other);
    ~ABQ();

    void enqueue(T data);
    T dequeue();
    T peek();

//############### Getters and Setters ##################
//######################################################
    unsigned int getSize();
    unsigned int getMaxCapacity();
    unsigned int getFirst();
    T at(int index);
    T* getData();
};

// ######################################################
// ############## Class Definition ######################
// ######################################################

// ############## Default Constructor ###################
template<typename T>
ABQ<T>::ABQ() {
    _maxCapacity = 1;
    _actualSize = 0;
    _theData = new T[_maxCapacity];
    _first = 0;
}

template<typename T>
ABQ<T>::ABQ(int capacity) {
    _maxCapacity = capacity;
    _actualSize = 0;
    _theData = new T[_maxCapacity];
    _first = 0;
}

// ############### Getters and Setters ###################
template<typename T>
unsigned int ABQ<T>::getSize() {
    return _actualSize;
}

template<typename T>
unsigned int ABQ<T>::getMaxCapacity() {
    return _maxCapacity;
}

template<typename T>
unsigned int ABQ<T>::getFirst() {
    return _first;
}

template<typename T>
T ABQ<T>::at(int index) {
    return _theData[index];
}

// ############### The Big Three #########################

// ###### COPY CONSTRUCTOR
template<typename T>
ABQ<T>::ABQ (const ABQ& other) {
    _theData = other._theData;
    _actualSize = other._actualSize;
    _maxCapacity = other._maxCapacity;
    _first = other._first;

    for (int i = 0; i < other._maxCapacity; ++i) {
        _theData[i] = other._theData[i];
    }
}

// ##### Copy Assignment 
template<typename T> 
ABQ<T>& ABQ<T>::operator=(const ABQ& other) {
    _theData = other._theData;
    _actualSize = other._actualSize;
    _maxCapacity = other._maxCapacity;
    _first = other._first;

    for (int i = 0; i < other._maxCapacity; ++i) {
        _theData[i] = other._theDatat[i];
    }
    return *this;
}

// #### Destructor
template<typename T> 
ABQ<T>::~ABQ () {
    delete[] _theData;
}

// #########################################################
// ########### Queue Behavior ##############################
// #########################################################

// #### Enqueue
template<typename T>
void ABQ<T>::enqueue(T data) {
    int lastIndex;
    
    // If too many data points, begin resize. 
    if (_actualSize == _maxCapacity) resizeLarger();

    // Determine last index so that data is input in correct place. 
    if (_actualSize == 0) lastIndex = _first; 
    else lastIndex = ((_first + _actualSize) % _maxCapacity);

    _theData[lastIndex] = data;
    _actualSize++;
}

// #### Dequeue 
// Contains the Logic for if a resize smaller is required.
template<typename T>
T ABQ<T>::dequeue() {
    // The dequeue result is collected at the start. 
    T result = _theData[_first++];
    // Check fo if array is empty
    if (_actualSize == 0) 
        throw runtime_error("Data structure is empty, unable to dequeue.");

    // If _first has run over, the, reset it back to start of array
    if (_first > _maxCapacity) _first = _first % _maxCapacity;
    _actualSize--;

    // Logic for resize
    float percentFilled = ((float)_actualSize / (float)_maxCapacity);
    if ( percentFilled < (1.0f / _scaleFactor)) {
        resizeSmaller();
    }  
    return result;
}

// #### Peek
template<typename T>
T ABQ<T>::peek() {
    if (_actualSize == 0) 
        throw runtime_error("Data structure is empty, nothing to peek");
    return _theData[_first];
}

// #### Resize Larger
template<typename T>
void ABQ<T>::resizeLarger() {
    unsigned int i;
    unsigned int oldMax = _maxCapacity; // have to normalize capcity to the array largest index size. 

    _maxCapacity = _scaleFactor * _maxCapacity;
    T* temp = new T[_maxCapacity];    
    for (i = 0; i < _maxCapacity; ++i){
        temp[i] = _theData[(i + _first) % oldMax];
    }

    _first = 0;
    delete[] _theData;
    _theData = temp; 
}

// #### Resize Smaller 
template<typename T>
void ABQ<T>::resizeSmaller() {
    unsigned int i;
    unsigned int iOldArray;
    unsigned int oldMax = _maxCapacity; // have to normalize capcity to the array largest index size. 
    _maxCapacity = _maxCapacity / _scaleFactor;
    T* temp = new T[_maxCapacity];    
    for (i = 0; i < _maxCapacity; ++i){
        iOldArray = (i + _first) % (oldMax + 1);
        temp[i] = _theData[iOldArray];
    }
    _first = 0;
    delete[] _theData;
    _theData = temp;
}
