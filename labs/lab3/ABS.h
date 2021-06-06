#include <iostream>
#include <exception>
using std::cout;
using std::runtime_error;
using std::endl;

template <typename T>
class ABS {

    //############### Class Variables
    //###############################
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
    ABS(int capacity = 1);
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
     
     for (int i = 0; i < other._maxCapacity; ++i) {
         _theData[i] = other._theData[i];
     }
     return *this;
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

// Push data <T> onto stack
template<typename T>
void ABS<T>::push(T data) {
    if (_actualSize == _maxCapacity) {
        resizeLarger();
    } 
    _theData[_actualSize - 1] = data;
    _actualSize++;
}

// Pop Data <T>
template<typename T>
T ABS<T>::pop() {
    try {
        if (_actualSize == 0) {
            throw runtime_error("Array is empty.");
        }
    }
    catch (runtime_error& e){
        cout << "Error: " << e.what() << endl;
    }
    _actualSize--;
    return _theData[_actualSize--];
}

// Peek Data <T>
template<typename T>
T ABS<T>::peek() {
    try {
        if (_actualSize == 0) throw runtime_error("Array is empty.");
    }
    catch (runtime_error& e){
        cout << "Error: " << e.what() << endl;
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
     _theData = new T[other._maxCapacity];
     _actualSize = other._actualSize;
     
     for (int i = 0; i < other._maxCapacity; ++i) {
         _theData[i] = other._theData[i];
     }
     return *this;
}

// Resize array larger
template<typename T>
void ABS<T>::resizeLarger() {
    T* temp = new T[_scaleFactor * _maxCapacity];    
    for (int i = 0; i < _maxCapacity; ++i){
        temp[i] = _theData[i];
        delete[] _theData[i];
    }
    _theData = temp;
    delete[] temp;
}

// Resize array smaller
// TODO finish not done
template<typename T>
void ABS<T>::resizeSmaller() {
    T* temp = new T[_maxCapacity / _scaleFactor];    
    for (int i = 0; i < _actualSize; ++i){
        temp[i] = _theData[i];
        delete[] _theData[i];
    }
    _theData = temp;
    delete[] temp;
}
