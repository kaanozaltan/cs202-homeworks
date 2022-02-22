/*
 * Title: Sorting and Algorithm Efficiency
 * Author: Cemhan Kaan Özaltan
 * ID: 21902695
 * Section: 3
 * Assignment: 1
 * Description: The implementations of the sorting algorithms, helper functions and
 * additional functions are included in this file
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "sorting.h"
using namespace std;

/*
 * sorts the array using selection sort algorithm
 * returns the key comparison and data move count using pass by reference
 * @param arr array to be sorted
 * @param size size of arr
 * @param compCount key comparison count to be returned
 * @param moveCount data move count to be returned
 */
void selectionSort(int *arr, const int size, int &compCount, int &moveCount) {
    compCount = moveCount = 0; // reset compCount and moveCount

    // pick the largest element of the unsorted subarray and swap it with
    // the last element of the unsorted subarray for each element of the array
    for (int last = size - 1; last >= 1; last--) {
        int largest = 0;
        for (int i = 1; i < last + 1; i++) {
            if (arr[i] > arr[largest])
                largest = i;
            compCount++; // increment compCount for each comparison
        }

        // swap largest with last
        int tmp = arr[largest];
        arr[largest] = arr[last];
        arr[last] = tmp;

        moveCount = moveCount + 3; // add 3 to moveCount for the swap
    }
}

/*
 * sorts the array using merge sort algorithm
 * returns the key comparison and data move count using pass by reference
 * @param arr array to be sorted
 * @param size size of arr
 * @param compCount key comparison count to be returned
 * @param moveCount data move count to be returned
 */
void mergeSort(int *arr, const int size, int &compCount, int &moveCount) {
    compCount = moveCount = 0; // reset compCount and moveCount

    // determine the first and last indices of the array and pass them to mergeSortHelper
    int first = 0;
    int last = size - 1;
    mergeSortHelper(arr, size, first, last, compCount, moveCount);
}

/*
 * helper function for mergeSort which recursively sorts each half of the array and merges them
 * returns the key comparison and data move count using pass by reference
 * @param arr array to be sorted
 * @param size size of the original array
 * @param first index of first item in arr
 * @param last index of last item in arr
 * @param compCount key comparison count to be returned
 * @param moveCount data move count to be returned
 */
void mergeSortHelper(int *arr, const int size, const int first, const int last, int &compCount, int &moveCount) {
    // if first >= last, base case is reached and arr is sorted
    if (first < last) {
        int mid = (first + last) / 2; // index of arr's mid element

        // call the mergeSortHelper function for both halves
        mergeSortHelper(arr, size, first, mid, compCount, moveCount);
        mergeSortHelper(arr, size, mid + 1, last, compCount, moveCount);

        // merge the two sorted halves
        merge(arr, size, first, mid, last, compCount, moveCount);
    }
}

/*
 * merges the parts of the given array in ascending order
 * returns the key comparison and data move count using pass by reference
 * @param arr array to merge the parts of
 * @param size size of the original array
 * @param first index of first item in first subarray
 * @param mid index of last item in first subarray
 * @param last index of first item in second subarray
 * @param compCount key comparison count to be returned
 * @param moveCount data move count to be returned
 */
void merge(int *arr, const int size, const int first, const int mid, const int last, int &compCount, int &moveCount) {
    int tmp[size]; // temporary array
   
	int first1 = first; // index of first item in first subarray
    int last1 = mid; // index of last item in first subarray
    int first2 = mid + 1; // index of first item in second subarray
    int last2 = last; // index of last item in second subarray
    int index = first1; // next available location in tmp

    // compare pairs from the subarrays and add the smallest one to tmp
    for (; (first1 <= last1) && (first2 <= last2); index++) {
        if (arr[first1] < arr[first2]) {  
            tmp[index] = arr[first1];
            first1++;
        } else {  
            tmp[index] = arr[first2];
            first2++;
        }

        // increment compCount and moveCount
        compCount++;
        moveCount++;
    }

    // add the remaining elements of the first subarray to tmp
    for (; first1 <= last1; first1++, index++) {
        tmp[index] = arr[first1];
        moveCount++; // increment moveCount
    }

    // add the remaining elements of the second subarray to tmp
    for (; first2 <= last2; first2++, index++) {
        tmp[index] = arr[first2];
        moveCount++; // increment moveCount
    }

    // add the elements of tmp to the specific indices of the original array
    for (index = first; index <= last; index++) {
        arr[index] = tmp[index];
        moveCount++; // increment moveCount
    }
}

/*
 * sorts the array using quick sort algorithm
 * returns the key comparison and data move count using pass by reference
 * @param arr array to be sorted
 * @param size size of arr
 * @param compCount key comparison count to be returned
 * @param moveCount data move count to be returned
 */
void quickSort(int *arr, const int size, int &compCount, int &moveCount) {
    compCount = moveCount = 0; // reset compCount and moveCount

    // determine the indices of the first and last elements and pass them to quickSortHelper
    int first = 0;
    int last = size - 1;
    quickSortHelper(arr, first, last, compCount, moveCount);
}

/*
 * helper function for quickSort which partitions the array and recursively sorts it
 * returns the key comparison and data move count using pass by reference
 * @param arr array to be sorted
 * @param first index of first item in arr
 * @param last index of last item in arr
 * @param compCount key comparison count to be returned
 * @param moveCount data move count to be returned
 */
void quickSortHelper(int *arr, const int first, const int last, int &compCount, int &moveCount) {
    int pivotIndex;

    if (first < last) {
        // find and set the index of the partition of the array
        partition(arr, first, last, pivotIndex, compCount, moveCount);

        // call the quickSortHelper function for the first and second subarrays
        quickSortHelper(arr, first, pivotIndex - 1, compCount, moveCount);
        quickSortHelper(arr, pivotIndex + 1, last, compCount, moveCount);
   }
}

/*
 * partitions the array using its first element as pivot
 * returns the pivot index, key comparison and data move count using pass by reference
 * @param arr array to partition
 * @param size size of arr
 * @param compCount key comparison count to be returned
 * @param moveCount data move count to be returned
 */
void partition(int *arr, const int first, const int last, int& pivotIndex, int &compCount, int &moveCount) {
    int pivot = arr[first];

    int lastS1 = first; // index of last item in S1
    int firstUnknown = first + 1; // index of first item in unknown
   
	// move one item at a time until unknown region is empty
    for (; firstUnknown <= last; firstUnknown++) {

        // move item from unknown to the proper subarray depending on whether
        // it is smaller or greater than or equal to the pivot
        if (arr[firstUnknown] < pivot) {
		    lastS1++;
            int tmp = arr[firstUnknown];
            arr[firstUnknown] = arr[lastS1];
            arr[lastS1] = tmp;
            moveCount += 3; // increment moveCount by 3 for the swap
        }
        compCount++; // increment compCount for the condition in if
    }

    // place pivot in its position and save its index
    int tmp = arr[first];
    arr[first] = arr[lastS1];
    arr[lastS1] = tmp;
    pivotIndex = lastS1;
    moveCount += 3; // increment moveCount by 3 for the swap
}

/*
 * sorts the array using radix sort algorithm
 * @param arr array to be sorted
 * @param size size of arr
 */
void radixSort(int *arr, const int size) {
    // find the max item of arr which will determine the maximum number of digits
    int max = arr[0];
    for (int i = 0; i < size; i++)
        if (arr[i] > max)
            max = arr[i];

    // call the radixSortHelper function for all digits of the items of the array
    for (int pow = 1; (max / pow) > 0; pow *= 10)
        radixSortHelper(arr, size, pow);
}

/*
 * helper function for radixSort that groups the items according to the specified digit
 * @param arr array to be grouped
 * @param size size of arr
 */
void radixSortHelper(int *arr, int size, const int pow) {
    int groups[10][size]; // digit groups
    int counts[10] = {0}; // sizes of digit groups

    int d; // current digit of the item
    // for each item in arr, add the item to the proper digit
    // group and increase the size of that group in counts
    for (int i = 0; i < size; i++) {
        d = (arr[i] / pow) % 10;
        groups[d][counts[d]++] = arr[i];
    }

    // add the items in each group in order to arr
    int k = 0;
    for (int i = 0; i < 10; i++)
        for(int j = 0; j < counts[i]; j++)
            arr[k++] = groups[i][j];
}

/*
 * displays the contents of the given array
 * @param arr array to be displayed
 * @param size size of arr
 */
void displayArray(const int *arr, const int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << ", ";
}

/*
 * creates 4 dynamic arrays with random items
 * @param arr1 first array to be returned
 * @param arr2 second array to be returned
 * @param arr3 third array to be returned
 * @param arr4 fourth array to be returned
 * @param size size of the arrays
 */
void createRandomArrays(int *&arr1, int *&arr2, int *&arr3, int *&arr4, const int size) {
    arr1 = new int[size], arr2 = new int[size], arr3 = new int[size], arr4 = new int[size]; // create 4 dynamic arrays

    // initialize the arrays with the same random items
    for (int i = 0; i < size; i++) {
        arr1[i] = arr2[i] = arr3[i] = arr4[i] = rand() % 300000;
    }
}

/*
 * creates 4 dynamic arrays with ascending items
 * @param arr1 first array to be returned
 * @param arr2 second array to be returned
 * @param arr3 third array to be returned
 * @param arr4 fourth array to be returned
 * @param size size of the arrays
 */
void createAscendingArrays(int *&arr1, int *&arr2, int *&arr3, int *&arr4, const int size) {
    arr1 = new int[size], arr2 = new int[size], arr3 = new int[size], arr4 = new int[size]; // create 4 dynamic arrays

    // initialize the arrays with the same ascending items
    for (int i = 0; i < size; i++) {
        arr1[i] = arr2[i] = arr3[i] = arr4[i] = rand() % 10 + (10 * i); // increase the interval in each iteration
    }
}

/*
 * creates 4 dynamic arrays with descending items
 * @param arr1 first array to be returned
 * @param arr2 second array to be returned
 * @param arr3 third array to be returned
 * @param arr4 fourth array to be returned
 * @param size size of the arrays
 */
void createDescendingArrays(int *&arr1, int *&arr2, int *&arr3, int *&arr4, const int size) {
    arr1 = new int[size], arr2 = new int[size], arr3 = new int[size], arr4 = new int[size]; // create 4 dynamic arrays

    // initialize the arrays with the same descending items
    for (int i = 0; i < size; i++) {
        arr1[i] = arr2[i] = arr3[i] = arr4[i] = rand() % 10 + (10 * (size - i)); // decrease the interval in each iteration
    }
}

/*
 * calls each sorting algorithm for random, ascending and descending arrays created
 * with the array creation functions for sizes from 6000 to 30000 with 4000 intervals
 * does not use every returned array in the same loop as it would be impossible to
 * print each algorithm seperately that way, but this does not affect the experiment
 * since the rand function generates the same random values for the same intervals
 */
void performanceAnalysis() {
    cout << "Analysis of Selection Sort\n";
    cout << "Random Arrays:\n" << "Array Size\t" << "Elapsed Time\t" << "compCount\t" << "moveCount\n";
    for (int size = 6000; size <= 30000; size += 4000) {
        int *arr1, *arr2, *arr3, *arr4; // declare the arrays
        int compCount, moveCount; // declare compCount and moveCount

        createRandomArrays(arr1, arr2, arr3, arr4, size); // create and initialize random arrays

        // test the algorithm
        double duration;
        clock_t startTime = clock();
        selectionSort(arr1, size, compCount, moveCount);
        duration = 1000 * double(clock() - startTime) / CLOCKS_PER_SEC;
        cout << size << "\t\t" << duration << " ms\t\t" << compCount << "\t" << moveCount << endl; // print the results

        // delete the arrays
        delete [] arr1;
        delete [] arr2;
        delete [] arr3;
        delete [] arr4;
    }

    cout << "Ascending Arrays:\n" << "Array Size\t" << "Elapsed Time\t" << "compCount\t" << "moveCount\n";
    for (int size = 6000; size <= 30000; size += 4000) {
        int *arr1, *arr2, *arr3, *arr4; // declare the arrays
        int compCount, moveCount; // declare compCount and moveCount

        createAscendingArrays(arr1, arr2, arr3, arr4, size); // create and initialize ascending arrays

        // test the algorithm
        double duration;
        clock_t startTime = clock();
        selectionSort(arr1, size, compCount, moveCount);
        duration = 1000 * double(clock() - startTime) / CLOCKS_PER_SEC;

        cout << size << "\t\t" << duration << " ms\t\t" << compCount << "\t" << moveCount << endl; // print the results

        // delete the arrays
        delete [] arr1;
        delete [] arr2;
        delete [] arr3;
        delete [] arr4;
    }

    cout << "Descending Arrays:\n" << "Array Size\t" << "Elapsed Time\t" << "compCount\t" << "moveCount\n";
    for (int size = 6000; size <= 30000; size += 4000) {
        int *arr1, *arr2, *arr3, *arr4; // declare the arrays
        int compCount, moveCount; // declare compCount and moveCount

        createDescendingArrays(arr1, arr2, arr3, arr4, size); // create and initialize descending arrays

        // test the algorithm
        double duration;
        clock_t startTime = clock();
        selectionSort(arr1, size, compCount, moveCount);
        duration = 1000 * double(clock() - startTime) / CLOCKS_PER_SEC;

        cout << size << "\t\t" << duration << " ms\t\t" << compCount << "\t" << moveCount << endl; // print the results

        // delete the arrays
        delete [] arr1;
        delete [] arr2;
        delete [] arr3;
        delete [] arr4;
    }

    cout << "\nAnalysis of Merge Sort\n";
    cout << "Random Arrays:\n" << "Array Size\t" << "Elapsed Time\t" << "compCount\t" << "moveCount\n";
    for (int size = 6000; size <= 30000; size += 4000) {
        int *arr1, *arr2, *arr3, *arr4; // declare the arrays
        int compCount, moveCount; // declare compCount and moveCount

        createRandomArrays(arr1, arr2, arr3, arr4, size); // create and initialize random arrays

        // test the algorithm
        double duration;
        clock_t startTime = clock();
        mergeSort(arr1, size, compCount, moveCount);
        duration = 1000 * double(clock() - startTime) / CLOCKS_PER_SEC;
        cout << size << "\t\t" << duration << " ms\t\t" << compCount << "\t\t" << moveCount << endl; // print the results

        // delete the arrays
        delete [] arr1;
        delete [] arr2;
        delete [] arr3;
        delete [] arr4;
    }

    cout << "Ascending Arrays:\n" << "Array Size\t" << "Elapsed Time\t" << "compCount\t" << "moveCount\n";
    for (int size = 6000; size <= 30000; size += 4000) {
        int *arr1, *arr2, *arr3, *arr4; // declare the arrays
        int compCount, moveCount; // declare compCount and moveCount

        createAscendingArrays(arr1, arr2, arr3, arr4, size); // create and initialize ascending arrays

        // test the algorithm
        double duration;
        clock_t startTime = clock();
        mergeSort(arr1, size, compCount, moveCount);
        duration = 1000 * double(clock() - startTime) / CLOCKS_PER_SEC;

        cout << size << "\t\t" << duration << " ms\t\t" << compCount << "\t\t" << moveCount << endl; // print the results

        // delete the arrays
        delete [] arr1;
        delete [] arr2;
        delete [] arr3;
        delete [] arr4;
    }

    cout << "Descending Arrays:\n" << "Array Size\t" << "Elapsed Time\t" << "compCount\t" << "moveCount\n";
    for (int size = 6000; size <= 30000; size += 4000) {
        int *arr1, *arr2, *arr3, *arr4; // declare the arrays
        int compCount, moveCount; // declare compCount and moveCount

        createDescendingArrays(arr1, arr2, arr3, arr4, size); // create and initialize descending arrays

        // test the algorithm
        double duration;
        clock_t startTime = clock();
        mergeSort(arr1, size, compCount, moveCount);
        duration = 1000 * double(clock() - startTime) / CLOCKS_PER_SEC;

        cout << size << "\t\t" << duration << " ms\t\t" << compCount << "\t\t" << moveCount << endl; // print the results

        // delete the arrays
        delete [] arr1;
        delete [] arr2;
        delete [] arr3;
        delete [] arr4;
    }

    cout << "\nAnalysis of Quick Sort\n";
    cout << "Random Arrays:\n" << "Array Size\t" << "Elapsed Time\t" << "compCount\t" << "moveCount\n";
    for (int size = 6000; size <= 30000; size += 4000) {
        int *arr1, *arr2, *arr3, *arr4; // declare the arrays
        int compCount, moveCount; // declare compCount and moveCount

        createRandomArrays(arr1, arr2, arr3, arr4, size); // create and initialize random arrays

        // test the algorithm
        double duration;
        clock_t startTime = clock();
        quickSort(arr1, size, compCount, moveCount);
        duration = 1000 * double(clock() - startTime) / CLOCKS_PER_SEC;
        cout << size << "\t\t" << duration << " ms\t\t" << compCount << "\t\t" << moveCount << endl; // print the results

        // delete the arrays
        delete [] arr1;
        delete [] arr2;
        delete [] arr3;
        delete [] arr4;
    }

    cout << "Ascending Arrays:\n" << "Array Size\t" << "Elapsed Time\t" << "compCount\t" << "moveCount\n";
    for (int size = 6000; size <= 30000; size += 4000) {
        int *arr1, *arr2, *arr3, *arr4; // declare the arrays
        int compCount, moveCount; // declare compCount and moveCount

        createAscendingArrays(arr1, arr2, arr3, arr4, size); // create and initialize ascending arrays

        // test the algorithm
        double duration;
        clock_t startTime = clock();
        quickSort(arr1, size, compCount, moveCount);
        duration = 1000 * double(clock() - startTime) / CLOCKS_PER_SEC;

        cout << size << "\t\t" << duration << " ms\t\t" << compCount << "\t" << moveCount << endl; // print the results

        // delete the arrays
        delete [] arr1;
        delete [] arr2;
        delete [] arr3;
        delete [] arr4;
    }

    cout << "Descending Arrays:\n" << "Array Size\t" << "Elapsed Time\t" << "compCount\t" << "moveCount\n";
    for (int size = 6000; size <= 30000; size += 4000) {
        int *arr1, *arr2, *arr3, *arr4; // declare the arrays
        int compCount, moveCount; // declare compCount and moveCount

        createDescendingArrays(arr1, arr2, arr3, arr4, size); // create and initialize descending arrays

        // test the algorithm
        double duration;
        clock_t startTime = clock();
        quickSort(arr1, size, compCount, moveCount);
        duration = 1000 * double(clock() - startTime) / CLOCKS_PER_SEC;

        cout << size << "\t\t" << duration << " ms\t\t" << compCount << "\t" << moveCount << endl; // print the results

        // delete the arrays
        delete [] arr1;
        delete [] arr2;
        delete [] arr3;
        delete [] arr4;
    }

    cout << "\nAnalysis of Radix Sort\n";
    cout << "Random Arrays:\n" << "Array Size\t" << "Elapsed Time\n";
    for (int size = 6000; size <= 30000; size += 4000) {
        int *arr1, *arr2, *arr3, *arr4; // declare the arrays

        createRandomArrays(arr1, arr2, arr3, arr4, size); // create and initialize random arrays

        // test the algorithm
        double duration;
        clock_t startTime = clock();
        radixSort(arr1, size);
        duration = 1000 * double(clock() - startTime) / CLOCKS_PER_SEC;

        cout << size << "\t\t" << duration << " ms\t\t\n"; // print the results

        // delete the arrays
        delete [] arr1;
        delete [] arr2;
        delete [] arr3;
        delete [] arr4;
    }

    cout << "Ascending Arrays:\n" << "Array Size\t" << "Elapsed Time\n";
    for (int size = 6000; size <= 30000; size += 4000) {
        int *arr1, *arr2, *arr3, *arr4; // declare the arrays

        createAscendingArrays(arr1, arr2, arr3, arr4, size); // create and initialize ascending arrays

        // test the algorithm
        double duration;
        clock_t startTime = clock();
        radixSort(arr1, size);
        duration = 1000 * double(clock() - startTime) / CLOCKS_PER_SEC;

        cout << size << "\t\t" << duration << " ms\t\t\n"; // print the results

        // delete the arrays
        delete [] arr1;
        delete [] arr2;
        delete [] arr3;
        delete [] arr4;
    }

    cout << "Descending Arrays:\n" << "Array Size\t" << "Elapsed Time\n";
    for (int size = 6000; size <= 30000; size += 4000) {
        int *arr1, *arr2, *arr3, *arr4; // declare the arrays

        createDescendingArrays(arr1, arr2, arr3, arr4, size); // create and initialize descending arrays

        // test the algorithm
        double duration;
        clock_t startTime = clock();
        radixSort(arr1, size);
        duration = 1000 * double(clock() - startTime) / CLOCKS_PER_SEC;

        cout << size << "\t\t" << duration << " ms\t\t\n"; // print the results

        // delete the arrays
        delete [] arr1;
        delete [] arr2;
        delete [] arr3;
        delete [] arr4;
    }
}