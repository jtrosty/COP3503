#include <iostream>
using namespace std;

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

//Don't change main
int main() {

   int size;
   cin >> size;
   int* arr = new int[size];

    for(int i = 0; i < size; i++)
        cin >> arr[i];

   arr =  extractMax(arr, size);
   for(int i = 0; i < size - 1; i++)
      cout << arr[i] << " ";

   return 0;
}