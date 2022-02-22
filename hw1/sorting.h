/*
 * Title: Sorting and Algorithm Efficiency
 * Author: Cemhan Kaan Özaltan
 * ID: 21902695
 * Section: 3
 * Assignment: 1
 * Description: The prototypes of the sorting algorithms, helper functions and
 * additional functions are included in this file
 */

using namespace std;

// sorting functions
void selectionSort(int *arr, const int size, int &compCount, int &moveCount);
void mergeSort(int *arr, const int size, int &compCount, int &moveCount);
void quickSort(int *arr, const int size, int &compCount, int &moveCount);
void radixSort(int *arr, const int size);

// helper functions
void mergeSortHelper(int *arr, const int size, const int first, const int last, int &compCount, int &moveCount);
void merge(int *arr, const int size, const int first, const int mid, const int last, int &compCount, int &moveCount);
void quickSortHelper(int *arr, const int first, const int last, int &compCount, int &moveCount);
void partition(int *arr, const int first, const int last, int& pivotIndex, int &compCount, int &moveCount);
void radixSortHelper(int *arr, const int size, const int pow);

// additional functions
void displayArray(const int *arr, const int size);
void createRandomArrays(int *&arr1, int *&arr2, int *&arr3, int *&arr4, const int size);
void createAscendingArrays(int *&arr1, int *&arr2, int *&arr3, int *&arr4, const int size);
void createDescendingArrays(int *&arr1, int *&arr2, int *&arr3, int *&arr4, const int size);
void performanceAnalysis();