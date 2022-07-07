#include <iostream>
#include <string>
#include <fstream>
#include "dictionary.h"

using namespace std;

WordMean::WordMean(string w, string m): word(w), meaning(m) {}

string WordMean::getWord() const {
    return word;
}

string WordMean::getMeaning() const {
    return meaning;
}

void WordMean::setMeaning(string m) {
    meaning = m;
}

void WordMean::setWord(string w) {
    word = w;
}

BST<WordMean> Dictionary::getWords() const {
	return words;
}

// ---------------------------------------------

//TODO
void Dictionary::readFile(ifstream &f) {
}

//TODO
string Dictionary::consult(string word1, WordMean& previous, WordMean& next) const {
    return "";
}

//TODO
bool Dictionary::update(string word1, string mean1) {
    return true;
}

//TODO
void Dictionary::print() const {
}
