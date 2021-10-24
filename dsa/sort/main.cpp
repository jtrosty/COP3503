#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

void heapify_down(vector<int>& arr, int size, int root) {
    int child1 = (root * 2) + 1;
    int child2 = (root * 2) + 2;
    int temp = - 1;
    if (child1 > size - 1) return;
    else if (child1 == size - 1) {
        if (arr.at(root) < arr.at(child1)) {
            temp = arr.at(root);
            arr.at(root) = arr.at(child1);
            arr.at(child1) = temp;
            heapify_down(arr, size, child1);
        }
        else return;
    }
    else {
        if (arr.at(root) < arr.at(child1) || arr.at(root) < arr.at(child2)) {
            if (arr.at(child1) < arr.at(child2)) {
                temp = arr.at(root);
                arr.at(root) = arr.at(child2);
                arr.at(child2) = temp;
                heapify_down(arr, size, child2);
            }
            else {
                temp = arr.at(root);
                arr.at(root) = arr.at(child1);
                arr.at(child1) = temp;
                heapify_down(arr, size, child1);
            }
        }
        else return; 
    }
}

int main(void) {
    cout << "success" << endl;
    //vector<int> test = { 1, 7, 5, 2, 3, 8, 9, 10, 4, 6};

    return 0;
}