/* Adam Mellan */
/* Dr. Li      */
/* CSC 230     */
/* Project 4   */

#include <iostream>
#include "SLL.h"
using  namespace  std;

template <class V>
class HashTable {
    int tableSize; // table size
    
    SLL<V>* table;
    
public:
    // default constructor, which uses default table size 3
    HashTable(){
        tableSize = 3;
        table = new SLL<V>[tableSize];
    }
    
    // constructor, which use size as the table size
    HashTable(int size){
        // implement this method
        
        // Allocate table
        tableSize = size;
        table = new SLL<V>[tableSize];
    }
    
    // search item in the table
    // if found, return true; otherwise, return false
    bool find(V item){
        // implement this method
        
        // h(k) = k % table size
        int key = stoi(item) % tableSize;
        
        // Search for ssn in table at index "key"
        if (table[key].search(item) != nullptr){return true;}
        
        return false;
    }
    
    // insert (item1, item2) to the table
    // use item1 as the key
    // if inserted, return true
    // otherwise, return false
    bool insert(V item1, V item2){
        //implement this method
        
        // h(k) = k % table size
        int key = stoi(item1) % tableSize;
        
        if (table[key].getHeadPtr() == nullptr) {
            // Bucket is empty
            
            SLL<V> *newBucket = new SLL<V>; // Create new bucket
            newBucket->insert(item1, item2); // Insert new data into bucket
            
            table[key] = *newBucket; // Insert new bucket into table
            
            return true;
        } else {
            // Iterate through list in table at index "key"
            Node<V> *currNode = table[key].getHeadPtr();
            while (currNode != nullptr) {
                if (item1 == currNode->SSN){return false;} // Check if data is already in bucket
                currNode = currNode->next;
            }
            
            // Data is not in the bucket
            // Insert new data into bucket
            table[key].insert(item1, item2);
            
            return true;
        }
        
        return false;
    }
    
    // delete the pair whose key value is item
    // if deleted, return true
    // otherwise, return false
    bool erase(V item){
        // implement this method
        
        // h(k) = k % table size
        int key = stoi(item) % tableSize;
        
        // Iterate through list in table at index "key"
        Node<V> *currNode = table[key].getHeadPtr();
        while (currNode != nullptr) {
            
            // Found data to remove
            if (item == currNode->SSN) {
                return table[key].remove(item);
            }
            
            currNode = currNode->next;
        }
        
        return false;
    }
    
    // return the total number of nodes in the hash table
    int getSize(){
        // implement this method
        
        int totalNodes = 0;
        
        // Iterate through table
        for (int x = 0; x < tableSize; x++) {
            if (table[x].getHeadPtr() != nullptr) {
                // Sum the list sizes
                totalNodes += table[x].getSize();
            }
        }
        
        return totalNodes;
    }
    
};
