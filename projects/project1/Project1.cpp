/* Adam Mellan */
/* CSC 230-2   */
/* Project 1   */

#include <iostream>
#include <vector>
#include <cstring>
#include <stdlib.h>
#include "colormod.h"

using namespace std;

// Global variables
Color::Setting red(Color::FG_RED);
Color::Setting defaultColor(Color::FG_DEFAULT);

// Interface - method declarations
void transferColorDataToNewColorMatrix(vector<vector<int> > &matrixA, vector<vector<int> > &matrixB);
void findWordInMatrix(vector<vector<char> > &matrix, vector<vector<int> > &colorMatrix, char *word);
void printMatrix(vector<vector<char> > &matrix, vector<vector<int> > &colorMatrix);
void printColorMatrix(vector<vector<int> > &colorMatrix);

void transferColorDataToNewColorMatrix(vector<vector<int> > &matrixA, vector<vector<int> > &matrixB) {
    // This method prevents the color data from incorrectly being overwritten
    // when checking for word "x" in different directions
    // or
    // when checking for a different word.
    //
    // This method copies the color data (1's)
    // from the pervious version of the colorMatrix
    // to the newly modified colorMatrix
    for (int x = 0; x < matrixA.size(); x++) {
        for (int y = 0; y < matrixA[x].size(); y++) {
            if ((matrixA[x][y] == 1) && (matrixB[x][y] == 0)) {
                matrixB[x][y] = 1;
            }
        }
    }
}

void findWordInMatrix(vector<vector<char> > &matrix, vector<vector<int> > &colorMatrix, char *word) {
    // Iterate through the matrix
    for (int x = 0; x < matrix.size(); x++) {
        for (int y = 0; y < matrix[x].size(); y++) {
            
            // If the char at (x,y) == to the 1st char of the word
            if (matrix[x][y] == word[0]) {

                // Check for the word in all 8 directions
                for (int i = 1; i <= 8; i++) {

                    // Init variables
                    bool isInBounds = false;
                    int wordLength = strlen(word);
                    int p, q; // Direction variables (p: up & down) (q: left & right)

                    switch (i) {
                        case 1: { // Check left to right
                            if ((y + (wordLength-1)) <= matrix[x].size()-1) { // Check bounds
                                isInBounds = true;
                                p = 0; // Null
                                q = 1; // Right
                            }

                            break;
                        }
                        case 2: { // Check right to left
                            if ((y - (wordLength-1)) >= 0) { // Check bounds
                                isInBounds = true;
                                p = 0; // Null
                                q = -1; // Left
                            }

                            break;
                        }
                        case 3: { // Check up to down
                            if ((x + (wordLength-1)) <= matrix[x].size()-1) { // Check bounds
                                isInBounds = true;
                                p = 1; // Down
                                q = 0; // Null
                            }

                            break;
                        }
                        case 4: { // Check down to up
                            if ((x - (wordLength-1)) >= 0) { // Check bounds
                                isInBounds = true;
                                p = -1; // Up
                                q = 0; // Null
                            }

                            break;
                        }
                        case 5: { // Check diagonal up-right
                            if ((x - (wordLength-1)) >= 0) { // Check vertical bounds
                                if ((y + (wordLength-1)) <= matrix[x].size()-1) { // Check horizontal bounds
                                    isInBounds = true;
                                    p = -1; // Up
                                    q = 1; // Right
                                }
                            }
                    
                            break;
                        }
                        case 6: { // Check diagonal up-left
                            if ((x - (wordLength-1)) >= 0) { // Check vertical bounds
                                if ((y - (wordLength-1)) >= 0) { // Check horizontal bounds
                                    isInBounds = true;
                                    p = -1; // Up
                                    q = -1; // Left
                                }
                            }

                            break;
                        }
                        case 7: { // Check diagonal down-right
                            if ((x + (wordLength-1)) <= matrix.size()-1) { // Check vertical bounds
                                if ((y + (wordLength-1)) <= matrix[x].size()-1) { // Check horizontal bounds
                                    isInBounds = true;
                                    p = 1; // Down
                                    q = 1; // Right
                                }
                            }

                            break;
                        }
                        case 8: { // Check diagonal down-left
                            if ((x + (wordLength-1)) <= matrix.size()-1) { // Check vertical bounds
                                if ((y - (wordLength-1)) >= 0) { // Check horizontal bounds
                                    isInBounds = true;
                                    p = 1; // Down
                                    q = -1; // Left
                                }
                            }

                            break;
                        }
                        default: {
                            break;
                        }
                    }

                    // Only check for word in that direction if it is in bounds
                    // This algorithmn can check all 8 directions by multipling "a" by "p" or "q"
                    // "p" and "q" are set to either 1, -1, or 0 which allows the method to negate the direction.
                    // Example: x = 5, a = 2, p = -1;   (x + (a * p)) = (5 + (-2)) = (5 - 2)
                    // vs.
                    //          x = 5, a = 2, p = 1;    (x + (a * p)) = (5 + (2))  = (5 + 2)
                    if (isInBounds) {
                        vector<vector<int> > colorMatrix1(colorMatrix); // Copy colorMatrix to new matrix before modifying

                        for (int a = 0; a < strlen(word); a++) { // Only check "a" number of chars from the starting (x,y)
                            colorMatrix[x+(a*p)][y+(a*q)] = 1; // By default assign all chars to have color

                            if (matrix[x+(a*p)][y+(a*q)] != word[a]) { // If a char does NOT match the corresponding char in the word
                                for (int b = a; b >= 0; b--) { // Then iterate back over the chars checked
                                    colorMatrix[x+(b*p)][y+(b*q)] = 0; // and revert them all back to DEFAULT color value
                                }

                                break;
                            }
                        }
                        transferColorDataToNewColorMatrix(colorMatrix1, colorMatrix); // Safeguard to prevent color data from being incorrectly overwritten

                    }
                }
            }
        }
    }
}

void printMatrix(vector<vector<char> > &matrix, vector<vector<int> > &colorMatrix) {
    // Print the matrix with color
    // colorMatrix data: "1" represents color, "0" represents default color
    for (int x = 0; x < matrix.size(); x++) {
        for (int y = 0; y < matrix[x].size(); y++) {
            if (colorMatrix[x][y] == 1) {
                cout << red << matrix[x][y];
            } else {
                cout << defaultColor << matrix[x][y];
            }
        }
        cout << endl;
    }
}

void printColorMatrix(vector<vector<int> > &colorMatrix) {
    // Print the colorMatrix data with color
    // colorMatrix data: "1" represents color, "0" represents default color
    for (int x = 0; x < colorMatrix.size(); x++) {
        for (int y = 0; y < colorMatrix[x].size(); y++) {
            if (colorMatrix[x][y] == 1) {
                cout << red << colorMatrix[x][y];
            } else {
                cout << defaultColor << colorMatrix[x][y];
            }
        }
        cout << endl;
    }
}

int main(int argc, char *argv[]) {
    // Declare variables
    vector<vector<int> > colorMatrix;
    int row, col;

    // Input row and column
    cin >> row;
    cin >> col;

    // Create the matrix from a file
    vector<vector<char> > matrix;
    matrix.resize(row);
    colorMatrix.resize(row);
    for (int x = 0; x < row; x++) {
        matrix[x].resize(col);
        colorMatrix[x].resize(col);
        for (int y = 0; y < col; y++) {
            cin >> matrix[x][y];
            colorMatrix[x][y] = 0;
        }
    }

    // Find the inputed words in the matrix
    for (int x = 1; x < argc; x++) {
        findWordInMatrix(matrix, colorMatrix, argv[x]);
    }

    // Print the matrix with color
    cout << endl;
    printMatrix(matrix, colorMatrix);

    // Print the colorMatrix data
    cout << endl;
    //printColorMatrix(colorMatrix);

    return 0;
}