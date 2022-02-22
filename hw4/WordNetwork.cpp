/**
 * Title : Balanced Search Trees , Hashing and Graphs
 * Author : Cemhan Kaan Özaltan
 * ID: 21902695
 * Section : 3
 * Assignment : 4
 * Description : WordNetwork class implementation
 */

#include <fstream>
#include <sstream>
#include "WordNetwork.h"
using namespace std;

/*
 * creates an adjacency matrix and a hash table using the given files
 * @param vertexFile vertex file name
 * @param edgeFile edge file name
 */
WordNetwork::WordNetwork(const string vertexFile, const string edgeFile) {
    // initialize adjMat dynamically since it is very large
    adjMat = new int*[WORD_COUNT];
    for (int i = 0; i < WORD_COUNT; i++)
        adjMat[i] = new int[WORD_COUNT];
    
    // all connections are initially 0
    for (int i = 0; i < WORD_COUNT; i++)
        for (int j = 0; j < WORD_COUNT; j++)
            adjMat[i][j] = 0;
    
    // open input files
    ifstream vertexF(vertexFile.c_str());
    ifstream edgeF(edgeFile.c_str());

    // initialize words and hashTable
    for (int i = 0; i < WORD_COUNT; i++) {
        getline(vertexF, words[i]);
        Word word(words[i], i);
        hashTable.add(word);
    }
    
    // initialize adjMat by marking connections 1
    string word1, word2;
    for (int i = 0; i < EDGE_COUNT; i++) {
        // read word pair from edgeF
        getline(edgeF, word1, ',');
        getline(edgeF, word2);
        
        // mark words adjacent symmetrically since this is an undirected graph
        adjMat[hashTable.getIndex(word1)][hashTable.getIndex(word2)] = 1;
        adjMat[hashTable.getIndex(word2)][hashTable.getIndex(word1)] = 1;
    }

    // close input files
    vertexF.close();
    edgeF.close();
}

/*
 * deallocates adjMat
 */
WordNetwork::~WordNetwork() {
    for (int i = 0; i < WORD_COUNT; i++)
        delete[] adjMat[i];
    delete[] adjMat;
}

/*
 * lists immediate neighbors of given word if it exists in the graph
 * @param word word to list neighbors of
 */
void WordNetwork::listNeighbors(const string word) {
    if (hashTable.getIndex(word) == -1) // check whether word exists in the graph
        cout << word << " does not exist in the graph\n";
    else {
        // print neighbors if there are any
        string neighbors = "";  // string to keep neighbors in
        for (int i = 0; i < WORD_COUNT; i++)
            if (adjMat[hashTable.getIndex(word)][i] == 1)
                neighbors += words[i] + "\n";
        if (neighbors == "")    // check whether word has no neighbors
            cout << word << " has no neighbors\n";
        else
            cout << "Neighbors of " << word << ":\n" << neighbors;  // print neighbors
    }

    cout << endl;
}

/*
 * lists neighbors of given word with a given distance if it exists in the graph using recursive BFT
 * note: distance must be greater than 0 since distance 0 means word itself which is not a 
 * neighbor and negative distance is not possible
 * @param word word to list the neighbors of
 * @param distance distance of neighbors
 */
void WordNetwork::listNeighbors(const string word, const int distance) {
    if (hashTable.getIndex(word) == -1) // check whether word exists in graph
        cout << word << " does not exist in the graph\n";
    else if (distance < 1)  // check whether distance is valid
        cout << "Invalid distance (must be greater than 0)\n";
    else {
        int visited[WORD_COUNT] = {0};  // to keep track of visited words
        LinkedList<string> level;   // level to pass to listHelper
        int prev[WORD_COUNT];   // to print the path to each word
        LinkedList<string> result;  // resulting neighbors

        // all prev's are initially -1
        for (int i = 0; i < WORD_COUNT; i++)
            prev[i] = -1;

        level.add(word);    // level initially only has word
        visited[hashTable.getIndex(word)] = 1;  // mark word visited

        listNeighborsHelper(level, distance, visited, prev, result);

        if (result.isEmpty())   // check whether word has any neighbors with given distance
            cout << word << " has no neighbors with distance " << distance << endl;
        else {
            cout << "Neighbors of " << word << " with distance " << distance << ":\n";

            // construct and print path for each word with given distance
            for (int i = 0; i < result.getSize(); i++) {
                LinkedList<int> path;

                // construct path using prev
                for (int cur = hashTable.getIndex(result.get(i + 1)); cur != -1; cur = prev[cur]) {
                    path.add(cur);
                }
                
                // print path from word to current word
                for (int j = path.getSize(); j > 0; j--) {
                    if (j == 1)
                        cout << words[path.get(j)] << endl;
                    else
                        cout << words[path.get(j)] << " -> ";
                }
            }
        }
    }

    cout << endl;
}

/*
 * list all connected components of the graph using recursive BFT
 */
void WordNetwork::listConnectedComponents() {
    int visited[WORD_COUNT] = {0};  // to keep track of visited words
    int cur = 0;  // current word's index in current component
    int compNo = 1;  // component no
    bool done = false;  // whether all components are printed

    while (!done) {
        LinkedList<string> level;   // level to pass to listHelper

        level.add(words[cur]);  // level initially only has current word
        cout << "Connected component " << compNo << ":\n";
        cout << words[cur] << endl;   // print current word
        visited[cur] = 1;   // mark current word visited
        
        conCompHelper(level, visited);  // call helper function

        // determine a word from next component and if all words visited, assign done true since all components printed
        for (int i = 0; i < WORD_COUNT; i++)
            if (visited[i] == 0) {
                cur = i;
                break;
            } else if (i == WORD_COUNT - 1)
                done = true;

        compNo++; // move on to next component
    }

    cout << endl;
}

/*
 * prints shortest path from a given word to another using iterative BFT
 * @param word1 word to start from
 * @param word2 target word
 */
void WordNetwork::findShortestPath(const string word1, const string word2) {
    if ((hashTable.getIndex(word1) == -1) || (hashTable.getIndex(word2) == -1))
        cout << "Invalid word input(s)\n";
    else {
        int visited[WORD_COUNT] = {0};  // to keep track of visited words
        Queue q;    // to print with BFT
        int prev[WORD_COUNT];   // stores previous index of each word to construct shortest path
        
        // all prev's are initially -1
        for (int i = 0; i < WORD_COUNT; i++)
            prev[i] = -1;

        // mark word1 visited and enqueue it
        visited[hashTable.getIndex(word1)] = 1;
        q.enqueue(word1);

        int curIndex;   // current word's index
        while (!q.isEmpty()) {
            // dequeue current word; enqueue, mark visited and set prev of its neighbors
            string cur = q.dequeue();
            curIndex = hashTable.getIndex(cur); // calculate here to prevent repetitive calculations
            for (int i = 0; i < WORD_COUNT; i++)
                if ((adjMat[curIndex][i] == 1) && (visited[i] != 1)) {
                    visited[i] = 1;
                    q.enqueue(words[i]);
                    prev[i] = curIndex; // mark neighbor's prev as cur's index
                }
        }

        // construct path in reverse using prev
        LinkedList<int> path;
        for (int cur = hashTable.getIndex(word2); cur != -1; cur = prev[cur])
            path.add(cur);

        // check whether word2 is connected to word1 and if so, print the path
        if (path.get(path.getSize()) != hashTable.getIndex(word1))
            cout << "There is no path from " << word1 << " to " << word2 << endl;
        else {
            cout << "Shortest path from " << word1 << " to " << word2 << ":\n";
            // print in reverse since path was constructed in reverse
            for (int i = path.getSize(); i > 0; i--)
                cout << words[path.get(i)] << endl;
        }
    }

    cout << endl;
}

/*
 * recursively finds neighbors of a given level with a given distance
 * @param level words to find neighbors of
 * @param distance distance of neighbors
 * @param visited array to keep track of visited words
 * @param prev array holding indices of previous nodes of words
 * @param result resulting neighbors to return with pass by reference
 */
void WordNetwork::listNeighborsHelper(const LinkedList<string>& level, int distance, int* visited, int* prev, LinkedList<string>& result) {
    if ((distance > 0) && !level.isEmpty()) {    // base case is when distance <= 0 or neighbors is empty
        LinkedList<string> neighbors;   // neighbors to make recursive call with
        int curIndex;   // current word's index
        // for every word in neighbors; add to neighbors, mark visited and set prev of its neighbors
        for (int i = 0; i < level.getSize(); i++) {
            curIndex = hashTable.getIndex(level.get(i + 1)); // calculate here to prevent repetitive calculations
            for (int j = 0; j < WORD_COUNT; j++) {
                // find word's neighbors
                if ((adjMat[curIndex][j] == 1) && (visited[j] != 1)) {
                    neighbors.add(words[j]);
                    visited[j] = 1;
                    prev[j] = curIndex;
                }
            }
        }

        listNeighborsHelper(neighbors, distance - 1, visited, prev, result);   // recursive call with decremented distance
    } else if (!level.isEmpty()) // base case reached, return items of level if it's not empty
        for (int i = 0; i < level.getSize(); i++)
            result.add(level.get(i + 1));
}

/*
 * recursively prints all neighbors of a given level
 * @param level level to print neighbors of
 * @param visited array to keep track of visited words
 */
void WordNetwork::conCompHelper(const LinkedList<string>& level, int* visited) {
    if (!level.isEmpty()) {    // base case is when neighbors is empty
        LinkedList<string> neighbors;   // neighbors to make recursive call with
        int curIndex;   // current word's index
        // for every word in neighbors, print, add to neighbors and mark visited its neighbors
        for (int i = 0; i < level.getSize(); i++) {
            curIndex = hashTable.getIndex(level.get(i + 1)); // calculate here to prevent repetitive calculations
            for (int j = 0; j < WORD_COUNT; j++) {
                // find word's neighbors
                if ((adjMat[curIndex][j] == 1) && (visited[j] != 1)) {
                    cout << words[j] << endl;
                    neighbors.add(words[j]);
                    visited[j] = 1;
                }
            }
        }

        conCompHelper(neighbors, visited);   // recursive call
    }
}