/* Adam Mellan */
/* CSC 230     */
/* Project 5   */

#include <iostream>
#include <fstream>
#include "AVLTree.h"
#include <string>
#include <time.h>
#include <ctime>

using namespace std;

void printTree(const int iCount, const int dCount, const int rCount, const int height) {
    cout << "The Number of Valid Insertation: " << iCount << endl;
    cout << "The Number of Valid Deletion: " << dCount << endl;
    cout << "The Number of Valid Retrieval: " << rCount << endl;
    cout << "The height of the AVL tree: " << height << endl;
}

int main(int argc, char* argv[]){
    // Init and start timer
    double duration = 0.0;
    clock_t start, end;
    start = clock();
    
    // Declare tree
    AVLTree tree;
    
    // Declare counter variables
    int iCounter = 0;
    int dCounter = 0;
    int rCounter = 0;
    
    // Declare input variables
    string option; // Possible values 'i', 'd', 'r'
    string ssn, firstName, lastName, fullName;
    string skipInput; // Variable to skip over undesired input
    
    // Create input stream from file
    fstream input(argv[1]);
    
    // Iterate through the file
    while (!input.eof()) {
        // Take in input from the file and assign it to the ledger
        input >> option;
        input >> ssn >> firstName >> lastName;
        fullName = firstName + " " + lastName;
        
        switch (option[0]) {
                // Insert entry
            case 'i': {
                if (tree.insert(ssn, fullName)){iCounter++;}
                
                break;
            }
                // Delete entry
            case 'd': {
                if (tree.deleteNode(ssn)){dCounter++;}
                
                break;
            }
                // Retrieve entry
            case 'r': {
                if (tree.find(ssn)){rCounter++;}
                
                break;
            }
                
            default : {
                input >> skipInput >> skipInput >> skipInput;
                
                break;
            }
        }
        
        option = "";
        firstName = "";
        lastName = "";
        
        if (!input) break; // Break at the end of the file
    }
    input.close(); // Close the text file
    
    // Print out program results
    int treeHeight = tree.height(tree.getRoot());
    printTree(iCounter, dCounter, rCounter, treeHeight);
    
    // End timer
    end = clock();
    duration = (end - start) / (double)CLOCKS_PER_SEC;
    cout << "Time elapsed: " << duration << endl;
    
    tree.levelOrder();
    
    return 0;
}
