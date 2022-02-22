/*
 * Title: Sorting and Algorithm Efficiency
 * Author: Cemhan Kaan Özaltan
 * ID: 21902695
 * Section: 3
 * Assignment: 1
 * Description: The sorting algorithms are tested in this file
 */

#include <iostream>
#include "sorting.h"
using namespace std;

int main() {
    // create 4 identical arrays
    int arr1[] = {12, 7, 11, 18, 19, 9, 6, 14, 21, 3, 17, 20, 5, 12, 14, 8};
    int arr2[] = {12, 7, 11, 18, 19, 9, 6, 14, 21, 3, 17, 20, 5, 12, 14, 8};
    int arr3[] = {12, 7, 11, 18, 19, 9, 6, 14, 21, 3, 17, 20, 5, 12, 14, 8};
    int arr4[] = {12, 7, 11, 18, 19, 9, 6, 14, 21, 3, 17, 20, 5, 12, 14, 8};

    int size = 16; // initialize the size
    int compCount, moveCount; // declare compCount and moveCount

    // print the initial array
    cout << "Array: ";
    displayArray(arr1, size);

    // use selection sort on arr1 and display the key comparison count, data move count and the array after sorting
    selectionSort(arr1, size, compCount, moveCount);
    cout << "\n\nSelection Sort\n" << "compCount: " << compCount << endl << "moveCount: " << moveCount << endl << "Array after sorting: ";
    displayArray(arr1, size);

    // use merge sort on arr2 and display the key comparison count, data move count and the array after sorting
    mergeSort(arr2, size, compCount, moveCount);
    cout << "\n\nMerge Sort\n" << "compCount: " << compCount << endl << "moveCount: " << moveCount << endl << "Array after sorting: ";
    displayArray(arr2, size);

    // use quick sort on arr3 and display the key comparison count, data move count and the array after sorting
    quickSort(arr3, size, compCount, moveCount);
    cout << "\n\nQuick Sort\n" << "compCount: " << compCount << endl << "moveCount: " << moveCount << endl << "Array after sorting: ";
    displayArray(arr3, size);

    // use radix sort on arr4 and display the array after sorting
    radixSort(arr4, size);
    cout << "\n\nRadix Sort\n" << "Array after sorting: ";
    displayArray(arr4, size);

    cout << endl << endl;
    performanceAnalysis(); // call the performanceAnalysis function

    return 0;
}