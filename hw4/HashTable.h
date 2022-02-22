/**
 * Title : Balanced Search Trees , Hashing and Graphs
 * Author : Cemhan Kaan Özaltan
 * ID: 21902695
 * Section : 3
 * Assignment : 4
 * Description : HashTable class interface
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "LinkedList.h"
using namespace std;

class HashTable {
    public:
        HashTable();

        void add(Word word);
        int getIndex(string word);

    private:
        static int hash(const string& key, int tableSize);
        
        static const int TABLE_SIZE = 5000; // table size (number of buckets)
        LinkedList<Word> hashTable[TABLE_SIZE]; // hash table with seperate chaining as a linked list array
};

#endif