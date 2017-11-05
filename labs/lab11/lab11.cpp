/* Adam Mellan */
/* CSC 230     */
/* Lab 11      */

#include <iostream>
#include <stack>
#include <queue>

using namespace std;

// Tree Node has data, left pointer, right pointer
struct TreeNode
{
    int datum;
    struct TreeNode* left;
    struct TreeNode* right;
};

// create a new node with given value, left and right pointers are nullptr
struct TreeNode* newTreeNode(int value)
{
    struct TreeNode* node = new struct TreeNode;
    node->datum = value;
    node->left = nullptr;
    node->right = nullptr;
    return(node);
}

// Non-recursive traverse a binary tree
// print out the values by inorder
// it uses stack to store the nodes 
void noRecInorder(TreeNode *root)
{
    // Create empty stack
    stack<TreeNode *> treeStack;
    
    // Infinite loop
    while (true) {
        
        // Push left subtree
        while (root) {
            treeStack.push(root);
            root = root->left;
        }
        
        // All nodes have been printed, break out of loop
        if (treeStack.empty()) { break; }
        
        // Reassign root to the top of the stack
        root = treeStack.top();
        treeStack.pop();
        
        // Print node
        cout << root->datum << endl;
        
        root = root->right;
    }
}

// level order traversal 
// It uses queue to store the values of the next level
void levelOrder(TreeNode *root){
    // Create empty queue
    queue<TreeNode *> treeQueue;
    
    // Enqueue the root node
    if (root) { treeQueue.push(root); }
    
    while (!treeQueue.empty()) {
        // Create temp and assign it the front of the queue
        TreeNode *temp = treeQueue.front();
        
        // Print the front of the queue
        cout << temp->datum << endl;
        
        // Remove front from queue
        treeQueue.pop();
        
        if (temp->left) { treeQueue.push(temp->left); } // Enqueue left child
        if (temp->right) { treeQueue.push(temp->right); } // Enqueue right child
    }
}


// Driver program to test above functions
int main()
{
    /* Constructed binary tree is
        100
      /     \
      9      10
     /  \    /
     9   4  7
     */
    struct TreeNode *root = newTreeNode(100);
    root->left        = newTreeNode(9);
    root->right       = newTreeNode(10);
    root->left->left  = newTreeNode(9);
    root->left->right = newTreeNode(4);
    root->right->left = newTreeNode(7);
    
    cout << "Inorder traversal result:" << endl;;
    noRecInorder(root);
    cout << "Level traversal result:" << endl;
    
    levelOrder(root);
    
    return 0;
}
