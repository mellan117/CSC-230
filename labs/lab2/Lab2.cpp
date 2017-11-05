/* Adam Mellan */
/* CSC 230-2   */
/* Lab 2       */

#include <iostream>
#include <vector>
#include <cstring>
#include <stdlib.h>

using namespace std;

// Check if word is in the matrix
bool check(vector<vector<char> > &matrix, char *word, int x, int y) {
    // Init variables
    int wordLength = strlen(word);

    // Iterate left to right through the matrix starting at (x,y)
    // and determine if the word is in the matrix
    for (int i = 0; i < strlen(word); i++) { // Only check "i" number of chars from the starting (x,y)
        if ((x + (wordLength-1)) <= matrix[x].size()-1) { // Check bounds

            if (matrix[y][x+i] != word[i]) { // If a char does NOT match the corresponding char in the word
                return false;                // then return false
            } else if (i == (wordLength-1)) { // else if all the chars match
                return true;                  // then return true
            }
        }
    }

    return false; // Default return statement
}

int main(int argc, char *argv[]) {
    // Init variablesx
    char *word = argv[1];
    int row, col;

    // Input row and column
    cin >> row;
    cin >> col;

    // Create the matrix from a file
    vector<vector<char> > matrixVector;
    matrixVector.resize(row);
    for (int x = 0; x < row; x++) {
        matrixVector[x].resize(col);
        for (int y = 0; y < col; y++) {
            cin >> matrixVector[x][y];
        }
    }

    for (int x = 0; x < matrixVector.size(); x++) {
        for (int y = 0; y < matrixVector[x].size(); y++) {
            cout << matrixVector[x][y] << " ";
        }
        cout << endl;
    }

    // Log to console if the word is in the matrix
    if (check(matrixVector, word, atoi(argv[2]), atoi(argv[3]))) {
        cout << "true";
    } else {
        cout << "false";
    }

    return 0;
}