/*
 * Title: Binary Search Trees
 * Author: Cemhan Kaan Özaltan
 * ID: 21902695
 * Section: 3
 * Assignment: 2
 * Description: Implementation of BinarySearchTree class
 */

#include "BinarySearchTree.h"
using namespace std;

/*
 * default constructor for BinarySearchTree which sets root to NULL
 */
BinarySearchTree::BinarySearchTree(): root(NULL) {}

/*
 * destructor for BinarySearchTree which calls the desroy function with the root
 */
BinarySearchTree::~BinarySearchTree() {
	destroyTree(root);
}

/*
 * destroyTree function used by the destructor which recursively deletes 
 * left and right subtrees and then the root
 * @param treePtr root of current subtree
 */
void BinarySearchTree::destroyTree(BinaryNode*& treePtr) {
    // base case reached if treePtr is NULL
    if (treePtr != NULL) {
        // destroy left and right subtrees
		destroyTree(treePtr->leftChildPtr);
		destroyTree(treePtr->rightChildPtr);

        // delete the current root
		delete treePtr;
		treePtr = NULL;
	}
}

/*
 * tells whether the BST is empty
 * @return whether the BST is empty
 */
bool BinarySearchTree::isEmpty() const {
    return root == NULL;
}

/*
 * calculates the height of the BST by passing
 * the root to the height function
 * @return height of the tree
 */
int BinarySearchTree::getHeight() {
    return height(root);
}

/*
 * helper function for getHeight which calculates the height of the BST
 * by calculating the heights of left and right subtrees recursively
 * and finding their max
 * @return height of the tree
 */
int BinarySearchTree::height(BinaryNode*& treePtr) {
    // base case reached if treePtr is NULL
    if (treePtr == NULL)
        return 0;
    else {
        // find the heights of left and right subtrees
        int leftHeight = height(treePtr->leftChildPtr);
        int rightHeight = height(treePtr->rightChildPtr);

        // find whether the left or the right subtree is higher,
        // add 1 for the current node in both cases
        if (leftHeight > rightHeight)
            return leftHeight + 1;
        else
            return rightHeight + 1;
    }
}

/*
 * gives the number of nodes in the BST by using a helper function
 * @return number of nodes
 */
int BinarySearchTree::getNumberOfNodes() {
    int result = 0;
    getNodeNo(root, result);
    return result;
}

/*
 * helper function for getNumberOfNodes which finds the node number 
 * with recursion and returns it using pass by reference
 * @param treePtr root of current subtree
 * @param result node number to be returned
 */
void BinarySearchTree::getNodeNo(BinaryNode* treePtr, int& result) {
    if (treePtr != NULL) {
        result++;
        getNodeNo(treePtr->leftChildPtr, result);
        getNodeNo(treePtr->rightChildPtr, result);
    }
}

/*
 * adds the given entry to the BST by using a helper function, 
 * does not add if item already exists
 * @param newEntry entry to add
 * @return whether the operation was successful
 */
bool BinarySearchTree::add(const int newEntry) {
    return insertItem(root, newEntry);
}

/*
 * helper function for add which adds the given entry recursively
 * @param treePtr root of current subtree
 * @param newItem item to be added
 * @return whether the operation was succesful
 */
bool BinarySearchTree::insertItem(BinaryNode*& treePtr, const int newItem) {
    // insert location found if treePtr is NULL
    if (treePtr == NULL) {
        treePtr = new BinaryNode(newItem, NULL, NULL);
        
        // if still NULL after insertion, operation failed
        if (treePtr == NULL)
            return false;
        
        // else, operation successful
        return true;
    } else if (newItem == treePtr->item) // do not insert if item already exists
        return false; 
    else if (newItem < treePtr->item)
        insertItem(treePtr->leftChildPtr, newItem); // recursive call for left subtree
    else
        insertItem(treePtr->rightChildPtr, newItem); // recursive call for right subtree
}

/*
 * removes the given entry by using a helper function
 * @param anEntry entry to be removed
 * @return whether the operation was succesful
 */
bool BinarySearchTree::remove(const int anEntry) {
    return deleteItem(root, anEntry);
}

/*
 * helper function for remove which removes the given entry recursively
 * @param treePtr root of current subtree
 * @param item item to be removed
 * @return whether the operation was succesful
 */
bool BinarySearchTree::deleteItem(BinaryNode*& treePtr, int item) {
    if (treePtr == NULL) // item not found or cannot delete from an empty tree
        return false;
	else if (item == treePtr->item) { // delete location found
		deleteNodeItem(treePtr);
        return true;
    }
	else if (item < treePtr->item)
		deleteItem(treePtr->leftChildPtr, item); // recursive call for left subtree
	else
		deleteItem(treePtr->rightChildPtr, item); // recursive call for right subtree
}

/*
 * helper function for deleteItem which deletes a specified node
 * @param nodePtr node to be deleted
 */
void BinarySearchTree::deleteNodeItem(BinaryNode*& nodePtr) {
    BinaryNode* delPtr; // will be used for single child cases
	int replacementItem; // will be used for 2 child case

	if ((nodePtr->leftChildPtr == NULL) && (nodePtr->rightChildPtr == NULL)) { // check whether the given node is a leaf
		delete nodePtr;
		nodePtr = NULL;
	} else if (nodePtr->leftChildPtr == NULL){ // check for no left child
		delPtr = nodePtr;
		nodePtr = nodePtr->rightChildPtr;
		delPtr->rightChildPtr = NULL; 
		delete delPtr;
	} else if (nodePtr->rightChildPtr == NULL) { // check for no right child
		delPtr = nodePtr;
        nodePtr = nodePtr->leftChildPtr;
        delPtr->leftChildPtr = NULL;
        delete delPtr; 
	} else { // two children case, retrieve and delete the inorder successor
		processLeftmost(nodePtr->rightChildPtr, replacementItem);
		nodePtr->item = replacementItem;
	}
}

/*
 * helper function for deleteNodeItem which is used in 2 child case,
 * makes the necessary pointer moves and retrieves the inorder
 * successor using pass by reference which will replace the deleted item
 * @param nodePtr node to be deleted
 * @param item inorder successor to be retrieved
 */
void BinarySearchTree::processLeftmost(BinaryNode*& nodePtr, int& item) {
    // successor reached if no left child
	if (nodePtr->leftChildPtr == NULL) {
		item = nodePtr->item;
		BinaryNode* delPtr = nodePtr;
		nodePtr = nodePtr->rightChildPtr;
		delPtr->rightChildPtr = NULL;
		delete delPtr;
	} else
		processLeftmost(nodePtr->leftChildPtr, item); // if successor not reached, move to left child
}

/*
 * tells whether the bst contains the given entry
 * @param anEntry entry to be checked
 * @return whether the bst contains the entry
 */
bool BinarySearchTree::contains(const int anEntry) {
    return checkContains(root, anEntry);
}

/*
 * helper function for contains which checks the current root's
 * item and recursively checks the left and right subtrees if
 * item not found
 * @param treePtr root of current subtree
 * @param anEntry entry to be checked
 * @return whether the BST contains the entry
 */
bool BinarySearchTree::checkContains(BinaryNode* treePtr, const int anEntry) {
    // base case reached if treePtr is NULL
    if (treePtr == NULL)
        return false;
    else if (treePtr->item == anEntry)
        return true;
    else if (treePtr->item < anEntry)
        checkContains(treePtr->leftChildPtr, anEntry); // recursive call for left child
    else
        checkContains(treePtr->rightChildPtr, anEntry); // recursive call for right child
}

/*
 * traverses and prints the BST in preorder using a helper function
 */
void BinarySearchTree::preorderTraverse() {
    preorder(root);
}

/*
 * helper function for preorderTraverse which recursively
 * traverses and prints the BST in preorder
 * @param treePtr root of current subtree
 */
void BinarySearchTree::preorder(BinaryNode* treePtr) {
    if (treePtr != NULL) {
		cout << treePtr->item << ", ";
		preorder(treePtr->leftChildPtr);
		preorder(treePtr->rightChildPtr);
	}
}

/*
 * traverses and prints the BST in inorder using a helper function
 */
void BinarySearchTree::inorderTraverse() {
    inorder(root);
}

/*
 * helper function for inorderTraverse which recursively
 * traverses and prints the BST in inorder
 * @param treePtr root of current subtree
 */
void BinarySearchTree::inorder(BinaryNode* treePtr) {
    if (treePtr != NULL) {
		inorder(treePtr->leftChildPtr);
		cout << treePtr->item << ", ";
		inorder(treePtr->rightChildPtr);
	}
}

/*
 * traverses and prints the BST in postorder using a helper function
 */
void BinarySearchTree::postorderTraverse() {
    postorder(root);
}

/*
 * helper function for postorderTraverse which recursively
 * traverses and prints the BST in postorder
 * @param treePtr root of current subtree
 */
void BinarySearchTree::postorder(BinaryNode* treePtr) {
    if (treePtr != NULL) {
		postorder(treePtr->leftChildPtr);
		postorder(treePtr->rightChildPtr);
		cout << treePtr->item << ", ";
	}
}

/*
 * traverses and prints the BST in levelorder using a helper function
 */
void BinarySearchTree::levelorderTraverse() {
    levelTraverse(root);
}

/*
 * helper function for levelorderTraverse which iteratively traverses the 
 * levels of the BST and prints the items using a helper function
 * @param treePtr root of BST
 */
void BinarySearchTree::levelTraverse(BinaryNode* treePtr) {
    int h = height(root);

    // call levelDisplay for each level
    for (int level = 1; level <= h; level++)
        levelDisplay(treePtr, level);
}

/*
 * helper function for levelTraverse which recursively prints a specific
 * level by making recursive calls with decremented lengths
 * @param treePtr root of BST
 */
void BinarySearchTree::levelDisplay(BinaryNode* treePtr, const int level) {
    if (treePtr != NULL) {
        if (level == 1)
            cout << treePtr->item << ", ";
        else {
            levelDisplay(treePtr->leftChildPtr, level - 1);
            levelDisplay(treePtr->rightChildPtr, level - 1);
        }
    }
}

/*
 * finds the number of items that are >= a and <= b in the BST by
 * using a helper function
 * @param a inclusive lower bound
 * @param b inclusive upper bound
 * @return number of items in the given span
 */
int BinarySearchTree::span(const int a, const int b) {
    int result = 0;
    spanTree(root, a, b, result);
    return result;
}

/*
 * helper function for span which recursively counts the number
 * of items in the given span and returns it using pass by reference
 * items which are not in the span are not traversed
 * @param treePtr root of current subtree
 * @param a inclusive lower bound
 * @param b inclusive upper bound
 * @param result result to be returned
 */
void BinarySearchTree::spanTree(BinaryNode* treePtr, const int a, const int b, int& result) {
    if (treePtr != NULL) {
        if ((treePtr->item >= a) && (treePtr->item <= b)) // check whether the item is in the span
            result++;
        if (treePtr->item >= a) // check whether it is necessary to traverse the left subtree
            spanTree(treePtr->leftChildPtr, a, b, result); // recursive call for left subtree
        if (treePtr->item <= b) // check whether it is necessary to traverse the right subtree
            spanTree(treePtr->rightChildPtr, a, b, result); // recursive call for right subtree
    }
}

/*
 * mirrors the tree using a helper function
 */
void BinarySearchTree::mirror() {
    mirrorTree(root);
}

/*
 * helper function for mirror which recursively mirrors the tree by changing
 * the left and right child pointers of every node
 * @param treePtr root of current subtree
 */
void BinarySearchTree::mirrorTree(BinaryNode* treePtr) {
    // base case is when the given treePtr is null
    if (treePtr != NULL) {
        // swap the left and right child pointers
        BinaryNode* tmpPtr = treePtr->leftChildPtr;
        treePtr->leftChildPtr = treePtr->rightChildPtr;
        treePtr->rightChildPtr = tmpPtr;
        tmpPtr = NULL;
        delete tmpPtr;

        // call the mirrorTree function for the left and right subtrees
        mirrorTree(treePtr->leftChildPtr);
        mirrorTree(treePtr->rightChildPtr);
    }
}