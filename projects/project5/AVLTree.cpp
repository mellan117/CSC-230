/* Adam Mellan */
/* CSC 230     */
/* Project 5   */

#include <iostream>
#include <string>
#include "AVLTree.h"
#include <iomanip>
#include <queue>
using namespace std;

AVLTree::AVLTree(){
    root = nullptr;
}

AVLTree::~AVLTree(){
    AVLNode *nextNode = nullptr;
    AVLNode *current = root;
    while (current) {
        if (!current->left) {       // Delete current node
            nextNode = current->right;
            delete current;
        } else {                    // Rotate left node into a right node
            nextNode = current->left;
            current->left = nextNode->right;
            nextNode->right = current;
        }
        current = nextNode;
    }
}

AVLNode* AVLTree::getRoot(){
    return root;
}


// search value ss in the AVL tree
bool AVLTree::find(string ss){
    if (root == nullptr) {
        return false;
    }
    
    AVLNode* node = root;
    
    while (node != nullptr) {
        if (ss.compare(node->ssn) == 0) {
            return true;
        }
        if (ss.compare(node->ssn) < 0) {
            node = node->left;
        }
        else{
            node = node->right;
        }
    }
    return false;
}

// return the height of the subtree rooted at node
// if subtree is empty, height is -1
// if subtree has one node, height is 0
int AVLTree::height(AVLNode* node){
    
    if(node != nullptr){
        return node->height;
    }
    else{
        return -1;
    }
}

// return the balance factor of the node
int AVLTree::balanceFactor(AVLNode* node){
    return height(node->left) - height(node->right);
}

// update the height of the node
// this should be done whenever the tree is modified
void AVLTree::updateHeight(AVLNode* node){
    int hl = height(node->left);
    int hr = height(node->right);
    node->height = (hl>hr ? hl : hr) + 1;
}


// rotate right the subtree rooted at node
// return the new root of the subtree
AVLNode* AVLTree::rotateRight(AVLNode* node){
    AVLNode* lp = node->left;      // left child of node
    if (node->parent!=nullptr) {  // node is not root
        if (node->parent->left == node) { // node is a left child
            node->parent->left = lp;
        }else{
            node->parent->right = lp;     // node is a right child
        }
    }
    
    if (lp->right != nullptr) {           // pointer update
        lp->right->parent = node;
    }
    
    lp->parent = node->parent;
    node->left = lp->right;
    lp->right = node;
    node->parent = lp;
    updateHeight(node);                   // after rotation, update height
    updateHeight(lp);                     // after rotation, update height
    if (node == root) {
        root = lp;
    }
    return lp; // lp is the new root of the subtree
}


// rotate left the subtree rooted at node
// return the new root of the subtree
AVLNode* AVLTree::rotateLeft(AVLNode* node){
    AVLNode* rp = node->right;
    if (node->parent!=nullptr) {
        if (node->parent->left == node) {
            node->parent->left = rp;
        }else{
            node->parent->right = rp;
        }
    }
    
    if (rp->left != nullptr) {
        rp->left->parent = node;
    }
    
    rp->parent = node->parent;
    
    node->right = rp->left;
    rp->left = node;
    node->parent = rp;
    node->parent = rp;
    updateHeight(node);
    updateHeight(rp);
    if (node == root) {
        root = rp;
    }
    return rp;
}


// rebalance a tree rooted at node
// return the new root of the subtree
AVLNode* AVLTree::balance(AVLNode* node){
    updateHeight(node);
    if (balanceFactor(node) == 2) {
        if (balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left); // for left right case
        }
        
        AVLNode* temp = rotateRight(node);
        updateHeight(temp);
        return temp;
    }
    
    if (balanceFactor(node) == -2) {
        if (balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);  // for right left case
        }
        AVLNode* temp2 = rotateLeft(node);
        updateHeight(temp2);
        return temp2;
    }
    return node;
}

// insert a new node with (ss, na) to the AVL tree
// if there exists ss value, return false
// otherwise, insert it, balance the tree, return true
bool AVLTree::insert(string ss, string na){
    // please implement here
    
    if (!root) {
        // Tree is empty
        // New data becomes root
        root = new AVLNode(ss, na);
        
        return true;
    } else {
        AVLNode *newNode = new AVLNode(ss, na);
        
        // Iterate through the tree
        AVLNode *current = root;
        AVLNode *parent = nullptr;
        while (current) {
            if (ss == current->ssn) {       // Node already in tree
                return false;
            } else if (ss < current->ssn) { // Left branch
                parent = current;
                current = current->left;
            } else {                        // Right branch
                parent = current;
                current = current->right;
            }
        }
        
        // Insert new node
        if (ss < parent->ssn) { // Left branch
            parent->left = newNode;
            newNode->parent = parent;
        } else {                // Right branch
            parent->right = newNode;
            newNode->parent = parent;
        }
        
        // Balance the tree
        while (parent) {
            parent = balance(parent);
            parent = parent->parent;
        }
        
        return true;
    }
    
    return true;
}

AVLNode* AVLTree::maxOfSubtree(AVLNode* node){
    if (node == nullptr) {
        return nullptr;
    }
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
}

bool AVLTree::deleteNode(string ss){
    // please implement here
    
    if (!root) {
        // Tree is empty
        return false;
    } else {
        bool nodeFound = false;
        AVLNode *current = root;
        AVLNode *parent = nullptr;
        AVLNode *nodeToRemove = nullptr;
        AVLNode *nodeToRemoveParent = nullptr;
        
        // Iterate through the tree
        while (current) {
            
            if (ss == current->ssn) { // Found node to remove
                nodeFound = true;
                
                if (!current->left && !current->right) { // NO children

                    // Update parent
                    if (parent->left == current) {
                        parent->left = nullptr;
                    } else {
                        parent->right = nullptr;
                    }
                    
                    // Set nodeToRemove
                    nodeToRemove = current;
                    nodeToRemoveParent = parent;
                    break;
                } else if (current->left && !current->right) { // Only LEFT child
                    
                    // Node to remove is root
                    // Reassign root and set nodeToRemove
                    if (current == root) {
                        nodeToRemove = root;
                        root = root->left;
                        root->parent = nullptr;
                        break;
                    } else {
                        // Update parent->left with the removed node's -> left node
                        AVLNode *temp = current->left;
                        if (parent->left == current) {
                            parent->left = temp;
                            temp->parent = parent;
                        } else {
                            parent->right = temp;
                            temp->parent = parent;
                        }

                        // Set nodeToRemove
                        nodeToRemove = current;
                        nodeToRemoveParent = parent;
                        break;
                    }
                    
                    
                } else if (!current->left && current->right) { // Only right child
                    
                    // Node to remove is root
                    // Reassign root and set nodeToRemove
                    if (current == root) {
                        nodeToRemove = root;
                        root = root->right;
                        root->parent = nullptr;
                        break;
                    } else {
                        // Update parent->right with the removed node's -> right node
                        AVLNode *temp = current->right;
                        if (parent->left == current) {
                            parent->left = temp;
                            temp->parent = parent;
                        } else {
                            parent->right = temp;
                            temp->parent = parent;
                        }

                        // Set nodeToRemove
                        nodeToRemove = current;
                        nodeToRemoveParent = parent;
                        break;
                    }
                    
                    
                } else if (current->left && current->right) { // TWO children
                    // Find max node in current's left subtree
                    AVLNode *maxNode = maxOfSubtree(current->left);
                    AVLNode *maxNodeParent = nullptr;
                    
                    // Iterate through the tree to find the maxNode's parent
                    AVLNode *curr = root;
                    while (curr) {
                        if (maxNode->ssn == curr->ssn) {
                            break;
                        } else if (maxNode->ssn < curr->ssn) {
                            maxNodeParent = curr;
                            curr = curr->left;
                        } else {
                            maxNodeParent = curr;
                            curr = curr->right;
                        }
                    }
                    
                    // Reassign the node's VALUE
                    current->ssn = maxNode->ssn;
                    current->name = maxNode->name;
                    
                    // Update maxNodeParent
                    if (!maxNode->left && !maxNode->right) { // Max node has NO children

                        if (maxNodeParent->left == maxNode) {
                            maxNodeParent->left = nullptr;
                        } else {
                            maxNodeParent->right = nullptr;
                        }
                    } else if (maxNode->left && !maxNode->right) { // Max node has LEFT child

                        // Update maxNodeParent->left with the maxNode's -> left node
                        AVLNode *temp = maxNode->left;
                        if (maxNodeParent->left == maxNode) {
                            maxNodeParent->left = temp;
                            temp->parent = maxNodeParent;
                        } else {
                            maxNodeParent->right = temp;
                            temp->parent = maxNodeParent;
                        }
                    }
                    
                    // Set nodeToRemove
                    nodeToRemove = maxNode;
                    nodeToRemoveParent = maxNodeParent;
                    break;
                }
            } else if (ss < current->ssn) { // Left branch
                parent = current;
                current = current->left;
            } else {                        // Right branch
                parent = current;
                current = current->right;
            }
        }
        
        if (nodeFound) {
            // Release the node
            delete nodeToRemove;
            
            // Balance the tree
            while (nodeToRemoveParent) {
                nodeToRemoveParent = balance(nodeToRemoveParent);
                nodeToRemoveParent = nodeToRemoveParent->parent;
            }
            
            // Successfully removed the node containing "ss" from the tree
            return true;
        }
    }
    
    return false;
}

// internal function
// do not call it directly
void AVLTree::print(AVLNode* x, int indent){
    if(x == nullptr) return;
    if (x->right != nullptr) {
        print(x->right, indent+4);
    }
    
    if (indent != 0) {
        cout << std::setw(indent) << ' ';
    }
    
    if(x->right != nullptr){
        cout << " /\n" << std::setw(indent) << ' ';
    }
    
    cout << x->ssn << endl;
    
    if (x->left != nullptr) {
        cout << std::setw(indent) << ' ' <<" \\\n";
        print(x->left, indent+4);
    }
    
}

// print out the structure of the binary tree
// use it for debugging, I love this function
void AVLTree::print(){
    int count = 0;
    print(root, count);
}


// it does not level order traversal
// it prints out the number of node
// use it mainly for debugging
void AVLTree::levelOrder(){
    
    // please implement it
    
    int totalNodes = 0;
    
    if (root) { // Tree is NOT empty

        // Iterate through the tree
        AVLNode *current = root;
        AVLNode *parent = nullptr;
        while (current) {
            if (!current->left) {
                // Increment node counter
                totalNodes++;
                current = current->right;
            } else {

                // Find the parent
                parent = current->left;
                while (parent->right) {
                    if (parent->right == current) {
                        break;
                    } else {
                        parent = parent->right;
                    }
                }

                if (!parent->right) { // Make current as right child of its parent
                    parent->right = current;
                    current = current->left;
                } else {              // Revert the right child of the parent
                    parent->right = nullptr;
                    // Increment node counter
                    totalNodes++;
                    current = current->right;
                }
            }
        }
    }
    
    cout << "tree size . . . " << totalNodes << endl;
}


