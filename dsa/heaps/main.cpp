#include <iostream>
#include <sstream>
//using namespace std;

int* extractMax(int arr[], int size) {
    //code here
    arr[0] = arr[size - 1];
    size--;

    int tracker = 0;
    int temp = 0;

    while ((arr[tracker] < arr[(2 * tracker) + 1] 
         || arr[tracker] < arr[(2 * tracker) + 2]) 
         && ((2 * tracker) < size - 1)) {
        if (arr[(2 * tracker) + 1] > arr[(2 * tracker) + 2]) {
            temp = arr[(2 * tracker) + 1];
            arr[(2 * tracker) + 1] = arr[tracker];
            arr[tracker] = temp;
            tracker = (2 * tracker) + 1;
        }
        else {
            temp = arr[(2 * tracker) + 2];
            arr[(2 * tracker) + 2] = arr[tracker];
            arr[tracker] = temp;
            tracker = (2 * tracker) + 2;
        }
    }
    return arr;
}

//////////////////////////////////////////////////////////////////////
//                   Heap 6.1.1

int readHeap(int* theheap)
{
    //your code here
    //use std::cin to read in the data
    //return the size of the heap   
    std::string input;
    int counter = 0;
    for ( ; input != "-1" ; getline(std::cin, input, ' ')) {
        theheap[counter] = std::stoi(input);
    }
    return ++counter;
}

void heapRemove(int* theheap, int& size)
{
   //your code here  
   // 'Delete' the first nod,e reduce the size of the array.
   theheap[0] = theheap[size--];
   int root = 0;
   int leftChild = 1;
   int rightChild = 2;
   int temp = 0;

   while(theheap[root] > theheap[leftChild] || theheap[root] > theheap[rightChild]) {
       if (theheap[leftChild] < theheap[rightChild] && leftChild < size) {
           temp = theheap[leftChild];
           theheap[leftChild] = theheap[root];
           theheap[root] = temp;
           root = leftChild;
       }
       if (theheap[rightChild] < theheap[leftChild] && rightChild < size) {
           temp = theheap[rightChild];
           theheap[rightChild] = theheap[root];
           theheap[root] = temp;
           root = rightChild;
       }
        leftChild = (2 * root) + 1;
        rightChild = (2 * root) + 2;
    }
}

void heapPrint(int* theheap, int size)
{
    //use cout to print the array representing the heap
    for (int i = 0; i < size; i++) {
        std::cout << theheap[i] << " ";
    }
}

//Don't change main
int main() {

////////////////////////////////////////////
// HEAP Quiz
/*
   int size;
   cin >> size;
   int* arr = new int[size];

    for(int i = 0; i < size; i++)
        cin >> arr[i];

   arr =  extractMax(arr, size);
   for(int i = 0; i < size - 1; i++)
      cout << arr[i] << " ";

   return 0;
   */
}