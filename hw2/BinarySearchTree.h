/*
 * Title: Binary Search Trees
 * Author: Cemhan Kaan Özaltan
 * ID: 21902695
 * Section: 3
 * Assignment: 2
 * Description: Interface of BinarySearchTree class
 */

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include "BinaryNode.h"
using namespace std;

class BinarySearchTree {
    public:
        BinarySearchTree();
        ~BinarySearchTree();
        bool isEmpty() const;
        int getHeight();
        int getNumberOfNodes();
        bool add(const int newEntry);
        bool remove(const int anEntry);
        bool contains(const int anEntry);
        void preorderTraverse();
        void inorderTraverse();
        void postorderTraverse();
        void levelorderTraverse();
        int span(const int a, const int b);
        void mirror();

    protected:
        bool insertItem(BinaryNode*& treePtr, const int newItem);
        bool deleteItem(BinaryNode*& treePtr, int item);
        void deleteNodeItem(BinaryNode*& nodePtr);
        void processLeftmost(BinaryNode*& nodePtr, int& item);

    private:
        void destroyTree(BinaryNode*& treePtr);
        void getNodeNo(BinaryNode* treePtr, int& result);
        void preorder(BinaryNode* treePtr);
        void inorder(BinaryNode* treePtr);
        void postorder(BinaryNode* treePtr);
        bool checkContains(BinaryNode* treePtr, const int anEntry);
        int height(BinaryNode*& treePtr);
        void levelTraverse(BinaryNode* treePtr);
        void levelDisplay(BinaryNode* treePtr, const int level);
        void mirrorTree(BinaryNode* treePtr);
        void spanTree(BinaryNode* treePtr, const int a, const int b, int& result);

        BinaryNode* root;
};

#endif