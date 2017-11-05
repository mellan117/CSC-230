/* Adam Mellan */
/* CSC 230     */
/* Lab 9       */

#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>

using namespace std;

long hashCode(char *s) {
    int wordLen = strlen(s);
    long key = 0;

    //       n-1
    // h(s) = E  s[x] * 31^(n-1-x)
    //       x=0
    for (int x = 0; x < wordLen; x++) {
        key += s[x] * pow(31, wordLen-1-x);
    }

    return key % 10007;
}

int main(int argc, char *argv[]) {
    // Init "hash table"
    // Not real hash table
    // if value at key "x" is false then bucket is considered empty
    // if value at key "x" is true then bucket is considered NOT empty
    bool hashTable[10007]; // Init array to null or "false" values
    
    
    // Declare counter variables
    int inputCounter = 0;
    int collisionCounter = 0;
    
    // Create input stream from file
    fstream inputStream(argv[1]);
    string inStr;
    
    // Iterate through the file
    while (!inputStream.eof()) {
        // Take in input from the file
        inputStream >> inStr;

        // Convert type string to type Cstring
        char inputCStr[inStr.length()];
        strcpy(inputCStr, inStr.c_str());

        // Assign the key value
        long key = hashCode(inputCStr);
        
        if (!hashTable[key]) {
            // Bucket is EMPTY
            hashTable[key] = true; // Add element to bucket
            inputCounter++;
        } else {
            // Bucket is NOT empty
            // Collision has occured
            inputCounter++;
            collisionCounter++;
        }
        
        if (!inputStream) break; // Break at the end of the file
    }
    inputStream.close(); // Close the text file
    inputCounter--;
    
    // Program output
    cout << "Total Input is " << inputCounter << endl;
    cout << "Collision # is " << collisionCounter << endl;
    
    return 0;
}