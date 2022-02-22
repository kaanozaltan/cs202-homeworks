/*
 * Title: Binary Search Trees
 * Author: Cemhan Kaan Özaltan
 * ID: 21902695
 * Section: 3
 * Assignment: 2
 * Description: Interface of BinaryNode class
 */

#ifndef BINARYNODE_H
#define BINARYNODE_H
#include <iostream>
using namespace std;

class BinaryNode {
    public:
        int getItem();
        void setItem(const int item);
        BinaryNode* getLeftChildPtr();
        void setLeftChildPtr(BinaryNode* left);
        BinaryNode* getRightChildPtr();
        void setRightChildPtr(BinaryNode* right);

    private:
        BinaryNode();
        BinaryNode(const int nodeItem, BinaryNode* left = NULL, BinaryNode* right = NULL);

        int item; // contains the data
        BinaryNode* leftChildPtr; // left child pointer
        BinaryNode* rightChildPtr; // right child pointer

    friend class BinarySearchTree; // BinarySearchTree can access the private parts
};

#endif