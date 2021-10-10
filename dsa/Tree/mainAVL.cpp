#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::vector;


class TreeNode {
 public:
   int val, height;
   TreeNode *left;
   TreeNode *right;
   TreeNode() : val(0), left(nullptr), right(nullptr) {}
   TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
   TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Node {
    public: 
        int name; // The name serves as the node's value
        Node* left = NULL;
        Node* right = NULL;
};

//char insertHelper(TreeNode** root, int value);
/////////////////////////////////////////////////////////////////////////////
// Rotation of trees

// We have provided for you a diagram to aid with visualization/debugging :)
/*

             C                    B                    A
            / \                 /   \                 / \
           B   Z               A     C               W   B
          / \       right     / \   / \      left       / \
         A   Y     ------>   W   X Y   Z   <------     X   C
        / \                                               / \
        W   X                                             Y   Z

*/

Node* rotateLeft(Node *node) {
    Node* grandChildNode = node->right->left;
    Node* newRoot = node->right;
    newRoot->left = node;
    node->right = grandChildNode;
    return newRoot;
}

Node* rotateRight(Node *node) {
    Node* grandChildNode = node->left->right;
    Node* newRoot = node->left;
    newRoot->right = node;
    node->left = grandChildNode;
    return newRoot;
}

Node* rotateLeftRight(Node *node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

void levelOrder(TreeNode* root, int level, vector<int>& result) {
    if (root == nullptr) return;
    if (result.size() <= level) {
        result.push_back(0);
    }
    result.at(level) += root->val;
    level++;
    levelOrder(root->left, level, result);
    levelOrder(root->right, level, result);
}

vector<int> levelOrder(TreeNode* root) {
    vector<int> result;
    result.push_back(root->val);
    int level = 1;
    levelOrder(root->left, level, result);
    levelOrder(root->right, level, result);
    return result;
}
///////////////////////////////////////////////////////////////////////////////
// Make a new balanced tree with TreeNode

TreeNode* rotateLeft(TreeNode *node) {
    TreeNode* grandChildNode = node->right->left;
    TreeNode* newRoot = node->right;
    newRoot->left = node;
    node->right = grandChildNode;
    return newRoot;
}

TreeNode* rotateRight(TreeNode *node) {
    TreeNode* grandChildNode = node->left->right;
    TreeNode* newRoot = node->left;
    newRoot->right = node;
    node->left = grandChildNode;
    return newRoot;
}

TreeNode* rotateLeftRight(TreeNode *node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

TreeNode* rotateRightLeft(TreeNode *node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

int heightOfNode(TreeNode* node) {
    int heightLeft = 0;
    int heightRight = 0;
    if (node == nullptr) return 0;
    if(node->left != nullptr) 
        heightLeft += heightOfNode(node->left);
    else if(node->right != nullptr) 
        heightRight += heightOfNode(node->right);

    if(heightRight > heightLeft) 
        return heightRight + 1;
    else 
        return heightLeft + 1;
}

char insertHelper(TreeNode** root, int value) {
    int balance = 0;
    int childBalance = 0;
    if (*root == nullptr) {
        *root = new TreeNode(value);
        return 0;
    }
    if (value <= (*root)->val) {
        childBalance = insertHelper(&(*root)->left, value);
    }
    else if (value > (*root)->val) {
        childBalance = insertHelper(&(*root)->right, value);
    }

    // Find height of node
    int left = heightOfNode((*root)->left);
    int right = heightOfNode((*root)->right);
    balance = heightOfNode((*root)->left) - heightOfNode((*root)->right);

    // Balance if needed
    if (balance > 1 && childBalance == -1) {
        *root = rotateLeftRight(*root);
    }
    else if (balance < -1 && childBalance == 1) {
        *root = rotateRightLeft(*root);
    }
    else if (balance > 1) {
        *root = rotateRight(*root);
    }
    else if (balance < -1) {
        *root = rotateLeft(*root);
    }

    return balance;
}

TreeNode* insert(TreeNode** root, int value) {
    int balance = insertHelper(root, value);
    if (balance >= 2) return rotateRight((*root));
    if (balance <= -2) return rotateLeft((*root));
    return *root;
}

void convertToBBSTHelper(TreeNode* root, TreeNode** newRoot) {
    if (root == nullptr) return;
    convertToBBSTHelper(root->left, newRoot);
    *newRoot = insert(newRoot, root->val);
    convertToBBSTHelper(root->right, newRoot);
}

TreeNode* convertToBBST(TreeNode* root) {
    TreeNode* newRoot = nullptr;
    if (root != nullptr) {
        convertToBBSTHelper(root, &newRoot);
    }
    return newRoot;
}


void traverse(TreeNode* root) {
    if (root != nullptr) {
        traverse(root->left);
        cout << root->val << " ";
        traverse(root->right);
    }
}

void preOrder(TreeNode* root) {
    if (root != nullptr) {
        cout << root->val << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void printvector(vector<int>& vect) {
    for (int i = 0; i < vect.size(); i++) {
        cout << i << ": " << vect.at(i) << endl;
    }
}

void checkPerfect(TreeNode* root, vector<int>& counterVect, int height) {
    int rightHeight = height;
    if (root->left == nullptr && root->right == nullptr) return;
    if (counterVect.size() == height) {
        counterVect.push_back(0);
    }
    if (root->left != nullptr) {
        counterVect.at(height)++;
        checkPerfect(root->left, counterVect, ++height);
    }
    if (root->right != nullptr) {
        counterVect.at(height)++;
        checkPerfect(root->right, counterVect, ++rightHeight);
    } 
}

bool checkPerfect(TreeNode* root) 
{
    //Returns if a tree is a perfect BST or not
    int height = 1;
    vector<int> counterVect;
    counterVect.push_back(0);
    if (root != nullptr) counterVect.at(0)++;

    checkPerfect(root, counterVect, height);

    int size = counterVect.size();
    if (size == 1) {
        return true;
    }
    else {
        for (int i = 1; i < size; i++) {
            if ((i * 2) != counterVect.at(i)) {
                return false;
            }
        }
    }
    return true;

}

/////////////////////////////////////////////////////////////////////////
// BALANCED TREE 2, 
// 5.2.1
int isAVLHelper(Node* node, char& isAVL) {
    if (node == nullptr) return 1;
    int left = isAVLHelper(node->left, isAVL);
    int right = isAVLHelper(node->right, isAVL);
    int result = left - right;
    cout << "result " << result << endl;
    if (result > 1 || result < -1) isAVL = 0;
    if (left > right) return 1 + left;
    else return 1 + right;
}

bool isAVL(Node* root) {
    char isAVL = 1;
    isAVLHelper(root, isAVL);
    if (isAVL == 1) return true;
    else return false;
}
/////////////////////////////////////////////////////////////////////////
// BALANCED TREE 2, 
// 5.2.2
TreeNode* insert(TreeNode* root, int key)
{
    // Base case of recursion we get to a nullptr
    if (root == nullptr) {
        TreeNode* newNode = new TreeNode(key);
        root = newNode;
        return root;
    }
    // Searching for apporpriate position. Recursion
    // Does not handle case of equal keys
    if (key < root->val) root->left = insert(root->left, key);
    else                 root->right = insert(root->right, key);
    
    // Set Height after completing the insertion. Leaf nodes have heigh of 0. 
    // Root has max height.
    if (root->right == nullptr) 
        root->height =  1 + root->left->height;
    else if (root->left == nullptr) 
        root->height =  1 + root->right->height;
    else if (root->left->height > root->right->height) 
    root->height =  1 + root->left->height;
    else 
    root->height =  1 + root->right->height;

    return root;
}

int main (void) {
    cout << "########################################################################" << endl;
    TreeNode* root = new TreeNode(5);
    insert(root, 3);
    insert(root, 7);
    insert(root, 1);
    insert(root, 4);
    insert(root, 6);

    cout << endl;
    cout << "########################################################################" << endl;




    //Node* center = new Node;
    //Node* left = new Node;
    //Node* leftLeft = new Node;
    //Node* right = new Node;
    //Node* rightRight = new Node;
    //Node* rightLeft = new Node;
    //Node* rightLeftRight = new Node;
    //Node* rightLeftRightRight = new Node;

    //                                        center->left = left; 
    //                    left->left = leftLeft;                              center->right = right;
    //                                            right->left = rightLeft;                        // right->right = rightRight;
    //                                                    rightLeft->right = rightLeftRight; 
    
    // 
    ////rightLeftRight->right = rightLeftRightRight;
    //cout << isAVL(center);

    //cout << endl;
    //cout << "########################################################################" << endl;

    //TreeNode* node1 = new TreeNode(1);
    //TreeNode* node4 = new TreeNode(4);
    //TreeNode* node7 = new TreeNode(7);
    //TreeNode* node9 = new TreeNode(9);
    //TreeNode* node10 = new TreeNode(10);
    //TreeNode* node12 = new TreeNode(12);
    //node9->left = node7;
    //node9->right = node12;
    //// Right Side
    //node12->left = node10;
    //// Left side
    //node7->left = node1;
    //node1->right = node4;

    //TreeNode* testEasy9 = new TreeNode(9);
    //TreeNode* testEasy7 = new TreeNode(7);
    //TreeNode* testEasy1 = new TreeNode(1);
    //testEasy9->left = testEasy7;
    //testEasy7->left = testEasy1;


    //traverse(node9);
    //cout << endl;
    //preOrder(node9);
    //cout << endl;

    //cout << "########################################################################" << endl;

    //TreeNode* newTree = nullptr;
    //newTree = insert(&newTree, 25);
    //preOrder(newTree);
    //cout << endl;
    //newTree = insert(&newTree, 22);
    //preOrder(newTree);
    //cout << endl;
    //newTree = insert(&newTree, 4);
    //preOrder(newTree);
    //cout << endl;
    //newTree = insert(&newTree, 1);
    //preOrder(newTree);
    //cout << endl;
    //newTree = insert(&newTree, 2);
    //preOrder(newTree);
    //cout << endl;
    //newTree = insert(&newTree, 28);
    //preOrder(newTree);
    //cout << endl;
    //newTree = insert(&newTree, 30);
    //preOrder(newTree);
    //cout << endl;
    //newTree = insert(&newTree, 3);
    //preOrder(newTree);
    //cout << endl;
    //cout << endl;
    //cout << "height " <<  heightOfNode(newTree) << endl;
    //cout << endl;
    //vector<int> result2 = levelOrder(newTree);
    //for (int i = 0; i < result2.size(); i++) {
    //    cout <<result2.at(i) << endl;
    //}

    //cout << "########################################################################" << endl;
    //TreeNode* test = nullptr;
    //test = convertToBBST(node9);
    //preOrder(test);
    //cout << endl;
    //vector<int> result = levelOrder(test);
    //for (int i = 0; i < result.size(); i++) {
    //    cout <<result.at(i) << endl;
    //}
    //cout << "root: " << test->val << endl;
    //cout << "left: " << test->left->val << endl;
    //cout << "right: " << test->right->val << endl;

    //cout << "########################################################################" << endl;
    //TreeNode* perfectL = new TreeNode(1);
    //TreeNode* perfectR = new TreeNode(3);
    //TreeNode* wrong = new TreeNode(4);
    //TreeNode* testPerfect = new TreeNode(2, perfectL, perfectR);
    //perfectR->right = wrong;
    //cout << " Testing if perfect tree" << endl;
    //cout << "The result is: " << checkPerfect(testPerfect) << endl;
    
    return 0;
}