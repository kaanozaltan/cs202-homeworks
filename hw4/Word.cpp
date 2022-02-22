/**
 * Title : Balanced Search Trees , Hashing and Graphs
 * Author : Cemhan Kaan Özaltan
 * ID: 21902695
 * Section : 3
 * Assignment : 4
 * Description : Word class implementation
 */

#include "Word.h"
using namespace std;

/*
 * default constructor
 */
Word::Word() {
    word = "invalid";
    index = -1;
}

/*
 * creates a Word object with given inputs
 * @param word word stored in Word object
 * @param index index of word
 */
Word::Word(string word, int index) {
    this->word = word;
    this->index = index;
}

/*
 * returns word
 * @return word
 */
string Word::getWord() {
    return word;
}

/*
 * returns index
 * @return index
 */
int Word::getIndex() {
    return index;
}