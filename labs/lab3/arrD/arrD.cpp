/* Adam Mellan */
/* CSC 230     */
/* Lab 3       */

#include <iostream>
#include <cstring>

using namespace std;

int main() {
    // Init variables
    char word[50];
    int indexToDelete = -1;

    // Take input from user
    cin >> word;
    cin >> indexToDelete;

    cout << "The result is: ";

    // Iterate through word
    for (int x = 0; x < strlen(word); x++) {
        if (x < indexToDelete) { // All chars before the indexToDelete do NOT change
            word[x] = word[x];
            cout << word[x] << ' ';
        } else if (x > indexToDelete) { // All chars after the indexToDelete get shifted to the left by one
            word[x-1] = word[x];
            cout << word[x] << ' ';
        }
    }
    word[strlen(word)-1] = ' '; // Reset the last element to ' '
}