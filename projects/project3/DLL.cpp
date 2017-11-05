#include "DLL.h"
#include <iostream>
#include <string>
using namespace std;

// default constructor is already implemented
// do not modify the default constructor
DLL::DLL(){
    headPtr = nullptr;
    itemCount=0;
}

// return the head pointer of the list
// it is already implemented, do not modify it
Node* DLL::getHeadPtr(){
    return headPtr;
}

// copy construct, which copies an existing list n
// the new list is a different object from n
// the new list and object n have the same contents
// Please implement it
DLL::DLL(DLL& n){
    headPtr = nullptr;
    
    // Iterate through the old list
    Node *oldNode = n.headPtr;
    while (oldNode != nullptr) {
        
        // Create a new node with the old node's values
        Node *newNode = new Node();
        newNode->ssn = oldNode->ssn;
        newNode->name = oldNode->name;
        newNode->succ = nullptr;
        newNode->pred = nullptr;
        
        if (headPtr == nullptr) { // Check if new list is empty
            headPtr = newNode;
            itemCount++;
        } else {
            // Iterate through the new list and append the next node to the end of the list
            Node *currNode = headPtr;
            while (currNode->succ != nullptr) {
                currNode = currNode->succ;
            }
            // Append new node to end of list
            currNode->succ = newNode;
            newNode->pred = currNode;
            itemCount++;
        }
        
        oldNode = oldNode->succ;
    }
}

// destructor
// release every node of the list
// Please implement it
DLL::~DLL(){
    // Iterate through list
    Node *currNode = headPtr;
    while (currNode->succ != nullptr) {
        Node *nodeToRelease = currNode; // Set nodeToRelease to current node
        currNode = currNode->succ; // Set current node to next node
        
        delete nodeToRelease; // Release the current node from memory
    }
    headPtr = nullptr;
}

// if some node has SSN matcthes string ss
// return the index value of the node
// the index value of the first node is 0, the second node is 1, etc.
// if there is no node matching ss, return -1
int DLL::search(string ss)const{
    int index = 0;
    
    // Iterate through list
    Node *currNode = headPtr;
    while (currNode->succ != nullptr) {
        
        // Found node
        if (currNode->ssn == ss) {
            return index;
        }
        
        currNode = currNode->succ;
        index++;
    }
    
    return -1;
}


// insert (ss, name) to the existing list
// the SSN values are each node are organized in INCREASING order
// if there is a node matching ss value, return false; otherwise true
// else create a node with (ss, name), insert the node to the proper position
// parameter count is the counter of number of valid insertion
// when you implement this method, consider the following situations:
// 1. list is empty
// 2. node should be inserted to the beginning of the list
// 3. node should be inserted to the middle of the list
// 4. node should be inserted to the end of the list
bool DLL::insert(string ss, string name, int & count){
    // Init new node with user data
    Node *newNode = new Node();
    newNode->ssn = ss;
    newNode->name = name;
    newNode->succ = nullptr;
    newNode->pred = nullptr;
    
    if (headPtr == nullptr) { // If list is empty then new node becomes head
        headPtr = newNode;
        count++;
        
        return true;
    } else {
        // Iterate through list
        Node *currNode = headPtr;
        while (currNode != nullptr) {
            if (currNode->ssn == ss) {
                return false;
            } else if (currNode->ssn < ss && currNode->succ != nullptr) { // Node should be inserted later in list
                currNode = currNode->succ;
            } else {
                // Node should be inserted at this index
                //
                if (currNode->succ == nullptr && currNode->ssn < ss) { // Insert at end of list
                    currNode->succ = newNode;
                    newNode->pred = currNode;
                    count++;
                    
                    return true;
                } else if (currNode->pred == nullptr && currNode->ssn > ss) { // Insert at beginning of list
                    newNode->succ = currNode;
                    currNode->pred = newNode;
                    headPtr = newNode;
                    count++;
                    
                    return true;
                } else { // Insert in middle of list
                    newNode->succ = currNode;
                    newNode->pred = currNode->pred;
                    currNode->pred->succ = newNode;
                    currNode->pred = newNode;
                    count++;
                    
                    return true;
                }
            }
        }
    }
    
    return false;
}


// remove node containing ss value
// if there is no node containing ss, return false; otherwise true
// consider the following situations:
// 1. list is empty
// 2. node containing ss value is the first node
// 3. node containing ss value is in the middle of the list
// 4. node containing ss value is the last node of the list
bool DLL::remove(string ss, int & count){
    
    // Iterate through list
    Node *currNode = headPtr;
    while (currNode != nullptr) {
        
        // Found node
        if (currNode->ssn == ss) {
            
            if (currNode->pred == nullptr) { // If node is head then remove from beginning
                headPtr = currNode->succ;
            } else if (currNode->succ == nullptr) { // If node is tail then remove from end
                currNode->pred->succ = nullptr;
            } else {                                // Else remove from middle
                currNode->pred->succ = currNode->succ;
                currNode->succ->pred = currNode->pred;
            }
            
            // Release node
            delete currNode;
            count++;
            
            return true;
        }
        currNode = currNode->succ;
    }
    
    // If there is no node containing ss
    // or the list is empty
    return false;
}

// return the number of the nodes
// it is already implemented, do not modify it
int DLL::size(){
    
    return itemCount;
}

// iterate through each node
// print out SSN and memory address of each node
// do not modify this method
void DLL::display(){
    Node* temp;
    temp = headPtr;
    while (temp!= nullptr) {
        cout << temp->ssn << "\t" << temp << endl;
        temp = temp->succ;
    }
}
