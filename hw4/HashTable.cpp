/**
 * Title : Balanced Search Trees , Hashing and Graphs
 * Author : Cemhan Kaan Özaltan
 * ID: 21902695
 * Section : 3
 * Assignment : 4
 * Description : HashTable class implementation
 */

#include <iostream>
#include "HashTable.h"
using namespace std;

/*
 * default constructor
 */
HashTable::HashTable() {

}

/*
 * adds given item
 * @param item item to add
 */
void HashTable::add(Word word) {
    hashTable[hash(word.getWord(), TABLE_SIZE)].add(word);  // add item to its hash value location
}

/*
 * gets index of given item
 * @param item item to find index of
 * @return index of item, -1 if item not found
 */
int HashTable::getIndex(string word) {
    // find item's hash value and search its bucket
    for (int i = 0; i < hashTable[hash(word, TABLE_SIZE)].getSize(); i++)
        if (hashTable[hash(word, TABLE_SIZE)].get(i + 1).getWord() == word)
            return hashTable[hash(word, TABLE_SIZE)].get(i + 1).getIndex();       
    return -1;
}

/*
 * hashes given item
 * @param key item to hash
 * @param tableSize table size
 * @return hash value
 */
int HashTable::hash(const string& key, int tableSize) {
    int hashVal = 0;
	
    for (int i = 0; i < key.length(); i++)
        hashVal = 37 * hashVal + key[i];
        
    hashVal %= tableSize;
    if (hashVal < 0)    // in case overflows occurs
        hashVal += tableSize;

    return hashVal;
}