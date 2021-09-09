#include <iostream>
#include <string.h>
#include <vector>
#include "other.h"
using std::cout;
using std::endl;
using std::string;


class Foo {
    public:
    int classValue;
    const Foo& SomeClassFunction() {
        this->classValue = 4;
        return *this;
    }
};

class second {
    public:
    int hello;
    second();
    int constTestClass(int& value) const;
    char* bye;
    std::vector<test> vectOfTest;
};

int second::constTestClass(int& value) const {
    value++;
    cout << value << endl;
    return value;
}


second::second() {
    bye = "hello";
}


void swappyBoi(int* swapA, int* swapB) {
    swapA = swapB;
}

void swappyGuy(int& swapA, int& swapB) {
    swapA = swapB;
}

bool checkPalindrome(string s) {
    if (s.size() == 1) {
        return true;
    }
    if (s.size() == 2) {
        if (s.at(0) == s.at(1)) return true;
        return false;
    }
    if (checkPalindrome(s.substr(1, s.size() - 2))) {
        if (s.at(0) == s.at(s.size() - 1)) return true;
        return false;
    }
    return false;
}

typedef struct tree {
    int data;
    struct tree* parent;
    struct tree* left;
    struct tree* right;
};

tree* searchTree(tree *l, int x) {
    if (l == nullptr) return (nullptr);
    if (l->data == x) return l;
    if (x < l->data) {
        searchTree(l->left, x);
    }
    else{
        searchTree(l->right, x);
    }
}

tree* findMinimum(tree *t) {
    tree* min;
    if (t == nullptr) return nullptr;
    min = t;
    while(min->left != nullptr) {
        min = min->left;
    }
    return min;
}

tree* findMaximum(tree *t) {
    tree* max;
    if (t == nullptr) return nullptr;
    max = t;
    while(max->left != nullptr) {
        max = max->left;
    }
    return max;
}

void treeTraversal(tree* t) {
    if (t != nullptr) {
        treeTraversal(t->left);
        cout << t->data << endl;
        treeTraversal(t->right);
    }
}

void insertTree(tree** l, int data, tree *parent) {
    tree* temp; // temp pointer
    if(*l == nullptr) {
        temp = (tree*)malloc(sizeof(tree)); // allocate data for the pointer
        temp->data = data;
        temp->left = nullptr;
        temp->right = nullptr;
        *l = temp;
        return;
    }
    if (data < (*l)->data) {
        insertTree(&((*l)->left), data, *l);
    }
    else {
        insertTree(&((*l)->right), data, *l);
    }
}

void deleteTreeNode(tree** l, int data) {
    tree* temp;
    if (*l == nullptr) return;
    tree* nodeToDelete = searchTree(*l, data);
    // NO c
    hildren
        if (nodeToDelete->left == nullptr && nodeToDelete->right == nullptr) {
        delete nodeToDelete;
        nodeToDelete = nullptr;
    }
    // 1 child
    else if (   (nodeToDelete->left != nullptr && nodeToDelete->right == nullptr) 
             || (nodeToDelete->left == nullptr && nodeToDelete->right != nullptr)) {
        // left child
        if (nodeToDelete->left != nullptr) {
            temp = nodeToDelete->left;
            temp->parent = nodeToDelete->parent;
            delete nodeToDelete;
        }
        // Rigth child
        if (nodeToDelete->right != nullptr) {
            temp = nodeToDelete->right;
            temp->parent = nodeToDelete->parent;
            delete nodeToDelete;
        }
    }
    // 2 children 
    else if (nodeToDelete->left != nullptr && nodeToDelete->right != nullptr) {
        
        
    }
}


string peakyString(string[] str) {
    int numOfStrings = str.size();
    if (numOfStrings == 1 || numOfStrings == 0) {
        return NULL;
    }
    for (int i = 0; i < numOfStrings; i++) {
        if (i == 0) {
            if (str[0].size() > str[1].size()) return str[0];
        }
        else if (i == size - 1) {
            if (str[i].size() > str[i - 1].size()) return str[i];
        }
        if (str[i].size() > str[i -1].size() && str[i].size() < str[i + 1].size()) 
            return str[i];
    }
}




int main(void) {
    cout << checkPalindrome("ABBBCA");
    int a = 5;
    int b = 9;
    swappyBoi(&a, &b); 
    cout << endl;
    cout << "test swappyBoi" << endl;
    cout << a << b << endl;
    
    swappyBoi(&a, &b); 
    cout << endl;
    cout << "test swappyGuy" << endl;
    cout << a << b << endl;
    
    
    /*
    
    void passPointer(int* rhs) {
        *rhs += 1;
    }
    
        cout << "Hlleo" << endl;
    
        unsigned int a = -23;
        cout << "unsigned int: " << a << endl;
    
        int x = 10;
        int y = 30;
        int& b = x;
        int* c = &x;
    
        cout << "x: " << b << endl;
        cout << "pointer " << c << endl;
        cout << "pontee " << *c << endl;
    
        b = y; 
    
        cout << "y from b: " << b << endl;
        cout << "x haver 'b = y': " << x << endl;
        passPointer(c);
        cout << "c after passPointer " << *c << endl;
    
        string stringA = "hello";
        string stringB = "hello";
        if ( stringA == stringB) {
            cout << " they are equal" << endl;
        }
        else {
            cout <<  "they are not equal" << endl;
        }
        */
    return 0;
}