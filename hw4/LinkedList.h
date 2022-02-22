/**
 * Title : Balanced Search Trees , Hashing and Graphs
 * Author : Cemhan Kaan Özaltan
 * ID: 21902695
 * Section : 3
 * Assignment : 4
 * Description : LinkedList class interface
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Word.h"
using namespace std;

template<class T>
class LinkedList {
    public:
        LinkedList();
        ~LinkedList();
        
        void add(T data);
        void remove(int index);
        T get(int index) const;
        int getSize() const;
        bool isEmpty() const;

    private:
        struct Node {
            T item;
            Node* next;
        };

        Node* find(int index) const;

        Node *head, *tail; // linked list's head and tail pointers
        int size;   // linked list's size
};

#endif