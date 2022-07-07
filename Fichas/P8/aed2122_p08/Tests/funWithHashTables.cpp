// AED 2021/2022 - Aula Pratica 08
// Pedro Ribeiro (DCC/FCUP) [12/12/2021]

#include "funWithHashTables.h"
#include "hashTable.h"

#include <vector>
#include <iostream>
#include <cctype>

// Exemplo de função de hash para ints
unsigned FunWithHashTables::hashInt(const int& i) {
  return i;
}

// Exemplo de função de hash para strings
unsigned FunWithHashTables::hashString(const string& s) {
  hash<string> h;
  return h(s);
}

// ----------------------------------------------------------
// Exercicio 1: Tabelas de Dispersão
// ----------------------------------------------------------

// ..............................
// d) Contando diferentes somas de pares
// TODO
int FunWithHashTables::sumPairs(const vector<int>& numbers) {
    /*
  set<int> difSumsSet;
  for (unsigned int i = 0; i < numbers.size() - 1; i++) {
    for (unsigned int j = i + 1; j < numbers.size(); j++) {
      difSumsSet.insert(numbers[i] + numbers[j]);
    }
  }
  return difSumsSet.size();
     */

    int count = 0, size = numbers.size();
    HashTable<int> table(size, hashInt);
    for (unsigned int i = 0; i < numbers.size(); i++) {
        for (unsigned int j = i + 1; j < numbers.size(); j++) {
            if (table.getNumEmpty() == 1) {
                size *= 2;
                table.rehash(size);
            }
            int key = numbers[i] + numbers[j]; // Sum of the pair
            table.insert(key);
        }
    }
    return table.getNumActive();
}

// ----------------------------------------------------------
// Exercicio 2: Um padrão no DNA
// ----------------------------------------------------------
// TODO
int FunWithHashTables::dnaMotifs(string dna, int k, unordered_set<string>& motifs) {
    unordered_map<string, int> substrings;
    int maxFreq = substrings[0];

    for (unsigned int i = 0; i < dna.size() - k + 1; i++) {
        string subs = dna.substr(i,k); // substring da string "dna"
        if (substrings.find(subs) == substrings.end()) { // substring still doesn't exists
            substrings.insert({subs, 1}); // Insert the new substring
        }
        else {
            substrings.find(subs)->second++; // Adds an occurrence to the frequency of that specific substring
        }
    }
    for (auto p : substrings) {
        if (p.second > maxFreq) {
            motifs.clear();
            motifs.insert(p.first);
            maxFreq = p.second;
        }
        else if (p.second == maxFreq) {
            motifs.insert(p.first);
        }
    }

    return maxFreq;
}

// ----------------------------------------------------------
// Exercicio 3: Torre de Babel
// ----------------------------------------------------------
// TODO
void FunWithHashTables::findLanguage(string text, const unordered_map<string, vector<string>>& dict, unordered_map<string, int>& answer) {
    vector<string> words; // words of the sentence text in lowercase
    string wLowercase; // variable to store a word of the string text

    for (unsigned int i = 0; i < text.length(); i++) {
        if (isalpha(text[i])) { // text[i] is alphabetic
            wLowercase += tolower(text[i]);
        }
        else if (text[i] == ' '){ // text[i] is not alphabetic
            words.push_back(wLowercase);
            wLowercase.clear();
        }
        if (i == text.length() - 1) words.push_back(wLowercase); // Adds the last word of text to the vector of words
    }
    for (auto p : dict) { // Goes through every pair of dict
        int wordsLang = 0;
        for (string word : p.second) { // Goes through every word of the language
            for (string w2 : words) { // Goes through every word of the text
                if (word == w2) {
                    wordsLang++;
                }
            }
        }
        answer.insert({p.first, wordsLang});
    }
}

// ----------------------------------------------------------
// Exercicio 4: Palavras Alienígenas
// ----------------------------------------------------------
// TODO
void FunWithHashTables::wordIndex(const vector<string> &words, vector<int>& answer) {
}
