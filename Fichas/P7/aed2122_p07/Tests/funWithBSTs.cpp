// AED 2021/2022 - Aula Pratica 07
// Pedro Ribeiro (DCC/FCUP) [06/12/2021]

#include <set>
#include "funWithBSTs.h"
#include "bst.h"

// ----------------------------------------------------------
// Exercicio 1: Colecao de Cromos
// ----------------------------------------------------------
// TODO
int FunWithBSTs::newBag(const vector<int>& collection, const vector<int>& bag) {
    set<int> collectionSet;
    int initialCollectionSize = 0;

    for (auto c : collection) collectionSet.insert(c);
    initialCollectionSize = collectionSet.size();
    for (auto b : bag) collectionSet.insert(b);

    return collectionSet.size() - initialCollectionSize;
}

// ----------------------------------------------------------
// Exercicio 2: Batalha de Pokemons
// ----------------------------------------------------------
// TODO
int FunWithBSTs::battle(const vector<int>& alice, const vector<int>& bruno) {
    multiset<int> aliceCards, brunoCards; // All sets are ordered

    for (auto c : alice) aliceCards.insert(c);
    for (auto c : bruno) brunoCards.insert(c);

    multiset<int>::const_iterator aliceMove;
    multiset<int>::const_iterator brunoMove;
    while (!aliceCards.empty() && !brunoCards.empty()) {
        aliceMove = --aliceCards.end();
        brunoMove = --brunoCards.end();

        if (*aliceMove > *brunoMove) {
            aliceCards.erase(aliceMove);
            aliceCards.insert(*aliceMove - *brunoMove);
            brunoCards.erase(brunoMove);
        }
        else if (*aliceMove < *brunoMove) {
            brunoCards.erase(brunoMove);
            brunoCards.insert(*brunoMove - *aliceMove);
            aliceCards.erase(aliceMove);
        }
        else {
            aliceCards.erase(aliceMove);
            brunoCards.erase(brunoMove);
        }
    }

    if (aliceCards.empty() && brunoCards.empty()) return 0;
    else if (aliceCards.empty()) return brunoCards.size() * (-1);
    return aliceCards.size();
}

// ----------------------------------------------------------
// Exercicio 3: Reviews Cinematograficas
// ----------------------------------------------------------

// ..............................
// a) Contando Filmes
// TODO
int FunWithBSTs::numberMovies(const vector<pair<string, int>>& reviews) {
    set<string> movies;
    vector<pair<string, int>>::const_iterator it;

    for (auto p : reviews) {
        movies.insert(p.first);
    }

    return movies.size();
}

// ..............................
// b) O filme com mais reviews
// TODO
void FunWithBSTs::moreReviews(const vector<pair<string, int>>& reviews, int& m, int& n) {
    map<string, int> movies;
    string name;
    m = 1;
    n = 0;
    int revCount = 0;

    for(const auto& review : reviews){
        name = review.first;
        pair<string, int> in(name, 1);
        pair<map<string,int>::iterator, bool> it = movies.insert(in);
        if(!it.second){
            revCount = ++it.first->second;
            if(revCount > m){
                m = revCount;
                n = 1;
            }
            else if(revCount == m)
                n++;
        }
        else{
            if(m == 1) n++;
        }
    }
}

// ..............................
// c) Os melhores filmes
// TODO
vector<string> FunWithBSTs::topMovies(const vector<pair<string, int>>& reviews, double k) {
    vector<string> answer;
    map<string,pair<int,double>> movies; // map<movieName, pair<numberOfTimes,average>>

    for (auto& review : reviews) {
        pair<string,pair<int,double>> in(review.first,pair<int,double>(review.second,1));
        pair<map<string,pair<int,double>>::iterator, bool> it = movies.insert(in);
        if (!it.second) {
            it.first->second.first += review.second;
            it.first->second.second++;
        }
    }

    for (auto movie : movies) {
        if (movie.second.first/movie.second.second >= k) {
            answer.push_back(movie.first);
        }
    }

    return answer;
}
