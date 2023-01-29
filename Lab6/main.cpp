#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
//
// COMSC-210 Lab #6
//
// Below is an implementation of merge sort for an array of integers.
//
// The length of our array to be sorted
const int ARRAYLEN = 10;
void merge(int a[], int first, int middle, int last) {
    int temp[ARRAYLEN] = { 0 };      // "Auxiliary" array to hold merged arrays
    int left = 0;                    // Counters to track positions in arrays, see below

    int right = 0;
    int cur = 0;
    int start = 0, stop = 0;
    // Loop through the left and right side sub-arrays, adding the next value
    // to the final array.  Remember, both sub-arrays are sorted at this point.

    for (left = first,         // 'left' will track the current position in the left side, starting from the first position
         right = middle;       // 'right' will track the current position in the right side, starting from the middle position
         left < middle &&      // Continue as long as we have not exhausted the
         right < last;         // left OR right sides.
         cur++) {              // Each time through the array, increment the current position
                               // in the auxiliary array (contains the final,merged result)
        // The left side is next
        if (a[left] <= a[right]) {   // when left side value is smaller than the right side value then take the left side value and put it in to the temp array.
            temp[cur] = a[left];     // Set the next value in the merged array
            left++;           // "consume" one value in the left side

        } else {                // when right side value is smaller than the left side value then take the right side value and put it in to the temp array.
        // The right side is next
            temp[cur] = a[right];    // Set the next value in the merged array
            right++;             // "consume" one value in the right side
        }
    }

    // At this point we have exhausted either the left or right side.  Find
    // which one is *not* exhausted, then add each element to the final
    // merged array.
    if (left == middle) {
        start = right;          // The left side was exhausted first, right side needs copying
        stop = last;
    } else {
        start = left;           // The right side was exhausted first, left side needs copying
        stop = middle;
    }

    // Copy the remaining part of the array that still has elements
    while (start < stop) {
        temp[cur++] = a[start++]; // when left side is finish early, putting the right side elements to the temp array or vice versa.
    }
    // and we're done!  The 'temp' array contains the merged
    // values at this point.  Replace the values in the array that
    // was passed with the sorted values.

    cout<<"Left side: ";
    //print the left side
    for(int i = first; i < middle; i++){
        cout<< a[i] << " "; // showing the current elements of left side
    }
    cout<< endl;

    cout<<"Right side: ";
    //print the right side
    for(int i = middle; i < last; i++){
        cout<< a[i] << " "; // showing the current elements of right side
    }
    cout<<endl;

    cout<<"Merged array: "; //print the Merged array
    for (int i = first, j = 0; i < last; i++, j++) { // 'i' holds the current position in the array
        a[i] = temp[j];              // 'j' holds the current position in the temp array
        cout << a[i] << " ";         // showing the current elements of current temp array
    }
    cout << endl;
}
//
// A recursive version of merge sort.
// The function is first called with the entire array:
//     first == the beginning (index 0)
//     last == the size of the array (ARRAYLEN)
//
// Each subsequent (recursive) call divides the array into halves and a
// a call is made for each half, until there is an array of length 1.  An
// array of length 1 is already sorted, so the merge can continue.
//
void mergeSort(int a[], int first, int last) {
    int middle = first + (last - first) / 2;
    // To see the recursive calls, uncomment this and the indices will be printed
    // cout << "indices: " << first << " " << middle << " " << last << endl; try this and it showes the first and mid and last continuously
    // Base case:  the length of this sub-array is less than 1 for
    // each side (the total array length must be at least 2).
    if ((last - first) < 2)
        return;
    // Sort the left side
    mergeSort(a, first, middle);
    // Sort the right side
    mergeSort(a, middle, last);
    // Merge the left and right sub-arrays
    merge(a, first, middle, last);
}
//
// Add your main() function here. It should:
//  - Make an array to sort (a local variable is OK)
//  - Call mergeSort() to start the sorting and print the annotations
//  - Verify that the array is sorted
int main(){

    const int MSIZE = 10;
    int mine[MSIZE];
    srand(time(0)); rand();
    bool sorted = true;
    for(int i = 0; i < MSIZE; i++){
        int item = 1 + rand() % 100;
        mine[i] = item;
    }
    mergeSort(mine, 0, MSIZE);
    for(int i = 1; i < MSIZE; i++){
        if(mine[i-1] > mine[i]){
            sorted = false;
        }
    }
    if(sorted == true){ cout <<"Sort verification passed" << endl;}



}
