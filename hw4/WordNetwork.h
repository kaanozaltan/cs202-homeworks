/**
 * Title : Balanced Search Trees , Hashing and Graphs
 * Author : Cemhan Kaan Özaltan
 * ID: 21902695
 * Section : 3
 * Assignment : 4
 * Description : WordNetwork class interface
 */

#ifndef WORDNETWORK_H
#define WORDNETWORK_H
#include <iostream>
#include "HashTable.h"
#include "Queue.h"
using namespace std;

class WordNetwork {
    public:
        WordNetwork(const string vertexFile, const string edgeFile);
        ~WordNetwork();

        void listNeighbors(const string word);
        void listNeighbors(const string word, const int distance);
        void listConnectedComponents();
        void findShortestPath(const string word1, const string word2);

    private:
        void listNeighborsHelper(const LinkedList<string>& adjWords, int distance, int* visited, int* prev, LinkedList<string>& result);
        void conCompHelper(const LinkedList<string>& adjWords, int* visited);

        static const int WORD_COUNT = 5757; // graph's word count
        static const int EDGE_COUNT = 14135;    // graph's edge count
        string words[WORD_COUNT];   // array to translate indices to words
        int** adjMat;   // adjacency matrix to keep track of connections
        HashTable hashTable;    // hash table to find indices efficiently
};

#endif