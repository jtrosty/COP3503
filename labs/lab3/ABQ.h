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
    unsigned int _totalResizes;
    unsigned int _first;

    T* _theData;
    float _scaleFactor;

    void resize(int control);
    ABQ& copy(const ABQ& other); // private copy funciton for copy constructor and copy assignment. 
    void copyHelper(const ABQ& other);

//################ Public  #############################
//######################################################
    public: 

    ABQ();
    ABQ(int capacity);
    ABQ(int capacity, float scaleFactor);
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
    unsigned int getTotalResizes();
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
    _scaleFactor = 2.0f;
    _theData = new T[_maxCapacity];
    _first = 0;
    _totalResizes = 0;
}

template<typename T>
ABQ<T>::ABQ(int capacity) {
    _maxCapacity = capacity;
    _actualSize = 0;
    _scaleFactor = 2.0f;
    _theData = new T[_maxCapacity];
    _first = 0;
    _totalResizes = 0;
}

template<typename T>
ABQ<T>::ABQ(int capacity, float scaleFactor) {
    _maxCapacity = capacity;
    _actualSize = 0;
    _scaleFactor = scaleFactor;
    _theData = new T[_maxCapacity];
    _first = 0;
    _totalResizes = 0;
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

template<typename T>
unsigned int ABQ<T>::getTotalResizes() {
    return _totalResizes;
}

// ############### The Big Three #########################

// ###### COPY CONSTRUCTOR
template<typename T>
ABQ<T>::ABQ (const ABQ& other) {
    copyHelper(other);
}

// ##### Copy Assignment 
template<typename T> 
ABQ<T>& ABQ<T>::operator=(const ABQ& other) {
    copyHelper(other);
    return *this;
}

// copy Helper for Copy Constructor and Copy Assignment
template<typename T>
void ABQ<T>::copyHelper(const ABQ& other) {
    this->_theData = other._theData;
    this->_actualSize = other._actualSize;
    this->_maxCapacity = other._maxCapacity;
    this->_scaleFactor = other._scaleFactor;
    this->_first = other._first;
    this->_totalResizes = other._totalResizes;

    for (int i = 0; i < other._maxCapacity; ++i) {
        this->_theData[i] = other._theData[i];
    }
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
    if (_actualSize == _maxCapacity) 
        resize(1);

    // Determine last index so that data is input in correct place. 
    if (_actualSize == 0) 
        lastIndex = _first; 
    else 
        lastIndex = ((_first + _actualSize) % _maxCapacity);

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
    if (_first > _maxCapacity) 
        _first = _first % _maxCapacity;

    // Logic for resize
    _actualSize--;
    float percentFilled = ((float)_actualSize / (float)_maxCapacity);
    if ( percentFilled < (1.0f / _scaleFactor)) {
        resize(-1);
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

// #### Resize 
// If control >= 0, resize array larger, else, resize it smaller. 
template<typename T>
void ABQ<T>::resize(int control) {
    _totalResizes++;
    unsigned int i;
    unsigned int iOldArray;
    unsigned int oldMax = _maxCapacity; // have to normalize capcity to the array largest index size. 

    // The following determiens if the data array will be getting larger or smaller. 
    if (control >= 0)
        _maxCapacity = _maxCapacity * _scaleFactor;
    else    
        _maxCapacity = _maxCapacity / _scaleFactor;

    T* temp = new T[_maxCapacity];    
    for (i = 0; i < _maxCapacity; ++i){
        // When the array is resized, _first is reset back to index 0, iOldArray is the transfer from _frist from the old array to 0 of the new array. 
        iOldArray = (i + _first) % (oldMax + 1);
        temp[i] = _theData[iOldArray];
    }

    _first = 0;
    delete[] _theData;
    _theData = temp; 
}