#include "game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;


unsigned int Game::numberOfWords(string phrase) {
  if ( phrase.length() == 0 ) return 0;

  unsigned n=1;
  size_t pos = phrase.find(' ');
  while (pos != string::npos) {
    phrase = phrase.substr(pos+1);
    pos = phrase.find(' ');
    n++;
  }
  return n;
}

Game::Game() {
	this->kids.clear();
}

Game::Game(list<Kid>& l2) {
	this->kids = l2;
}

//-----------------------------------------------------------------

// TODO
/**
 * This function adds a child to the list of participants in the game.
 * @param k1 (Kid to add to the game)
 */
void Game::addKid(const Kid k1) {
    kids.push_back(k1);
}

// TODO
list<Kid> Game::getKids() const {
    return kids;
}

// TODO
void Game::setKids(const list<Kid>& l1) {
    for (Kid k : l1) kids.push_back(k);
}

// TODO
Kid Game::loseGame(string phrase) {
    const unsigned int words = numberOfWords(phrase);

    while (kids.size() > 1) {
        unsigned int n = kids.size() % words;
        while (n > 1) {
            Kid k = kids.front(); // First kid in the list
            kids.pop_front(); // Removes the first kid in the list
            kids.push_back(k); // Add the same kid to the end of the list
            n--;
        }
        kids.pop_front(); // Removes the kid that stayed in the front of the list (kid to remove)
    }
    return kids.front();
}

// TODO
list<Kid> Game::removeOlder(unsigned id) {
    list<Kid> ofAge;
    for(list<Kid>::iterator it = kids.begin(); it != kids.end(); ++it){
        if(it->getAge() > id) {
            ofAge.push_back(*it);
            it = kids.erase(it);
        }
    }
    return ofAge;
}

// TODO
queue<Kid> Game::rearrange() {
    queue<Kid> result;
    list<Kid> boys;
    list<Kid> girls;
    list<Kid>::const_iterator itB = boys.begin();
    list<Kid>::const_iterator itG = girls.begin();

    for (auto k : kids) {
        if (k.getSex() == 'm') boys.push_back(k);
        else girls.push_back(k);
    }

    unsigned int n = girls.size(),
                m = boys.size();

    kids.clear();
    if (n < m) {
        unsigned int i = girls.size();
        while (i > 0 && !girls.empty()) {
            unsigned int div = m/n; // Number of boys between two girls
            kids.push_back(girls.front());
            girls.pop_front();
            while (div > 0 && !boys.empty()) {
                kids.push_back(boys.front());
                boys.pop_front();
                div--;
            }
            i--;
        }
    }
    else {
        unsigned int i = boys.size();
        while (i > 0 && !boys.empty()) {
            unsigned int div = n/m; // Number of girls between two boys
            kids.push_back(boys.front());
            boys.pop_front();
            while (div > 0 && !girls.empty()) {
                kids.push_back(girls.front());
                girls.pop_front();
                div--;
            }
            i--;
        }
    }

    for (Kid b : boys) {
        result.push(b);
    }
    for (Kid g : girls) {
        result.push(g);
    }

    return result;
}

// TODO
bool Game::operator==(Game& g2) {
    if (kids.size() != g2.getKids().size()) return false;
    list<Kid>::iterator it1 = kids.begin();
    list<Kid>::iterator it2 = g2.getKids().begin();

    while (it1 != kids.end()) {
        if ((*it1).getAge() != (*it2).getAge() || (*it1).getSex() != (*it2).getSex() || (*it1).getName() != (*it2).getName())
            return false;
        ++it1;
        ++it2;
    }

	return true;
}

// TODO
list<Kid> Game::shuffle() const {
	list<Kid> shuffledKids;
    list<Kid> kidsCopy;
    copy(kids.begin(), kids.end(), back_inserter(kidsCopy));
    srand(time(0));
    while (kidsCopy.size() > 0) {
        list<Kid>::iterator it = kidsCopy.begin();
        advance(it, rand() % kidsCopy.size());
        shuffledKids.push_back(*it);
        kidsCopy.erase(it);
    }
    return shuffledKids;
}
