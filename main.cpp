#include <iostream>
using namespace std;

// Binary Search Tree Node
struct BSTNode {
    int value;
    BSTNode* left = NULL;
    BSTNode* right = NULL;
};

// Binary Search Tree
class BST {
private:
    // root pointer
    BSTNode* root ;
public:
    // default contstructor
    BST (){ root = NULL;}

    /* tree operator */
    BSTNode*findMin(BSTNode* node);
    BSTNode*findMax(BSTNode* node);
    BSTNode*insert(int value, BSTNode* node);
    BSTNode* remove(int value, BSTNode* node);

    void preOrderTraversal() const;
    void preOrderTraversal(BSTNode* node) const;
    void inOrderTraversal() const;
    void inOrderTraversal(BSTNode* node) const;
    void postOrderTraversal() const;
    void postOrderTraversal(BSTNode* node) const;
    void insert(int value);
    void remove(int value);
};

// function to insert value in node
BSTNode* BST::insert(int value, BSTNode* node)
    {   
        // if node is null, create one
        if(node == NULL)
        {
            node = new BSTNode;
            node->value = value;
            node->left = node->right = NULL;
        }
        // if value < currrent value, insert to left
        else if(value < node->value)
            node->left = insert(value, node->left);
        // if value < currrent value, insert to right
        else if(value > node->value)
            node->right = insert(value, node->right);
        return node;
    }


// function to find minimum node
BSTNode* BST::findMin(BSTNode* node) {
    // if node is null, return null
    if(node == NULL)
        return NULL;
    // if left child is null, node value is minimum
    else if(node->left == NULL)
        return node;
    // recursive
    else
        return findMin(node->left);
}


// function to find max node
BSTNode* BST::findMax(BSTNode* node) {
    if(node == NULL)
        return NULL;
    else if(node->right == NULL)
        return node;
    else
        return findMax(node->right);
}

// function to print pre-order traversal
void BST::preOrderTraversal() const {
    cout << "preOrderTraversal: ";
    preOrderTraversal(root);
    cout << endl;
}

// function to print pre-order node value
void BST::preOrderTraversal(BSTNode* node) const {  
    if (node != NULL) {
        cout << node->value << " ";
        preOrderTraversal(node->left);
        preOrderTraversal(node->right);
    }
}

// function to print in-order traversal
void BST::inOrderTraversal() const {
    cout << "inOrderTraversal: ";
    inOrderTraversal(root);
    cout << endl;
}

// function to print in-order node value
void BST::inOrderTraversal(BSTNode* node) const {
    if (node != NULL) {
        inOrderTraversal(node->left);
        cout << node->value << " ";
        inOrderTraversal(node->right);
    }
}

// function to print post-order traversal
void BST::postOrderTraversal() const {
    cout << "postOrderTraversal: ";
    postOrderTraversal(root);
    cout << endl;
}
// function to print post-order node value
void BST::postOrderTraversal(BSTNode* node) const {
    if (node != NULL) {
        postOrderTraversal(node->left);
        postOrderTraversal(node->right);
        cout << node->value << " ";
    }
}
// function to insert value to BST taking value input
void BST::insert(int value) {
    root = insert(value, root);
}

// function to remove value from BST
BSTNode* BST::remove(int value, BSTNode* node) {
    BSTNode* temp;
    // no children
    // if node is null return null
    if(node == NULL){
        delete temp;
        return NULL;
    }
        
    // if input value > node value then apply remove() to left child
    else if(value < node->value)
        node->left = remove(value, node->left);
    // if input value < node value then apply remove() to right child
    else if(value > node->value)
        node->right = remove(value, node->right);
    // two children case
    // replace with minimum node
    else if(node->left && node->right != NULL) {
        // find minimum of right branch and replace with it
        temp = findMin(node->right);
        node->value = temp->value;
        node->right = remove(node->value, node->right);
    }
    // one child
    else {
        temp = node;
        // relink child to parent
        if(node->left == NULL)
            node = node->right;
        else if(node->right == NULL)
            node = node->left;
        delete temp;
    }
    return node;
}

// function to remove value using value input
void BST::remove(int value) {
    root = remove(value, root);
}



const int SIZE =15;
int main() {
    BST bst;
    int values[SIZE] = {5, 2, 12, -4, 3, 9, 21, -7, 19, 25, -8, -6, -4, 3, 12};
    for (int i = 0; i < SIZE; i++)
        bst.insert(values[i]);

    bst.preOrderTraversal(); /// should be 5 2 -4 -7 -8 -6 3 12 9 21 19 25
    bst.inOrderTraversal(); /// should be -8 -7 -6 -4 2 3 5 9 12 19 21 25
    bst.postOrderTraversal(); /// should be -8 -6 7 -4 3 2 9 19 25 21 12 5

    bst.remove(3); /// Node 3 has 0 children --> delete the node and make it NULL;
    bst.remove(-4); /// Node -4 has 1 children --> Link parent to child --> delete the node and make it NULL;
    bst.remove(12); /// Node 12 has 2 children --> findMin for the right subtree --> swap value -> delete

    bst.preOrderTraversal(); /// should be 5 2 -7 -8 -6 19 9 21 25
    bst.inOrderTraversal(); /// should be -8 -7 -6 2 5 9 19 21 25
    bst.postOrderTraversal(); /// should be -8 -6 7 2 9 25 21 19 5

    return 0;
}