/* Adam Mellan */
/* CSC 230     */
/* Lab 3       */

#include <cstring>

void reverse(char* p) {
    int wordLength = strlen(p);

    // Iterate through half of the word
    for (int x = 0; x < wordLength/2; x++) {
        char temp = p[x];           // Temp variable set to index from left half
        p[x] = p[wordLength-1-x];   // Set index from left half to index from right half
        p[wordLength-1-x] = temp;   // Set index from right half to temp (aka index from left half)
    }
}