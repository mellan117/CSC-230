/* Adam Mellan */
/* CSC 230     */
/* Project 2   */

#include <iostream>
#include <fstream>
#include <cstdio>
#include <ctime>

using namespace std;

// Declare a struct containing personal info
struct Person{
    string ssn;
    string fullName;
};

// Check to see if array needs to be resized
void checkArraySize(struct Person *&ledger, int &ledgerSize, char option) {
    switch(option) {
        // Check if array needs to be increased
        case 'i': {
            if (ledger[ledgerSize-1].ssn.length() != 0) { // If last element in array contains an object
                struct Person *newLedger = new Person[ledgerSize*2]; // Create a new temp array with double the size

                // Transfer data from the old array to the new larger array
                for (int x = 0; x < ledgerSize; x++) {
                    newLedger[x] = ledger[x];
                }
                delete [] ledger; // Release the old array
        
                ledger = newLedger; // Init the old array with the new larger array
                ledgerSize *= 2; // Update the array size variable
            }
            break;
        }

        // Check if the array needs to be decreased
        case 'd': {
            if (ledger[(ledgerSize/4)-1].ssn.length() == 0) { // If the array is less than 1/4 fullName
                struct Person *newLedger = new Person[ledgerSize/2]; // Create a new temp array with half the size

                // Transfer data from the old array to the new smaller array
                for (int x = 0; x < ledgerSize; x++) {
                    if (ledger[x].ssn.length() == 0) {break;}
                        newLedger[x] = ledger[x];
                }
                delete [] ledger; // Release the old array
        
                ledger = newLedger; // Init the old array with the new smaller array
                ledgerSize /= 2; // Update the array size variable
            }
            break;
        }

        default : {break;}
    }
}

void insertInfo(struct Person *&ledger, int &ledgerSize, fstream &input, int &index, int &insertCount) {
    // Declare variables
    string firstName, lastName;
    string ssnX;
    string skipInput;

    input >> ssnX; // Input the ssn of the entry that needs to be inserted into the array

    checkArraySize(ledger, ledgerSize, 'i'); // Check to see if the array is full before attempting to insert a new entry into the array

    // Iterate through the ledger
    for (int x = 0; x < ledgerSize; x++) {
        if (ssnX == ledger[x].ssn) { // Check if the ssn is already in the array
            input >> skipInput;
            input >> skipInput;

            break;
        } else if (ledger[x].ssn.length() == 0) {
            // If that ssn is NOT in the array then add that entry
            input >> firstName >> lastName;

            ledger[index].ssn = ssnX;
            ledger[index].fullName = firstName + " " + lastName;
            
            // Update counter variables
            index++;
            insertCount++;

            break;
        }
    }
}

void deleteInfo(struct Person *&ledger, int &ledgerSize, fstream &input, int &index, int &deleteCount) {
    // Declare variables
    string ssnX;
    string skipInput;

    input >> ssnX; // Input the ssn of the entry that needs to be deleted from the array

    // Iterate through the array
    for (int x = 0; x < ledgerSize; x++) {
        if (ledger[x].ssn.length() != 0) { // Check if element is not empty
            if (ssnX == ledger[x].ssn) { // Check if the inputed ssn matches any entries

                // Starting at the index of the entry to be deleted
                // shift all of the entries 1 to the left
                // which overwrites the entry to be deleted
                while (x < ledgerSize && ledger[x].ssn.length() != 0) {

                    if (x == ledgerSize-1) { // Bounds check, assign last element to ""
                        ledger[x].ssn = "";
                        ledger[x].fullName = "";
                    } else {
                        ledger[x].ssn = ledger[x+1].ssn;
                        ledger[x].fullName = ledger[x+1].fullName;
                    }
                    x++;
                }
                checkArraySize(ledger, ledgerSize, 'd'); // Check to see if the array is more than 3/4 empty and should be downsized

                // Update counter variables
                deleteCount++;
                index = x-1;
                break;
            }
        } else {break;}
    }
            
    input >> skipInput;
    input >> skipInput;
}

void retrieveInfo(struct Person *&ledger, int &ledgerSize, fstream &input, int &retrieveCount) {
    // Declare variables
    string ssnX;
    string skipInput;

    input >> ssnX; // Input ssn of entry to be retrieved

    // Iterate through the array
    for (int x = 0; x < ledgerSize; x++) {
        if (ssnX == ledger[x].ssn) { // Check if the ssn matches an entry in the array
            retrieveCount++;         // Update the counter
        } else if (ledger[x].ssn.length() == 0) { break;}
    }

    input >> skipInput;
    input >> skipInput;
}

void printLedger(const struct Person *ledger, const int ledgerSize, const int insertCount, const int deleteCount, const int retrieveCount) {
    cout << "The Number of Valid Insertation: " << insertCount << endl;
    cout << "The Number of Valid Deletion: " << deleteCount << endl;
    cout << "The Number of Valid Retrieval: " << retrieveCount << endl;
    cout << "Item numbers in the array: " << (insertCount - deleteCount) << endl;
    cout << "Array Size is: " << ledgerSize << endl;

    /*cout << endl;
    cout << "Index \t SSN \t\t Name" << endl;
    for (int x = 0; x < ledgerSize; x++) {
        if (ledger[x].ssn.length() != 0) {
            cout << x << "\t" << ledger[x].ssn << "\t" << ledger[x].fullName << endl;
        } else {
            break;
        }
    }*/
}

int main(int argc, char *argv[]) {
    // Init and start timer
    clock_t start, end;
    start = clock();

    // Declare and init the entry array
    int recordSize = 1000;
    struct Person *record = new Person[recordSize];
    
    // Declare variables
    double duration;
    int index = 0;
    int insertionCount = 0;
    int deletionCount = 0;
    int retrievalCount = 0;
    string option; // Possible values 'i', 'd', 'r'
    string ssnX; // SSN to search for
    string firstName, lastName;
    string skipInput; // Variable to skip over undesired input

    // Create input stream from file
    fstream input(argv[1]);

    // Iterate through the file
    while (!input.eof()) {
        // Take in input from the file and assign it to the record
        input >> option;

        switch (option[0]) {
            // Insert entry
            case 'i': {
                insertInfo(record, recordSize, input, index, insertionCount);

                break;
            }
            // Delete entry
            case 'd': {
                deleteInfo(record, recordSize, input, index, deletionCount);

                break;
            }
            // Retrieve entry
            case 'r': {
                retrieveInfo(record, recordSize, input, retrievalCount);

                break;
            }

            default :{
                input >> skipInput;
                input >> skipInput;
                input >> skipInput;

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
    printLedger(record, recordSize, insertionCount, deletionCount, retrievalCount);

    end = clock();
    duration = ( end - start ) / (double) CLOCKS_PER_SEC;

    cout << "Time elapsed: " << duration << endl;

    return 0;
}