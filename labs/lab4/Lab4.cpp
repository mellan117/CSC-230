/* Adam Mellan */
/* CSC 230     */
/* Lab 4       */

#include <iostream>
#include <fstream>

using namespace std;

struct Person{
        string ssn;
        string fullName;
};

int main(int argc, char *argv[]) {
    // Declare variables
    struct Person record[1000];
    int index;
    string ssnX; // SSN to search for
    string option; // Possible values 'i', 'd', 'r'
    string firstName, lastName;

    fstream input(argv[1]); // Create input stream from file

    // Iterate through the file
    while (!input.eof()) {
        // Take in input from the file and assign it to the record
        input >> option >> record[index].ssn >> firstName >> lastName;
        record[index].fullName = firstName + " " + lastName;

        if (!input) break; // Break at the end of the file

        index++;
    }
    input.close(); // Close the text file

    // Prompt the user to search for an ssn
    cout << "Input a SSN:" << endl;
    cin >> ssnX;

    // Search through the record for the user ssn
    for (int x = 0; x < index; x++) {
        if (!ssnX.compare(record[x].ssn)) {
            cout << "Found at location " << x << endl;
        }
    }
}