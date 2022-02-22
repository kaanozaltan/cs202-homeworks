/**
 * Title : Balanced Search Trees , Hashing and Graphs
 * Author : Cemhan Kaan Özaltan
 * ID: 21902695
 * Section : 3
 * Assignment : 4
 * Description : Queue class interface
 */

#ifndef QUEUE_H
#define QUEUE_H
#include "LinkedList.h"
using namespace std;

class Queue {
    public:
        Queue();

        void enqueue(string item);
        string dequeue();
        bool isEmpty();

    private:
        LinkedList<string> q;   // linked list to represent queue
};

#endif
