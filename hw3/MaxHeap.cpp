/*
 * Title: Heaps
 * Author: Cemhan Kaan Özaltan
 * ID: 21902695
 * Section: 3
 * Assignment: 3
 * Description: MaxHeap class implementation
 */

#include <iostream>
#include "MaxHeap.h"
using namespace std;

/*
 * default constructor for MaxHeap
 */
MaxHeap::MaxHeap(): size(0) {

}

/*
 * checks whether heap is empty
 * @return whether heap is empty
 */
bool MaxHeap::heapIsEmpty() const {
    return size == 0;
}

/*
 * inserts a request to heap 
 * note: in the case of equal priorities, the request with earlier arrival order must be processed. this 
 * is done by comparing the arrival order values of the nodes if priorities are equal in both heapInsert 
 * and heapRebuild. by doing this in both insertion and rebuilding after deletion, we ensure that the 
 * request with the highest priority and earliest arrival order remains on top of the heap to be deleted 
 * and retrieved. arrival orders are compared instead of request times since it is assumed that the input 
 * file will be in arrival order and if request times are compared, requests with equal priorities sent 
 * at the same minute may get processed out of order
 * @param newItem request to insert
 */
void MaxHeap::heapInsert(const PrintRequest& newItem) {
    if (size >= MAX_HEAP)
		cout << "Heap full\n";

	// put the new request at the end of items array
	items[size] = newItem;

	// trickle new request up to its proper position
	int place = size;
	int parent = (place - 1) / 2;
	// while place is not root and place's priority is larger than parent's priority or place's 
	// priority is equal to parent's priority and place has earlier arrival order, swap place and parent
	while ((place > 0) && ((items[place].getPriority() > items[parent].getPriority()) || ((items[place].getPriority() == items[parent].getPriority()) &&
			(items[place].getArrivalOrder() < items[parent].getArrivalOrder())))) {
		PrintRequest tmp = items[parent];
		items[parent] = items[place];
		items[place] = tmp;

		place = parent;
		parent = (place - 1) / 2;
	}
 	size++;
}

/*
 * deletes the print request with highest priority and returns it with pass by reference
 * @param rootItem print request at the root
 */
void MaxHeap::heapDelete(PrintRequest& rootItem) {
    if (heapIsEmpty())
        cout << "Heap empty\n";
	else {
		// swap the root request with the last one, decrement size and rebuild heap
		rootItem = items[0];
		items[0] = items[size - 1];
		size--;
		heapRebuild(0);
	}
}

/*
 * recursively restores the heap structure after deletion
 * @param root index of current heap's root
 */
void MaxHeap::heapRebuild(int root) {
    int child = 2 * root + 1; // index of root's left child if it has one

	if (child < size) { // root is not a leaf so that it has a left child
		int rightChild = child + 1; // index of root's left child if it has one

		// if root has right child, find the one with highest priority or if children priorities equal, find the one with earlier arrival order
		if ((rightChild < size) && ((items[rightChild].getPriority() > items[child].getPriority()) || ((items[rightChild].getPriority() == items[child].getPriority())
			&& (items[rightChild].getArrivalOrder() < items[child].getArrivalOrder()))))
			child = rightChild; // index of larger child

		// if root’s item has smaller priority than the chosen child or if root's priority is equal with 
		// the chosen child and the child has earlier arrival order, swap values
		if ((items[root].getPriority() < items[child].getPriority()) || ((items[root].getPriority() == items[child].getPriority())
			&& (items[root].getArrivalOrder() > items[child].getArrivalOrder()))) {
			PrintRequest tmp;
			tmp = items[root];
			items[root] = items[child];
			items[child] = tmp;

			// transform the new subtree into a heap
			heapRebuild(child);
		}
    }
}