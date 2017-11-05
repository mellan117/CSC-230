/* Adam Mellan */
/* CSC 230     */
/* Lab 10      */

#include "treeNode.h"
#include <iomanip>

template <class V>
class tree {
    TreeNode<V> * root;
    int size;
    
public:
    // default constructor
    // by default, the tree is empty
    tree(){
        root = nullptr;
        size = 0;
    }
    
    // search value x in tree rooted at node t
    bool treeSearch(V x, TreeNode<V>* t){
        
        if(t == nullptr) return false;
        if(t->getDatum() == x) return true;
        return treeSearch(x, t->getLeft()) || treeSearch(x, t->getRight());
    }
    
    bool treeSearch(V x){
        treeSearch(x, root);
    }
    
    
    // binary search value x in tree rooted at node t
    bool treeBSearch(V x, TreeNode<V>* t){
        // implement this method
        
        if(t == nullptr) {
            // Tree is empty
            return false;
        } else if(t->getDatum() == x) {
            // Leaf found
            return true;
        }
        
        // Continue to check   left branch        and         right branch
        return treeBSearch(x, t->getLeft()) || treeBSearch(x, t->getRight());
    }
    
    bool treeBSearch(V x){
        return treeBSearch(x, root);
    }
    
    // check node t is leaf
    bool isLeaf(TreeNode<V>* t){
        //implement this method
        
        if (t != nullptr) return true;
        
        return false;
    }
    
    // find the height of the tree rooted at node t
    int height(TreeNode<V>* t){
        //implement this method
        
        if (t == nullptr) {
            // Tree is empty
            return 0;
        } else {
            // Recursively find the left and right height
            int leftHeight = height(t->getLeft());
            int rightHeight = height(t->getRight());
            
            return 1 + max(leftHeight, rightHeight);
        }
        
        return 0;
    }
    
    int height(){
        return height(root);
    }
    
    // find the number of nodes of tree rooted at t
    int nNodes(TreeNode<V>* t){
        //implement this method
        
        if (t == nullptr) {
            // Tree is empty
            return 0;
        } else if (t->getLeft() == nullptr && t->getRight() == nullptr) {
            // Only 1 node (root)
            return 1;
        } else {
            // Recursively add the size of the left and right branches and 1 for the current node
            return 1 + nNodes(t->getLeft()) + nNodes(t->getRight());
        }
        
        return 0;
    }
    
    int nNodes(){
        return nNodes(root);
    }
    
    
    // insert value x to the current tree object
    void insert(V x){
        // implement this method
        
        if (root == nullptr) {
            // Tree is empty
            // New data becomes root
            root = new TreeNode<V>(x);
        } else {
            TreeNode<V> *newLeaf = new TreeNode<V>(x);
            TreeNode<V> *parentLeaf = new TreeNode<V>(0);
            
            // Iterate through the tree
            TreeNode<V> *currLeaf = root;
            while (currLeaf != nullptr) {
                if (x < currLeaf->getDatum()) {
                    // Left branch
                    parentLeaf = currLeaf;
                    currLeaf = currLeaf->getLeft();
                } else {
                    // Right branch
                    parentLeaf = currLeaf;
                    currLeaf = currLeaf->getRight();
                }
            }
            
            if (newLeaf->getDatum() < parentLeaf->getDatum()) {
                // Insert leaf on the left
                parentLeaf->setLeft(newLeaf);
            } else {
                // Insert leaf on the right
                parentLeaf->setRight(newLeaf);
            }
        }
    }
    
    
    // print out the values of tree rooted at x
    // it shows the hierarchy of the tree
    // it will be useful for debugging
    void print(TreeNode<V> * x, int indent){
        if(x == nullptr) return;
        if (x->getRight() != nullptr) {
            print(x->getRight(), indent+4);
        }
        
        if (indent != 0) {
            cout << std::setw(indent) << ' ';
        }
        
        if(x->getRight() != nullptr){
            cout << " /\n" << std::setw(indent) << ' ';
        }
        
        cout << x->getDatum() << endl;
        
        if (x->getLeft() != nullptr) {
            cout << std::setw(indent) << ' ' <<" \\\n";
            print(x->getLeft(), indent+4);
        }
        
    }
    
    void print(){
        int count = 0;
        print(root, count);
    }
    
};
