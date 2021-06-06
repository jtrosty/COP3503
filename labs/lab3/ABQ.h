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
    T* _theData;
    float _scaleFactor = 2.0f;
    
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
    T* getData();
};

