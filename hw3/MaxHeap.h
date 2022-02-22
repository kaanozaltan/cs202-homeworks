/*
 * Title: Heaps
 * Author: Cemhan Kaan Özaltan
 * ID: 21902695
 * Section: 3
 * Assignment: 3
 * Description: MaxHeap class interface
 */

#ifndef MAXHEAP_H
#define MAXHEAP_H
#include "PrintRequest.h"
using namespace std;

class MaxHeap {
    public:
        MaxHeap();

        bool heapIsEmpty() const;
        void heapInsert(const PrintRequest& newItem);
        void heapDelete(PrintRequest& rootItem);

    protected:
        void heapRebuild(int root);

    private:
        static const int MAX_HEAP = 2000; // max size of item array
        PrintRequest items[MAX_HEAP]; // array of heap items
        int size; // number of heap items
};

#endif