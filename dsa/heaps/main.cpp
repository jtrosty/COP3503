#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
using std::vector;

//////////////////////////////////////////////////////////////////////
//                   Heap 6.1.2
vector<double> findMedian(vector<int> arr) 
{ 
    vector<double> result;
    double temp;
    std::priority_queue< int, vector<int>, std::greater<int> > pq;
    std::priority_queue< int, vector<int>, std::greater<int> > pqSlow;
    for (int i = 0; i < arr.size(); i++) pq.push(arr.at(i));
    for (int i = 0; i < arr.size(); i++) {

        if (i == 0) {
            result.push_back(pq.top());
            pqSlow.push(pq.top());
        }
        else if (i % 2 == 0) {


        }
        else {
            temp = ((double)pq.top() + (double)pqSlow.top()) / 2.0;
            pqSlow.push(pq.top());
            result.push_back()
        }
        pq.pop();
    }
}

//////////////////////////////////////////////////////////////////////
//                   Heap 6.1.2
int kthlargest(vector<int>& nums, int k)
{
    std::priority_queue<int> pq;
    //your code here
    for (int i = 0; i < nums.size(); i++) pq.push(nums.at(i));
    for (int i = 1; i < k; i++) pq.pop();
    return pq.top();
}
//using namespace std;
//////////////////////////////////////////////////////////////////////
//                   Heap 6.1.1

int readHeap(int* theheap) {
    //your code here
    //use std::cin to read in the data
    //return the size of the heap   
    int input = 0;
    int endInput = -1;
    int counter = 0;

    std::cin >> input;
    while (input != endInput) { 
        theheap[counter] = input;
        std::cin >> input;
        counter++;
    }
    return counter;
}

void heapRemove(int* theheap, int& size)
{
   //your code here  
   // 'Delete' the first node reduce the size of the array.
   theheap[0] = theheap[(size - 1)];
   size--;
   int root = 0;
   int leftChild = 1;
   int rightChild = 2;
   int temp = 0;

   while ((theheap[root] > theheap[leftChild] 
        || theheap[root] > theheap[rightChild]) 
        && (leftChild < size || rightChild < size)) {
        //std::cout << "root " << root << std::endl;
        if (size - 1 == leftChild) {
            if (theheap[root] > theheap[leftChild]) {
                temp = theheap[root];
                theheap[root] = theheap[leftChild];
                theheap[leftChild] = temp;
                root = leftChild;
            }
        }
        else if (theheap[root] > theheap[leftChild] || theheap[root] > theheap[rightChild]) {
            if (theheap[leftChild] < theheap[rightChild]) {
                temp = theheap[leftChild];
                theheap[leftChild] = theheap[root];
                theheap[root] = temp;
                root = leftChild;
            }
            else {
                temp = theheap[rightChild];
                theheap[rightChild] = theheap[root];
                theheap[root] = temp;
                root = rightChild;
            }
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

//////////////////////////////////////////////////////////////////////////////
//                   Heap 6.1.3 isHeap
// size 1 2  3  4  5  6  7  8  9  10 11
//      0 1  2  3  4  5  6  7  8  9  10
//      0 0  1  1  2  2  3  3  4  4

bool isMinHeap(int arr[],int size)
{
    //code here
    int middle = (size - 1) / 2;
    // handles all nodes up to the last node in the 2nd to last level
    if (size == 1) return true;
    // Most common case
    for (int i = 0; i < middle; i++) {
        if (arr[i] > arr[(2 * i) + 1] || arr[i] > arr[(2 * i) + 2]) 
            return false;
    }
    // Handles the case of the last 2 nodes
    if (size - 1 == (2 * middle) + 1) {
        if (arr[middle] > arr[(2 * middle) + 1]) 
            return false;
    }
    else if (size - 1 == (2 * middle) + 2) {
        if (arr[middle] > arr[(2 * middle) + 1] || arr[middle] > arr[(2 * middle) + 2]) 
            return false;
    }
    return true;
}

bool isMaxHeap(int arr[],int size)
{
    //code here
    //code here
    int middle = (size - 1) / 2;
    // handles all nodes up to the last node in the 2nd to last level
    if (size == 1) return true;
    // Most common case
    for (int i = 0; i < middle; i++) {
        if (arr[i] < arr[(2 * i) + 1] || arr[i] < arr[(2 * i) + 2]) 
            return false;
    }
    // Handles the case of the last 2 nodes
    if (size - 1 == (2 * middle) + 1) {
        if (arr[middle] < arr[(2 * middle) + 1]) 
            return false;
    }
    else if (size - 1 == (2 * middle) + 2) {
        if (arr[middle] < arr[(2 * middle) + 1] || arr[middle] < arr[(2 * middle) + 2]) 
            return false;
    }
    return true;
}

int heapPlay(int arr[],int size)
{
    //code here
    bool maxHeap = false;
    bool minHeap = false;
    if (isMaxHeap(arr, size)) maxHeap = true; 
    if (isMinHeap(arr, size)) minHeap = true;
    std::cout << "maxHeap " << maxHeap << " minHeap " << minHeap << std::endl;

    if (maxHeap && minHeap) return 0;
    else if (maxHeap || minHeap) return arr[0];
    else return -1;
}

//Don't change main
int main() {
    int* theHeadp = new int[6];
    int size = 6;
    int arr[3] = {2, 1, 3};
    std::cout << heapPlay(arr, 3) << std::endl;;

    //readHeap(theHeadp);
    //heapRemove(theHeadp, size);
    //heapRemove(theHeadp, size);
    //heapPrint(theHeadp, size);

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