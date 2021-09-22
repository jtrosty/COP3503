#include <iostream>
#include <string>

using std::cout;
using std::endl;

class Node {
    public:
        int gatorID;
        std::string name;
        Node* left;
        Node* right;
        int height;

        Node(int _gatorID, std::string _name);
        Node(int _gatorID, std::string _name, int height);
};

Node::Node(int _gatorID, std::string _name) {
    gatorID = _gatorID;
    name = _name;
    left = nullptr;
    right = nullptr;
    height = 0;
}

Node::Node(int _gatorID, std::string _name, int _height) {
    gatorID = _gatorID;
    name = _name;
    left = nullptr;
    right = nullptr;
    height = _height;
}

class TreeNode {
    private:

        // Balance funcitons
        void rotateLeft(Node* root);
        void rotateRight(Node* root);
        void rotateLeftRight(Node* root);
        void rotateLeftRight(Node* root);

    public:
        Node* root = nullptr;

        // constructor
        TreeNode(std::string _gatorID, std::string _name);

        // Operations
        void insert(std::string name, std::string gatorID);
        void remove(std::string gatorID);

        // Funciton to Print out tree
        void printFormat(Node* node);
        void printInorder(Node* root);
        void printPreorder(Node* root);
        void printPostorder(Node* root);
        void printLevelCount();
};

void TreeNode(std::string _gatorID, std::string _name) {

}

int main(int argc, char* argv[]) {
    //We have received command line input
    char run = 1;
    size_t delimiter1 = -1;
    size_t delimiter2 = -1;
    std::string userInput;
    std::string command;
    std::string name;
    std::string gatorID;

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
        }
        else if (command == "remove") {

        }
        else if (command == "search") {

        }
        else if (command == "printInorder") {

        }
        else if (command == "printPreorder") {

        }
        else if (command == "printLevelCount") {

        }
        else if (command == "removeInorder") {

        }
        else if (command == "q") {
            run = 0;
        }
    }
    return 0;
}

//////////////////////////////////////////////////////////////////
//              Print Tree Functions
//////////////////////////////////////////////////////////////////

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
