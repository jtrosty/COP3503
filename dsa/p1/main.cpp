#include <iostream>
#include <string>

using std::cout;
using std::endl;

///////////////////////////////////////////////////////////////////////////////////////
//                        Node Class that has the data a generic Node
///////////////////////////////////////////////////////////////////////////////////////
class Node {
    public:
        int gatorID;
        std::string name;
        Node* left;
        Node* right;
        int height;

        Node(std::string _name, int _gatorID);
        Node(std::string _name, int _gatorID, int _height);
};

Node::Node(std::string _name, int _gatorID) {
    gatorID = _gatorID;
    name = _name;
    left = nullptr;
    right = nullptr;
    height = 0;
}

Node::Node(std::string _name, int _gatorID, int _height) {
    gatorID = _gatorID;
    name = _name;
    left = nullptr;
    right = nullptr;
    height = _height;
}

///////////////////////////////////////////////////////////////////////////////////////
//                         Custom AVL Tree Class for Student Data 
///////////////////////////////////////////////////////////////////////////////////////
class TreeNode {
    private:

        // Balance funcitons
        Node* rotateLeft(Node* root);
        Node* rotateRight(Node* root);
        Node* rotateLeftRight(Node* root);
        Node* rotateRightLeft(Node* root);
        char insertHelper(Node** root, std::string name, int gatorID);

    public:
        Node* root = nullptr;

        // constructor
        TreeNode();
        TreeNode(std::string _name, int gatorID);

        // Operations
        char insert(std::string name, int gatorID);
        void remove(std::string gatorID);

        // Funciton to Print out tree
        void printFormat(Node* node);
        void printInorder(Node* root);
        void printPreorder(Node* root);
        void printPostorder(Node* root);
        void printLevelCount();
};

TreeNode::TreeNode() { }

TreeNode::TreeNode(std::string _name, int _gatorID) {
    Node* newRoot = new Node(_name, _gatorID);
    root = newRoot;
}

char TreeNode::insert(std::string _name, int _gatorID) {
    insertHelper(&root, _name, _gatorID);
}

char TreeNode::insertHelper(Node** _root, std::string _name, int _gatorID) {
    // All GatorIDs must be unique, the if handles the case if we find the same gatorID
    int balance = 0;
    char success = 0;
    if ((*_root)->gatorID == _gatorID) {
        return 0;
        cout << "UNSUCCESSFUL" << endl; 
    }
    else if (root == nullptr) {
        Node* newNode = new Node(_name, _gatorID, (*_root)->height + 1);
        (*_root) = newNode;
        return 1;
        cout << "SUCCESS" << endl; 
    }
    else if (_gatorID < (*_root)->gatorID) success = insertHelper(&(*_root)->left, _name, _gatorID);
    else if (_gatorID > (*_root)->gatorID) success = insertHelper(&(*_root)->right, _name, _gatorID);

    // Only want to balance if a node was succesfully inserted
    if (success) {
        // collect balance
        balance = (*_root)->left->height - (*_root)->right->height;

        if (balance > 1 && (*_root)->left->height == -1) {
            *_root = rotateLeftRight(*_root);
        }
        else if (balance > 1 && (*_root)->right->height == -1) {
            *_root = rotateRightLeft(*_root);
        }
        else if (balance > 1) {
            *_root = rotateRight(*_root);
        }
        else if ( balance < -1) {
            *_root = rotateLeft(*_root);
        }
    }
    else {

    }
}

///////////////////////////////////////////////////////////////////////////////////////
//         TreeNode Class Private rotation functions to Maintain Balance
///////////////////////////////////////////////////////////////////////////////////////
// We have provided for you a diagram to aid with visualization/debugging :)
/*

          C                    B                    A
         / \                 /   \                 / \
        B   Z               A     C               W   B
       / \       right     / \   / \      left       / \
      A   Y     ------>   W   X Y   Z   <------     X   C
     / \                                               / \
    W   X                                             Y   Z
    a height -1                                 a height +1
    c height +1                                 c height -1
    b height -1                                 b height -1

*/

Node* TreeNode::rotateLeft(Node *node) {
    Node* grandChildNode = node->right->left;
    Node* newRoot = node->right;
    newRoot->left = node;
    node->right = grandChildNode;
    return newRoot;
}

Node* TreeNode::rotateRight(Node *node) {
    Node* grandChildNode = node->left->right;
    Node* newRoot = node->left;
    newRoot->right = node;
    node->left = grandChildNode;
    return newRoot;
}

Node* TreeNode::rotateLeftRight(Node *node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

Node* TreeNode::rotateRightLeft(Node *node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      Main Function
/////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[]) {
    //We have received command line input
    char run = 1;
    size_t delimiter1 = -1;
    size_t delimiter2 = -1;
    std::string userInput;
    std::string command;
    std::string name;
    std::string gatorID;

    TreeNode* studentData = new TreeNode();

    while (run) {
        // COLLECT USER INPUT
        std::getline(std::cin, userInput);

        // Work thorugh user input determine if it contains a command, name, and ID, max will be all 3.
        // If the user input has a space, that implies there are 2 commands being input EX: remove
        // If the user input has 2 spaces that implies that there are 3 user input wors EX: insert
        if ((delimiter1 = userInput.find(' ')) != std::string::npos) {
            command = userInput.substr(0, delimiter1);
            // Check if second space, if so, record name and gator ID
            if ((delimiter2 = userInput.find("\"", delimiter1)) != std::string::npos) {
                cout << "SUCCESS" << endl;
                if ((delimiter2 = userInput.find("\"", delimiter1 + 2, 1)) != std::string::npos) {
                    cout << "SUCCESS 1: " << delimiter1 << ", " << delimiter2 << endl;
                    name = userInput.substr(delimiter1 + 2, (delimiter2 - delimiter1 - 2));
                    gatorID = userInput.substr(delimiter2 + 2, std::string::npos);
                }
                else {
                    // FAIL
                }
            }
            // Not a name, just a user id.
            else {
                gatorID = userInput.substr(delimiter1 + 1, std::string::npos);
            }
        }
        // This is if there is only 1 user input
        else {
            command = userInput;
        }

        // USER INPUT HAS BEE RECIEVED AND SAVED, NOW TO PARSE IT FOR THE FUNCTIONS
        if (command == "insert"){
            cout << "command: " << command << " name: " << name << " id " << gatorID << endl;
            studentData->insert(name, std::stoi(gatorID));
        }
        else if (command == "remove") {

        }
        else if (command == "search") {

        }
        else if (command == "printInorder") {
            studentData->printInorder(studentData->root);
        }
        else if (command == "printPreorder") {
            studentData->printPreorder(studentData->root);
        }
        else if (command == "printPostorder") {
            studentData->printPostorder(studentData->root);
        }
        else if (command == "printLevelCount") {

        }
        else if (command == "removeInonrder") {

        }
        else if (command == "q") {
            run = 0;
        }
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////
//            TreeNode Class Print Tree Functions
////////////////////////////////////////////////////////////////////////////////////////////

void TreeNode::printFormat(Node* node) {
    cout << node->name << ", "; 
}

void TreeNode::printInorder(Node* root) {
    if (root == nullptr) return;
    printInorder(root->left);
    printFormat(root);
    printInorder(root->right);
}

void TreeNode::printPreorder(Node* root) {
    if (root == nullptr) return;
    printFormat(root);
    printPreorder(root->left);
    printPreorder(root->right);
}

void TreeNode::printPostorder(Node* root) {
    if (root == nullptr) return;
    printFormat(root);
    printPostorder(root->left);
    printPostorder(root->right);
}
