#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

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

struct NodeRemoveAndParent {
    Node* parent;
    Node* nodeToRemove;
    char direction;
};

Node::Node(std::string _name, int _gatorID) {
    gatorID = _gatorID;
    name = _name;
    left = nullptr;
    right = nullptr;
    height = 1;
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

        // Helper functions
        char insertHelper(Node** root, std::string name, int gatorID);
        NodeRemoveAndParent* searchRemove(int _gatorID);

        void setHeight(Node* node);

        // Test funcitons
        int checkBalance(Node* node);
        char testTreeBalance(Node*node);
        char testTreeBalance(Node* node); 

        char checkPerfect(); 
        void checkPerfect(Node* root, vector<int>& counterVect, int height); 

    public:
        Node* root = nullptr;

        // constructor
        TreeNode();
        TreeNode(std::string _name, int _gatorID);

        // Operations
        char insert(std::string _name, int _gatorID);
        char remove(int gatorID);
        Node* search(int gatorID);
        Node* search(std::string name);
        void search(std::string& name, Node* node, Node& result);

        // Funciton to Print out tree
        void printFormat(Node* node);
        void printInorder(Node* root);
        void printPreorder(Node* root);
        void printPostorder(Node* root);
        void printLevelCount();
// Tests
        char testTreeBalance();
};
///////////////////////////////////////////////////////////////////////////////
//                     Constructors
///////////////////////////////////////////////////////////////////////////////
TreeNode::TreeNode() { }

TreeNode::TreeNode(std::string _name, int _gatorID) {
    Node* newRoot = new Node(_name, _gatorID);
    root = newRoot;
}

///////////////////////////////////////////////////////////////////////////////
//                     Remove Functions
///////////////////////////////////////////////////////////////////////////////
char TreeNode::remove(int gatorID) {
    NodeRemoveAndParent* nodes = searchRemove(gatorID);
    // Case of if the node was not found

    // The case of the node being delete has no children.
    if (nodes->nodeToRemove->left == nullptr && nodes->nodeToRemove->right == nullptr) {
        delete nodes->nodeToRemove;
        if (nodes->parent != nullptr) {
            if (nodes->direction = 0) nodes->parent->left = nullptr;
            else nodes->parent->right = nullptr;
        } 
    }
    // Case of the node having 2 children
    if(nodes->nodeToRemove->left != nullptr && nodes->nodeToRemove->right != nullptr) {
        // Find next immediate successor in sorted order (not successor in the tree)
        Node* successor = nodes->nodeToRemove->right;
        Node* successorParent = nodes->nodeToRemove;
        while (successor->left != nullptr) {
            successorParent = successor;
            successor = successor->left;
        }
        if (successor->right != nullptr) successorParent->left = successor->right;
        if (nodes->parent != nullptr) {
            if (nodes->direction = 0) nodes->parent->left = successor;
            else nodes->parent->right = successor;
        } 
        successor->left = nodes->nodeToRemove->left;
        successor->right = nodes->nodeToRemove->right;
        delete nodes->nodeToRemove;
    }
    // Case of only left child on node to be deleted
    if (nodes->nodeToRemove->left != nullptr) {
        if (nodes->parent != nullptr) {
            if (nodes->direction = 0) nodes->parent->left = nodes->nodeToRemove->left;
            else nodes->parent->right = nodes->nodeToRemove->left;
        } 
        else root = nodes->nodeToRemove->left;
        delete nodes->nodeToRemove;
    }
    // Case of only right child on node to be deleted
    if (nodes->nodeToRemove->right != nullptr) {
        if (nodes->parent != nullptr) {
            if (nodes->direction = 0) nodes->parent->left = nodes->nodeToRemove->right;
            else nodes->parent->right = nodes->nodeToRemove->right;
        } 
        else root = nodes->nodeToRemove->left;
        delete nodes->nodeToRemove;
    }
    // Case of the node having 2 children


}

///////////////////////////////////////////////////////////////////////////////
//                     Insert Functions
///////////////////////////////////////////////////////////////////////////////
char TreeNode::insert(std::string _name, int _gatorID) {
    return insertHelper(&root, _name, _gatorID);
}
char TreeNode::insertHelper(Node** _root, std::string _name, int _gatorID) {
    // All GatorIDs must be unique, the if handles the case if we find the same gatorID
    int balance = 0;
    int childBalance = 0;
    char success = 0;
    if (*_root == nullptr) {
        Node* newNode = new Node(_name, _gatorID);
        (*_root) = newNode;
        return 1;
    }
    else if ((*_root)->gatorID == _gatorID) {
        return 0;
    }
    else if (_gatorID < (*_root)->gatorID) {
        success = insertHelper(&(*_root)->left, _name, _gatorID);
        if ((*_root)->left->height + 1 > (*_root)->height) (*_root)->height = (*_root)->left->height + 1;
        childBalance = checkBalance((*_root)->left);
    }
    else if (_gatorID > (*_root)->gatorID){
        success = insertHelper(&(*_root)->right, _name, _gatorID);
        if ((*_root)->right->height + 1 > (*_root)->height) (*_root)->height = (*_root)->right->height + 1;
        childBalance = checkBalance((*_root)->right);
    }

    // Only want to balance if a node was succesfully inserted
    if (success) {
        balance = checkBalance(*_root);

        if (balance > 1 && childBalance == -1) {
            *_root = rotateLeftRight(*_root);
        }
        else if (balance < -1 && childBalance == 1) {
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
        return success;
    }
    return success;
}
///////////////////////////////////////////////////////////////////////////////
//                     Search Functions
///////////////////////////////////////////////////////////////////////////////

Node* TreeNode::search(int _gatorID) {
    Node* nodeTosearch = root;
    do {
        if (nodeTosearch->gatorID == _gatorID) return nodeTosearch;
        if (_gatorID < nodeTosearch->gatorID) nodeTosearch = nodeTosearch->left;
        else nodeTosearch = nodeTosearch->right;
    } 
    while (nodeTosearch != nullptr);
    return nodeTosearch;
}

// To support deletion of notes, it is useful to have the parent.
// NodeRemoveAndParaent is a struct that has both
NodeRemoveAndParent* TreeNode::searchRemove(int _gatorID) {
    NodeRemoveAndParent* result;
    result->parent = nullptr;
    result->nodeToRemove = root;
    do {
        if (result->nodeToRemove->gatorID == _gatorID) return result;
        if (_gatorID < result->nodeToRemove->gatorID) {
            result->parent = result->nodeToRemove;
            result->nodeToRemove = result->nodeToRemove->left;
            result->direction = 0;
        }
        else {
            result->parent = result->nodeToRemove;
            result->nodeToRemove = result->nodeToRemove->right;
            result->direction = 1;
        }
    } 
    while (result->nodeToRemove != nullptr);
    return result;
}

Node* TreeNode::search(std::string _name) {
    Node* result = nullptr;
    search(_name, root, *result);
    if (result->name == _name) return result;
    else return nullptr;
}

void TreeNode::search(std::string& _name, Node* node, Node& result) {
    if (node == nullptr) return;
    if (node->name == _name) cout << node->gatorID << endl;
    search(_name, node->left, result);
    search(_name, node->right, result);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      Main Function
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//#ifdef DISABLE_TESTS

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
            if (studentData->insert(name, std::stoi(gatorID))) cout << "successful" << endl;
            else                                               cout << "unsuccessful" << endl;
        }
        else if (command == "remove") {

        }
        else if (command == "search") {
            if (name.empty()) {
                Node* result = studentData->search(gatorID);
                if (result != nullptr) cout << "successful" << endl;
                else cout << "unsuccessful" << endl;
            }
            else {
                studentData->search(name);
            }
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
            studentData->printLevelCount();
        }
        else if (command == "removeInonrder") {

        }
        else if (command == "test") {
            if (studentData->testTreeBalance()) cout << "Tree is balanced" << endl;
        }
        else if (command == "q") {
            run = 0;
        }
    }
    return 0;
}
//#endif

///////////////////////////////////////////////////////////////////////////////
//                     Check and Test Functions
///////////////////////////////////////////////////////////////////////////////

int TreeNode::checkBalance(Node* node) {
    if (node == nullptr) return 0;
    int left = 0;
    int right = 0;
    left = (node->left != nullptr) ? node->left->height : 0;
    right = (node->right != nullptr) ? node->right->height : 0;
    return left - right;
}

char TreeNode::testTreeBalance() {
    int balance = checkBalance(root);
    char isNodeBalanced = 0;
    isNodeBalanced = balance < 2 && balance > -2;
    return isNodeBalanced && testTreeBalance(root);
}

char TreeNode::testTreeBalance(Node* node) {
    if (node == nullptr) return 1;
    char isNodeBalanced = 0;
    char areChildrenBalanced = 0;
    int left = 0;
    int right = 0;
    left = checkBalance(node->left);
    right = checkBalance(node->right);
    isNodeBalanced = left < 2 && left > -2 && right < 2 && right > -2;
    areChildrenBalanced = testTreeBalance(node->left) && testTreeBalance(node->right);
    return isNodeBalanced && areChildrenBalanced;
}
void TreeNode::checkPerfect(Node* root, vector<int>& counterVect, int height) {
    if (root->left == nullptr && root->right == nullptr) return;
    if (counterVect.size() == height) {
        counterVect.push_back(0);
    }
    if (root->left != nullptr) counterVect.at(height)++;
    if (root->right != nullptr) counterVect.at(height)++;
    height++;
    if (root->left != nullptr) checkPerfect(root->left, counterVect, height);
    if (root->right != nullptr) checkPerfect(root->right, counterVect, height);
}

char TreeNode::checkPerfect() 
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
    // Perform Node rotation
    Node* grandChildNode = node->right->left;
    Node* newRoot = node->right;
    newRoot->left = node;
    node->right = grandChildNode;

    // Adjust Heights 
    setHeight(node->left);
    setHeight(node);

    return newRoot;
}

Node* TreeNode::rotateRight(Node *node) {
    // Perform Node rotation
    Node* grandChildNode = node->left->right;
    Node* newRoot = node->left;
    newRoot->right = node;
    node->left = grandChildNode;
    // Adjust heights
    setHeight(node->right);
    setHeight(node);
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

void TreeNode::setHeight(Node* node) {
    if (node == nullptr) return;
    int left = 0;
    int right = 0;
    if (node->left != nullptr) {
        left = node->left->height;
    }
    if (node->right != nullptr) {
        right = node->right->height;
    }
    if (left + 1 > right) node->height = left + 1;
    else node->height = right;
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

void TreeNode::printLevelCount() {
    cout << root->height << endl;
}
