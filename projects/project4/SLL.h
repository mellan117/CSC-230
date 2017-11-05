/* Adam Mellan */
/* Dr. Li      */
/* CSC 230     */
/* Project 4   */

#include <iostream>
#include "Node.h"
using  namespace  std;

template <class U>
class SLL {
    
    Node<U> * headPtr;
    int size;
    
public:
    // default constructor
    SLL(){
        //implement this method
        
        // Set default values
        headPtr = nullptr;
        size = 0;
    }
    
    // destructor
    ~SLL(){
        // implement this method
        
        // Iterate through list
        Node<U> *currNode = headPtr;
        while (currNode->next != nullptr) {
            Node<U> *nodeToRelease = currNode; // Set nodeToRelease to current node
            currNode = currNode->next; // Set current node to next node
            
            delete nodeToRelease; // Release the current node from memory
        }
        headPtr = nullptr;
    }
    
    Node<U>* getHeadPtr(){
        return headPtr;
    }
    
    // insert (item1, item2) to the list
    void insert(U item1, U item2){
        //implement this method
        
        // Init new node with data
        Node<U> *newNode = new Node<U>;
        newNode->SSN = item1;
        newNode->name = item2;
        newNode->next = nullptr;
        
        if (headPtr == nullptr) {
            // List is empty
            // New node becomes head
            headPtr = newNode;
            size++;
            return;
        } else {
            // Iterate through list
            Node<U> *currNode = headPtr;
            while (currNode->next != nullptr) {
                currNode = currNode->next;
            }
            
            // Append new node to end of list
            currNode->next = newNode;
            size++;
        }
    }
    
    // if find the item1 value, return the pointer to the node
    // otherwise, return nullptr
    Node<U>* search(U item1){
        //implement this method
        
        // Iterate through list
        Node<U> *currNode = headPtr;
        while (currNode != nullptr) {
            
            // Found node
            if (currNode->SSN == item1) {
                return currNode;
            }
            currNode = currNode->next;
        }
        
        return nullptr; // Node NOT found
    }
    
    // remove the node with key value: item1
    bool remove(U item1){
        //implement this method
        
        if (headPtr != nullptr) {
            // List is NOT empty
            //
            if (headPtr->SSN == item1) {
                // Remove head
                Node<U> *headTemp = headPtr;
                headPtr = headPtr->next;
                
                delete headTemp;
                size--;
                
                return true;
            } else {
                Node<U> *currNode = headPtr;
                Node<U> *nextNode = currNode->next;
                Node<U> *nodeToRemove = headPtr;
                
                // Iterate through list
                while (nextNode != nullptr) {
                    
                    // Found node to remove
                    if (nextNode->SSN == item1) {
                        nodeToRemove = nextNode;
                        currNode->next = nextNode->next;
                        
                        // Release node
                        delete nodeToRemove;
                        size--;
                        
                        return true;
                    }
                    // Continue iteration with nextNode always 1 node in front of currNode
                    currNode = currNode->next;
                    nextNode = nextNode->next;
                }
            }
        }
        
        return false;
    }
    
    int getSize(){
        
        return size;
    }
    
    // display the SSN values of each node in the linked list
    void display(){
        Node<U>* temp;
        temp = headPtr;
        while (temp!= nullptr) {
            cout << temp->SSN << endl;
            temp = temp->next;
        }
    }
};


