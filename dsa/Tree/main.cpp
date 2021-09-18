#include <iostream>
#include <exception>
#include <vector>
#include <list>
#include <string>
using std::cout;
using std::endl;
using std::vector;

long sumVector(std::vector<int> arr); 
long sumVectorModN(std::vector<int> arr, int n); 

/////////////////////////////////////////////////////////
// Used by some of the problmes Code given by assignment
class Node {
    public:
    int val;
    vector<Node*> children;
    // Constructor
    Node() {}
    // Constructor with stuff
    Node(int _val) {
        val = _val;
    }
    // Constructor with children
    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

/////////////////////////////////////////////////////////
// Used by some of the problmes Code given by assignment
 class TreeNode {
 public:
   int val;
   TreeNode *left;
   TreeNode *right;
   TreeNode() : val(0), left(nullptr), right(nullptr) {}
   TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
   TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

//////////////////////////////////////////////////////////
// Preorder problem, bascially, left to right
void preorder(Node* root) {
   // your code 
   cout << root->val << " ";
   for (int i = 0; i < root->children.size(); i++) {
       preorder(root->children.at(i));
   }
}

////////////////////////////////////////////////////////
// Traversing a tree by level the followign 2 functions are together
void levelOrder(vector<Node*>& level, int depth) {
    // End condition
    if (level.size() == 0) return;

    // Common Case
    vector<Node*> nextLevel;
    cout << "Level: " << depth << endl;
    for (int i = 0; i < level.size(); i++) {
        cout << level.at(i)->val << " ";
        for (int j = 0; j < level.at(i)->children.size(); j++) {
            nextLevel.push_back(level.at(i)->children.at(j));
        }
    }
    cout << endl;
    levelOrder(nextLevel, depth + 1);
}

void levelOrder(Node* root) {
    // Handles only the first level, the root
    vector<Node*> level;
    cout << "Level: 1" << endl;
    cout << root->val << " " << endl;
    for (int i = 0; i < root->children.size(); i++) {
        level.push_back(root->children.at(i));
    }
    levelOrder(level, 2);
}

/////////////////////////////////////////////////////////////
// Binary Tree Inorder Traversal

std::string traverse(TreeNode* root) {
    //your code here
    std::string result;
    if (root == nullptr) return "";
    result += traverse(root->left);
    result += std::to_string(root->val); 
    result += traverse(root->right);
    return result;
}

/////////////////////////////////////////////////////////////
// FLIP

void Flip(TreeNode* root) {
    // flip
    if (root == nullptr) return;
    TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;
    Flip(root->left);
    Flip(root->right);
}

/////////////////////////////////////////////////////////////
// Sum all the right leaves! leafs don't have nodes on them.
void sumOfRightLeaves(TreeNode* node, int& result) {
    if ((node->right != nullptr) && (node->right->left == nullptr) && (node->right->right == nullptr)) {
        result = result + node->right->val;
    }
    else if (node->right != nullptr) sumOfRightLeaves(node->right, result);
    if (node->left != nullptr) sumOfRightLeaves(node->left, result);
    return;
}

void sumOfRightLeaves(TreeNode* root) {
    if (!root) return;
    int temp = 0;
    int& result = temp;
    sumOfRightLeaves(root, result);
    cout << result;
}


int main (void) {
    // Setup
    Node* root = new Node(12);
    Node* root1 = new Node(1);
    Node* root2 = new Node(4);
    Node* root3 = new Node(5);
    Node* root4 = new Node(7);
    Node* root5 = new Node(11);
    Node* root6 = new Node(8);
    root->children.push_back(root1);
    root->children.push_back(root2);
    root->children.push_back(root3);
    root2->children.push_back(root4);
    root2->children.push_back(root5);
    root3->children.push_back(root6);

//       2
//    1     3 
//      9     4
    TreeNode* leftNode = new TreeNode(1);
    TreeNode* rightNode = new TreeNode(3);
    TreeNode* aNode = new TreeNode(4);
    TreeNode* bNode = new TreeNode(8);
    TreeNode* cNode = new TreeNode(9);
    TreeNode* start = new TreeNode(2, leftNode, rightNode);
    start->right->right = aNode;
    leftNode->right = cNode;
    
    preorder(root);
    cout << endl;
    levelOrder(root);
    cout << endl;
    cout << " traverse" << endl;
    cout << traverse(start);
    cout << "flip" << endl;
    //Flip(start);
    cout << traverse(start);
    cout << "sum of right leaves" << endl;
    sumOfRightLeaves(start);
    cout << endl;
    cout << " THis is " << start->left->right->left << endl;

    return 0;
}


long sumVector(std::vector<int> arr) {
    long acc = 0;
    for(int i = 0; i < arr.size(); i++) {
        acc += arr.at(i);
    }
    return acc;
}

long sumVectorModN(std::vector<int> arr, int n) {
    if (n <= 0) throw std::logic_error("Modular arithmetic undefined for non-positive integers!");
    return sumVector(arr) % n;
}
