/* Adam Mellan */
/* CSC 230     */
/* Project 3   */

#include "DLL.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <ctime>

using namespace std;

void printLedger(const int iCount, const int dCount, const int rCount) {
    cout << "The Number of Valid Insertation: " << iCount << endl;
    cout << "The Number of Valid Deletion: " << dCount << endl;
    cout << "The Number of Valid Retrieval: " << rCount << endl;
    cout << "Item numbers in the list: " << (iCount - dCount) << endl;
}

int main(int argc, char *argv[]) {
    // Init and start timer
    double duration;
    clock_t start, end;
    start = clock();
    
    // Declare doubly linked list
    DLL ledger;
    
    // Declare counter variables
    int iCounter;
    int dCounter;
    int rCounter;
    
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
        
        switch (option[0]) {
            // Insert entry
            case 'i': {
                input >> ssn >> firstName >> lastName;
                fullName = firstName + " " + lastName;
                
                ledger.insert(ssn, fullName, iCounter);
                
                break;
            }
            // Delete entry
            case 'd': {
                input >> ssn >> skipInput >> skipInput;
                
                ledger.remove(ssn, dCounter);
                
                break;
            }
            // Retrieve entry
            case 'r': {
                input >> ssn >> skipInput >> skipInput;
                
                if (ledger.search(ssn) != -1) {
                    rCounter++;
                }
                
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
    printLedger(iCounter, dCounter, rCounter);
    
    // End timer
    end = clock();
    duration = (end - start) / (double)CLOCKS_PER_SEC;
    cout << "Time elapsed: " << duration << endl;
    
    return 0;
}