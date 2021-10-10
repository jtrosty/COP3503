#include <iostream>
#include <vector>
using std::vector;

class Solution {
public:
    struct TreeNode {
        int val;
        TreeNode* left;
        TreeNode* right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    };

    TreeNode* insert(TreeNode* root, int key) {
        if (root == nullptr) {
            TreeNode* newNode = new TreeNode(key);
            root = newNode;
        }
        else if ( key < root->val) {
            if (root->left == nullptr) {
                TreeNode* newNode = new TreeNode(key);
                root->left = newNode;
            }
            else insert(root->left, key);
        }
        else {
            if (root->right == nullptr) {
                TreeNode* newNode = new TreeNode(key);
                root->right = newNode;
            }
            else insert(root->right, key);

        }
        return root;
    }

    TreeNode* search(TreeNode* root, int key) {
        if (root == nullptr) return nullptr;
        do {
            if (root->val == key) return root;
            if (root->val < key) root = root->left;
            else root = root->right;
        }
        while (root != nullptr);
        return root;
    }

    vector<int> twoSum(vector<int>& numbers, int target) {
        int size = numbers.size();
        TreeNode* root = new TreeNode();
        for (int i = 0; i < size; i++) {
            insert(root, numbers[i]);
        }

        for (int i = 0; i < size; i++) {

        }
    }

    void heapifyDown(vector<int>& stones, int index, int size) {
        int left = -1;
        int right = -1;
        int bigger = -1;
        int temp = 0;

        while (index < size - 1) {
            left = (index * 2) + 1;
            right = (index * 2) + 2;
            bigger = -1;
            //std::cout << "bigger: " << bigger <<" Left: " << left << " right: " << right << " index " << index << std::endl;

            if (right < size || left < size) {
                if (right < size && left < size) {
                    if (stones.at(right) > stones.at(left)) bigger = right;
                    else if (left <= (size -1)) bigger = left;
                }
                else if ( right < size) bigger = right;
                else if ( left < size) bigger = left;
            }
            if (bigger != -1) {
                if (stones.at(index) < stones.at(bigger)) {
                    temp = stones.at(index);
                    stones.at(index) = stones.at(bigger);
                    stones.at(bigger) = temp;
                }
                index = bigger;
            }
            else break;
        }
    }

    void heapifyUp(vector<int>& stones, int index, int size) {
        int parent = (index -1) / 2;
        int temp = -1;
        //std::cout << "heapifyup" << std::endl;
        //std::cout << "index " << index << " size " << size << " parent " << parent << std::endl;

        while (parent >= 0 && stones.at(parent) < stones.at(index)) {
            temp = stones.at(parent);
            stones.at(parent) = stones.at(index);
            stones.at(index) = temp;
            index = parent;
            parent = (index - 1) / 2;
        }
    }

    int extractmax(vector<int>& heap, int& size) {
        int result = heap.at(0);
        size--;
        heap.at(0) = heap.at(size);
        heapifyDown(heap, 0, size);
        return result;
    }

    void sortHeap(vector<int>& heap, int& size) {
        for (int i = size / 2; i >= 0; i--) {
            heapifyDown(heap, i, size);
        }
    }

    void insert(vector<int>& heap, int& size, int key) {
        size++;
        if (heap.size() < size) heap.push_back(key);
        else {
            heap.at(size - 1) = key;
        }
        heapifyUp(heap, size - 1, size);
    }

    int lastStoneWeight(vector<int>& stones) {
        int size = stones.size();
        int firstStone = -1;
        int secondStone = -1;
        int result = -1;
        sortHeap(stones, size);
        while (size > 1) {
            firstStone = extractmax(stones, size);
            secondStone = extractmax(stones, size);
            result = firstStone - secondStone;
            if (result <= 0) continue;
            else {
                insert(stones, size, result);
            }
        }
        if (size == 1) return stones[0];
        else return 0;
    }

    void printHeap (vector<int>& heap, int& size) {
        for (int i = 0; i < size; i++) {
            std::cout << heap.at(i) << " ";
        }
        std::cout << std::endl;
    }
};



int main(void) {
    Solution solution;
    vector<int>* heap = new vector<int>;
    heap->push_back(2);
    heap->push_back(7);
    heap->push_back(4);
    heap->push_back(1);
    heap->push_back(8);
    heap->push_back(1);
    int size = heap->size();
    std::cout << "answer " << solution.lastStoneWeight(*heap);
    //solution.printHeap(*heap, size);
    //solution.sortHeap(*heap, size);
    //solution.printHeap(*heap, size);
    //std::cout << "extract " << solution.extractmax(*heap, size) << std::endl;
    //solution.printHeap(*heap, size);
    //std::cout << "extract " << solution.extractmax(*heap, size) << std::endl;
    //solution.printHeap(*heap, size);
    //solution.insert(*heap, size, 5);
    //solution.printHeap(*heap, size);
}