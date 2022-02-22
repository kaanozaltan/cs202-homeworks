/**
 * Title : Balanced Search Trees , Hashing and Graphs
 * Author : Cemhan Kaan Özaltan
 * ID: 21902695
 * Section : 3
 * Assignment : 4
 * Description : Queue class implementation
 */

#include "Queue.h"
using namespace std;

/*
 * default constructor
 */
Queue::Queue() {

}

/*
 * enqueues given item
 * @param item item to enqueue
 */
void Queue::enqueue(string item) {
    q.add(item);
}

/*
 * dequeues an item
 * @return dequeued item
 */
string Queue::dequeue() {
    string item = q.get(1);
    q.remove(1);
    return item;  
}

/*
 * returns whether the queue is empty
 * @return whether the queue is empty
 */
bool Queue::isEmpty() {
    return q.isEmpty();
}