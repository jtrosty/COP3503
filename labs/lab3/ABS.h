#pragma once
#include <iostream>
#include <exception>
using std::cout;
using std::runtime_error;
using std::endl;

template <typename T>
class ABS {

    //############### Class Variables ##################
    //##################################################
    unsigned int _actualSize;
    unsigned int _maxCapacity;
    T* _theData;
    float _scaleFactor = 2.0f;
    
    void resizeLarger();
    void resizeSmaller();
    ABS& copy(const ABS& other); // private copy funciton for copy constructor and copy assignment. 

//################ Public  #############################
//######################################################
    public: 

    ABS();
    ABS(int capacity);
    ABS(const ABS& other);
    ABS& operator=(const ABS& other);
    ~ABS();

    void push(T data);
    T pop();
    T peek();

//############### Getters and Setters ##################
//######################################################
    unsigned int getSize();
    unsigned int getMaxCapacity();
    T* getData();
};

// ######################################################
// ############## Class Definition ######################
// ######################################################

// #################### Default Constructor ##############
// Set capcity to 1 initialize array of T.
template<typename T>
ABS<T>::ABS() {
    _maxCapacity = 1;
    _actualSize = 0;
    _theData = new T[_maxCapacity];
}

// #################### Constructor #####################
// Set capcity to user input
template<typename T>
ABS<T>::ABS(int capacity) {
    _maxCapacity = capacity;
    _actualSize = 0;
    _theData = new T[_maxCapacity];
}

// #################### Big 3 ############################
// #######################################################
// Destrutor
template<typename T>
ABS<T>::~ABS() {
    delete[] _theData;
}

// Copy Constructor
template<typename T>
ABS<T>::ABS(const ABS& other) {
     _theData = new T[other._maxCapacity];
     _actualSize = other._actualSize;
     _maxCapacity = other._maxCapacity; 

     for (int i = 0; i < other._maxCapacity; ++i) {
         _theData[i] = other._theData[i];
     }
}

// Copy Assignment 
template<typename T>
ABS<T>& ABS<T>::operator=(const ABS& other) {
     _theData = new T[other._maxCapacity];
     _actualSize = other._actualSize;
     
     for (int i = 0; i < other._maxCapacity; ++i) {
         _theData[i] = other._theData[i];
     }
     return *this;
}

// PUSH data <T> onto stack
// Controls if resize larger occurs. 
template<typename T>
void ABS<T>::push(T data) {
    if (_actualSize == _maxCapacity) {
        resizeLarger();
    } 
    _theData[_actualSize] = data;
    _actualSize++;
}

// POP Data <T>
// The function controls when to resize smaller. 
template<typename T>
T ABS<T>::pop() {
    // Check if array is empty
    if (_actualSize == 0) {
        throw runtime_error("Array is empty, unable to pop.");
    }
    // TODO: cout << "stuff " << _maxCapacity << ", " << _scaleFactor << endl;
    // Resize smalle if STRICTLY (size / maxCapacity) < (1 / scale factor) so a float cast is used
    _actualSize--;
    float percentFilled = ((float)_actualSize / (float)_maxCapacity);
    if ( percentFilled < (1.0f / _scaleFactor)) {
        resizeSmaller();
    } 
    return _theData[_actualSize]; // No need to decremetnt during return because of decrement above. 
}

// Peek Data <T>
template<typename T>
T ABS<T>::peek() {
    // Check if array is empty
    if (_actualSize == 0) {
        throw runtime_error("Array is empty, unable to pop.");
    }
    return _theData[_actualSize - 1];
}

// Get actual size of the Data Array
template<typename T>
unsigned int ABS<T>::getSize() {
    return _actualSize;
}

// Get max capcity of the array
template<typename T>
unsigned int ABS<T>::getMaxCapacity() {
    return _maxCapacity;
}

// Get data
template<typename T>
T* ABS<T>::getData() {
    return _theData;
}

// Private copy function for copy constructor and copy assignment operator
template<typename T>
ABS<T>& ABS<T>::copy(const ABS& other) {
    unsigned int i;
    _theData = new T[other._maxCapacity];
    _actualSize = other._actualSize;
     
    for (i = 0; i < other._maxCapacity; ++i){
        _theData[i] = other._theData[i];
    }
    return *this;
}

// Resize array larger
template<typename T>
void ABS<T>::resizeLarger() {
    unsigned int i;
    _maxCapacity = _scaleFactor * _maxCapacity;
    T* temp = new T[_maxCapacity];    
    for (i = 0; i < _maxCapacity; ++i){
        temp[i] = _theData[i];
    }
    delete[] _theData;
    _theData = temp;
}

// Resize array smaller
// TODO finish not done
template<typename T>
void ABS<T>::resizeSmaller() {
    unsigned int i;
    _maxCapacity = _maxCapacity / _scaleFactor;
    T* temp = new T[_maxCapacity];    
    for (i = 0; i <= _actualSize; ++i){
        temp[i] = _theData[i];
    }
    delete[] _theData;
    _theData = temp;
}