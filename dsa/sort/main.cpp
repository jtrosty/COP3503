#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

void heapify_down(vector<int>& arr, int size, int root); 

class Node {
public:
        int value;
        Node* next;
        Node() {next = nullptr;}
        Node(int val) {value = val; next = nullptr;}
};

void merge(vector<int>& array, int start, int middle, int end, vector<int>& temp) {
    int i = start;
    int j = middle;
    for (int k = start; k < end; k++) {
        if ((j >= end || temp.at(i) < temp.at(j)) && i < middle) {
            array.at(k) = temp.at(i);
            i++;
        }
        else if (j < end) {
            array.at(k) = temp.at(j);
            j++;
        }
    }
}

void split(vector<int>& array, int start, int end, vector<int>& temp) {
    if (end - start <= 1) return;
    int middle = (end + start) / 2;
    split(temp, start, middle, array);
    split(temp, middle, end, array);
    merge(array, start, middle, end, temp);
}

Node* sortList(Node* head) {
    vector<int> list;
    vector<int> tempList;
    Node* temp = head;
    while (temp != nullptr) {
        list.push_back(temp->value);
        tempList.push_back(temp->value);
        temp = temp->next;
    }
    split(list, 0, list.size(), tempList);
    temp = head;
    for (int i = 0; i < list.size(); i++) {
        temp->value = list.at(i);
        temp = temp->next;
    }
    return head;
}

int main(void) {
    cout << "success" << endl;
    Node q(3);
    Node q1(2);
    Node q2(4);
    Node q3(9);
    Node q4(1);
    q.next = &q1;
    q1.next = &q2;
    q2.next = &q3;
    q3.next = &q4;
    q = *sortList(&q);

    vector<int> test = { 1, 7, 5, 2, 3, 8, 9, 10, 4, 6};

    return 0;
}

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