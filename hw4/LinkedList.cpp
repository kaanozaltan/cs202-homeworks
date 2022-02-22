/**
 * Title : Balanced Search Trees , Hashing and Graphs
 * Author : Cemhan Kaan Özaltan
 * ID: 21902695
 * Section : 3
 * Assignment : 4
 * Description : LinkedList class implementation
 */

#include "LinkedList.h"
#include <iostream>
using namespace std;

/*
 * default constructor
 */
template<class T>
LinkedList<T>::LinkedList() {
    size = 0;
    head = NULL;
    tail = NULL;
}

/*
 * removes all items in the linked list
 */
template<class T>
LinkedList<T>::~LinkedList() {
    while (size > 0)
        remove(1);
}

/*
 * adds given item to the linked list
 * @param data item to add
 */
template<class T>
void LinkedList<T>::add(T data) {
    // create new node and place item inside it
    Node* node = new Node;
    node->item = data;

    // if size is 0, apply special case, apply default case if else
    if (size == 0) {
        head = node;
        tail = head;
        tail->next = NULL;
    } else {
        tail->next = node;
        tail = tail->next;
        tail->next = NULL;
    }
    
    size++; // increment size
}

/*
 * removes item at specified index
 * @param index index of item to remove
 */
template<class T>
void LinkedList<T>::remove(int index) {
    Node* cur;

    // check whether index is valid
    if (index < 1 || index > size)
        cout << "Index out of bounds\n";

    // apply special case if index is 1, regular case if else
    if (index == 1) {
        cur = head;  
        head = head->next;
    } else {
        Node* prev = find(index - 1);
        cur = prev->next;
        prev->next = cur->next;
    }

    // remove item's pointer and decrement size
    cur->next = NULL;
    delete cur;
    cur = NULL;
    size--;
}

/*
 * returns item at specified index
 * @param index index of item to return
 * @return item at index
 */
template<class T>
T LinkedList<T>::get(int index) const {
    if ((index < 1) || (index > size))
        cout << "Index out of bounds\n";
    else
        return (find(index))->item;
}

/*
 * returns size
 * @return size
 */
template<class T>
int LinkedList<T>::getSize() const {
    return size;
}

/*
 * returns whether the linked list is empty
 * @return whether the linked list is empty
 */
template<class T>
bool LinkedList<T>::isEmpty() const {
    return size == 0;
}

/*
 * returns a pointer to node at index, returns NULL if index is invalid
 * @param index index of node to return pointer of
 * @return pointer to node
 */
template<class T>
class LinkedList<T>::Node* LinkedList<T>::find(int index) const {
    // check whether index is valid
    if ((index < 1) || (index > size))
        return NULL;   
    else {
        // traverse the linked list until index and return that pointer
        Node* cur = head;
        for (int i = 1; i < index; i++)
        cur = cur->next;
        return cur;
    }
}

// LinkedList is a template class which can be used for the following types
template class LinkedList<Word>;
template class LinkedList<string>;
template class LinkedList<int>;