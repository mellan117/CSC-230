/* Adam Mellan */
/* CSC 230     */
/* Lab 12      */

#include <iostream>
#include <fstream>
using namespace std;

int partition(int arr[], int left, int right) {
   int l = 0;
   int r = 0;
   int midpoint = 0;
   int pivot = 0;
   int temp = 0;
   bool done = false;
   
   // Find midpoint index and set pivot value
   midpoint = left + (right - left) / 2;
   pivot = arr[midpoint];
   
   l = left;
   r = right;
   
   while (!done) {
      
      // Increment l while arr[l] < pivot
      while (arr[l] < pivot) {
         l++;
      }
      
      // Decrement r while pivot < arr[r]
      while (pivot < arr[r]) {
         r--;
      }
      
      // If there are 0 or 1 elements left
      // then all numbers are partitioned. Return r
      if (l >= r) {
         done = true;
      } else {
         // Swap arr[l] and arr[r]
         temp = arr[l];
         arr[l] = arr[r];
         arr[r] = temp;
         
         // Update l and r
         l++;
         r--;
      }
   }
   
   return r;
}

void quickSort(int arr[], int left, int right) {
   int midpoint = 0;
   
   // Base case: 1 or 0 elements in parition
   // Parition is already sorted
   if (left >= right) {
      return;
   }
   
   // Parition the data and return the location of the last element in the left parition
   midpoint = partition(arr, left, right);
   
   // Recursively sort left partition (left to midpoint)
   // Recursively sort right partition (midpoint+1, right)
   quickSort(arr, left, midpoint);
   quickSort(arr, midpoint+1, right);
   
   return;
}

int main(int argc, char* argv[]){
  fstream input(argv[1]);

  int vals[5000];

    // please implement this function
   
    int index = 0;
    int data = 0;

    // Iterate through the file
    while (!input.eof()) {

        // Take in the data
        input >> data;
        vals[index] = data;
        index++;

        if (!input) break; // Break at the end of the file
    }

    // Sort the data
   quickSort(vals, 0, index - 1);
   
   // Print sorted data
   cout << "Quick Sort Result is:" << endl;
   for(int i = 0; i < index; ++i) {
      cout << vals[i] << endl;
   }
}
