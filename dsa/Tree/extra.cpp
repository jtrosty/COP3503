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

char insertHelper(TreeNode** root, int value) {
    char balance = 0;
    char childBalance = 0;
    if (*root == nullptr) {
        *root = new TreeNode(value);
        return 0;
    }
    if (value <= (*root)->val) {
        childBalance += insertHelper(&(*root)->left, value);
        if (childBalance == 1 || childBalance == -1) balance++;
        if ((*root)->right == nullptr) balance++;
        else balance--;
    }
    else if (value > (*root)->val) {
        childBalance += insertHelper(&(*root)->right, value);
        if (childBalance == 1 || childBalance == -1) balance--;
        if ((*root)->left == nullptr) balance--;
        else balance++;
    }
    // Balance if needed
    if (childBalance == 2) {
        (*root)->left = rotateRight((*root)->left);
        return 0;
    }
    else if (childBalance == -2) {
        (*root)->right = rotateLeft((*root)->right);
        return 0;
    }
    else if (balance == 2 && childBalance == -1) {
        (*root)->left = rotateLeft((*root)->left);
    }
    else if (balance == -2 && childBalance == 1) {
        (*root)->right = rotateRight((*root)->right);
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