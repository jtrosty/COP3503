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
// Private items
    unsigned int _actualSize;
    unsigned int _maxCapacity;
    unsigned int _totalResizes;
    T* _theData;
    float _scaleFactor;
    
    void resize(int control);
    void copyHelper(const ABS& other); // private copy funciton for copy constructor and copy assignment. 

//################ Public  #############################
//######################################################
    public: 

    ABS();
    ABS(int capacity);
    ABS(int capacity, float scaleFactor);
    ABS(const ABS& other);
    ABS& operator=(const ABS& other);
    void test_DEBUG();
    ~ABS();

    void push(T data);
    T pop();
    T peek();

//############### Getters and Setters ##################
//######################################################
    unsigned int getSize();
    unsigned int getMaxCapacity();
    unsigned int getTotalResizes();
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
    _scaleFactor = 2.0f;
    _totalResizes = 0;
    _theData = new T[_maxCapacity];
}

// #################### Constructor #####################
// Set capcity to user input
template<typename T>
ABS<T>::ABS(int capacity) {
    _maxCapacity = capacity;
    _actualSize = 0;
    _scaleFactor = 2.0f;
    _totalResizes = 0;
    _theData = new T[_maxCapacity];
}

template<typename T>
ABS<T>::ABS(int capacity, float scaleFactor) {
    _maxCapacity = capacity;
    _actualSize = 0;
    _scaleFactor = scaleFactor;
    _totalResizes = 0;
    _theData = new T[_maxCapacity];
}

// #################### Big 3 ############################

// Destrutor
template<typename T>
ABS<T>::~ABS() {
    delete[] _theData;
}

// Copy Constructor
template<typename T>
ABS<T>::ABS(const ABS& other) {
    copyHelper(other);
}

// Copy Assignment 
template<typename T>
ABS<T>& ABS<T>::operator=(const ABS& other) {
     copyHelper(other);
     return *this;
}

// Private copy function for copy constructor and copy assignment operator
template<typename T>
void ABS<T>::copyHelper(const ABS& other) {
    unsigned int i;
    this->_theData = new T[other._maxCapacity];
    this->_actualSize = other._actualSize;
    this->_scaleFactor = other._scaleFactor;
    this->_totalResizes = other._totalResizes;
     
    for (i = 0; i < other._maxCapacity; ++i){
        this->_theData[i] = other._theData[i];
    }
}

// ################## Getters and Setters ################################## 

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

template<typename T>
unsigned int ABS<T>::getTotalResizes() {
    return _totalResizes;
}

// Get data
template<typename T>
T* ABS<T>::getData() {
    return _theData;
}

// ###########################################################################
// ################### Stack Behavior#########################################
// ###########################################################################

// PUSH data <T> onto stack
// Controls if resize larger occurs. 
template<typename T>
void ABS<T>::push(T data) {
    if (_actualSize == _maxCapacity) 
        resize(1);

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
    // Resize smaller if STRICTLY (size / maxCapacity) < (1 / scale factor) so a float cast is used
    _actualSize--;
    float percentFilled = ((float)_actualSize / (float)_maxCapacity);
    if ( percentFilled < (1.0f / _scaleFactor)) 
        resize(-1);

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

// Resize Array 
// If control >= 0 Make the array lareger, else the data array is made smaller.
template<typename T>
void ABS<T>::resize(int control) {
    _totalResizes++;
    // The following variables control the for loop that performs a copy of the data. 
    unsigned int i;
    unsigned int arraySize;

    // If control > 0, resize larger
    if (control >= 0) {
        arraySize = _maxCapacity;
        _maxCapacity = _maxCapacity * _scaleFactor;
    }
    // Resize smaller
    else  {
        _maxCapacity = _actualSize + 1; //_maxCapacity / _scaleFactor;
        arraySize = _actualSize + 1; // Adjust so actual size is normalized to a index of 0
    }

    T* temp = new T[_maxCapacity];    
    for (i = 0; i < arraySize; ++i){
        temp[i] = _theData[i];
    }
    delete[] _theData;
    _theData = temp;
}

// ONLY WORKS WITH INT DATA TYPE!!!
template<typename T>
void ABS<T>::test_DEBUG() {
    /*
    for (int i = 0; i < _actualSize; ++i) {
        cout << _theData[i] << " ";
    }
    */ 
    for (int i = 1; i < _actualSize; ++i) {
        if (_theData[i] != (_theData[i - 1] + 1)) {
            cout << "AGH FAIL at: " << i << endl; 
        }
    }
    //cout << "PASS" << endl; 
}