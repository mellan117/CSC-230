#include <iostream>

using namespace std;

int main() {
    int x, y;

    cout << "Enter the amount of rows:" << endl;
    cin >> x;

    cout << "Enter the amount of columns:" << endl;
    cin >> y;

    char array[x][y];

    for (int row = 0; row < x; row++) {
        for (int col = 0; col < y; col++) {
            cin >> array[row][col];
        }
    }

    for (int row = 0; row < x; row++) {
        for (int col = 0; col < y; col++) {
            cout << array[row][col] << "\t";
        }
        cout << endl;
    }

    return 0;
}