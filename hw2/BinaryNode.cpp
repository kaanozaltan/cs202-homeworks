/*
 * Title: Binary Search Trees
 * Author: Cemhan Kaan Özaltan
 * ID: 21902695
 * Section: 3
 * Assignment: 2
 * Description: Implementation of BinaryNode class
 */

#include "BinaryNode.h"
using namespace std;

/*
 * default constructor for BinaryNode class
 */
BinaryNode::BinaryNode() {}

/*
 * constructor for BinaryNode class
 */
BinaryNode::BinaryNode(const int nodeItem, BinaryNode* left, BinaryNode* right)
            : item(nodeItem), leftChildPtr(left), rightChildPtr(right) {}

/*
 * getter for item
 * @return item of the node
 */
int BinaryNode::getItem() {
    return item;
}

/*
 * setter for item
 * @param item item to set
 */
void BinaryNode::setItem(const int item) {
    this->item = item;
}

/*
 * getter for leftChildPtr
 * @return leftChildPtr of the node
 */
BinaryNode* BinaryNode::getLeftChildPtr() {
    return leftChildPtr;
}

/*
 * setter for leftChildPtr
 * @param left leftChildPtr to set
 */
void BinaryNode::setLeftChildPtr(BinaryNode* left) {
    leftChildPtr = left;
}

/*
 * getter for rightChildPtr
 * @return rightChildPtr of the node
 */
BinaryNode* BinaryNode::getRightChildPtr() {
    return rightChildPtr;
}

/*
 * setter for rightChildPtr
 * @param right rightChildPtr to set
 */
void BinaryNode::setRightChildPtr(BinaryNode* right) {
    rightChildPtr = right;
}