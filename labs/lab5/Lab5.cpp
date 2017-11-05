/* Adam Mellan */
/* CSC 230     */
/* Lab 5       */

#include <iostream>
#include <cstdlib>

using namespace std;

int A[100]; // Global array

// Recrusive function
void com(int n, int t) {
    if (n<1) { // Base case
        // Print out the array A
        for (int x = 0; x < t; x++) {
            cout << A[x];
        }
        cout << endl;
        return;
    } else if (n>=1) { // Recursive case
        // Assign A[n-1] with different values
        for (int x = 0; x < 10; x++) {
            A[n-1] = x;
            com(n-1,t); // Recursive call
        }
        
        return;
    }
}

int main(int arc, char *argv[]) {
    // First call of recursive function
    com(atoi(argv[1]), atoi(argv[1]));
}