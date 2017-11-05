/* Adam Mellan */
/* Dr. Li      */
/* CSC 230     */
/* Project 4   */

#include <iostream>
#include <fstream>
#include "hashTable.h"
#include <string>
#include <time.h>
#include <ctime>

using namespace std;

void printTable(const int iCount, const int dCount, const int rCount, int total) {
    cout << "The Number of Valid Insertation: " << iCount << endl;
    cout << "The Number of Valid Deletion: " << dCount << endl;
    cout << "The Number of Valid Retrieval: " << rCount << endl;
    cout << "Item numbers in the list: " << total << endl;
}

int main(int argc, char* argv[]){
    
    // implement this missing part
    // make the array size inside the hash table is 10007
    
    // Init and start timer
    double duration;
    clock_t start, end;
    start = clock();
    
    // Declare hash table
    HashTable<string> *table = new HashTable<string>(10007);
    
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
                if (table->insert(ssn, fullName)){iCounter++;}
                
                break;
            }
                // Delete entry
            case 'd': {
                if (table->erase(ssn)){dCounter++;}
                
                break;
            }
                // Retrieve entry
            case 'r': {
                if (table->find(ssn)){rCounter++;}
                
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
    printTable(iCounter, dCounter, rCounter, table->getSize());
    
    // End timer
    end = clock();
    duration = (end - start) / (double)CLOCKS_PER_SEC;
    cout << "Time elapsed: " << duration << endl;
    return 0;
}
