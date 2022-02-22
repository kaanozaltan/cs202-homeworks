/**
 * Title : Balanced Search Trees , Hashing and Graphs
 * Author : Cemhan Kaan Özaltan
 * ID: 21902695
 * Section : 3
 * Assignment : 4
 * Description : Word class interface
 */

#ifndef WORD_H
#define WORD_H
#include <string>
using namespace std;

class Word {
    public:
        Word();
        Word(string word, int index);

        string getWord();
        int getIndex();

    private:
        string word;    // word stored in the object
        int index;  // stored word's index
};

#endif