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
    unsigned int _last;

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
    unsigned int getLast();
    T at(int index);
    T* getData();
};

// ######################################################
// ############## Class Definition ######################
// ######################################################

// ############## Default Constructor ###################
/// Set
template<typename T>
ABQ<T>::ABQ() {
    _maxCapacity = 1;
    _actualSize = 0;
    _theData = new T[_maxCapacity];
    _first = 0;
    _last = 0;
}

template<typename T>
ABQ<T>::ABQ(int capacity) {
    _maxCapacity = capacity;
    _actualSize = 0;
    _theData = new T[_maxCapacity];
    _first = 0;
    _last = 0;
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
unsigned int ABQ<T>::getLast() {
    return _last;
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
    _last = other._last;

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
    _last = other._last;

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
    if (_actualSize == _maxCapacity) resizeLarger();

    _actualSize++;
    _theData[_last++] = data;
    if (_last >= _maxCapacity) _last = _last - _maxCapacity;
}

// #### Dequeue
template<typename T>
T ABQ<T>::dequeue() {
    if (_actualSize == 0) 
        throw runtime_error("Data structure is empty, unable to dequeue.");
    if (_first >= _maxCapacity) _first = _first - _maxCapacity;

    _actualSize--;

    float percentFilled = ((float)_actualSize / (float)_maxCapacity);
    if ( percentFilled < (1.0f / _scaleFactor)) {
        resizeSmaller();
    }  
    return _theData[_first++];
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
    _maxCapacity = _scaleFactor * _maxCapacity;
    T* temp = new T[_maxCapacity];    
    for (i = 0; i < _maxCapacity; ++i){
        temp[i] = _theData[i];
    }
    _first = 0; 
    _last = _actualSize;
    delete[] _theData;
    _theData = temp; 
}

// #### Resize Smaller 
template<typename T>
void ABQ<T>::resizeSmaller() {
    unsigned int i;
    _maxCapacity = _maxCapacity / _scaleFactor;
    T* temp = new T[_maxCapacity];    
    for (i = 0; i <= _actualSize; ++i){
        temp[i] = _theData[i];
    }
    _first = 0; 
    _last = _actualSize;
    delete[] _theData;
    _theData = temp;
}
