#include <iostream>
#include <vector>

using namespace std;

template <class T>
class MyVector {
    vector<T> values;
public:
    MyVector();
    ~MyVector();
    void push_back(T v1);
    vector<T> getValues() const;
    T max() const;
    bool hasDuplicates() const;
    void removeDuplicates() ;
};


// exception EmptyVector
class EmptyVector
{ };

// methods
template <class T>
MyVector<T>::MyVector() {}

template <class T>
MyVector<T>::~MyVector() {}

template <class T>
void MyVector<T>::push_back(T v1) {
    values.push_back(v1);
}

template <class T>
vector<T> MyVector<T>::getValues() const {
    return values;
}

//---------------------------------

// TODO
template <class T>
T MyVector<T>::max() const {
    T vmax = values[0];
    for(unsigned int i = 0; i < sizeof(values); i++) {
        if (values[i] > vmax) {
            vmax = values[i];
        }
    }
	return vmax;
}

// TODO
template<class T>
bool MyVector<T>::hasDuplicates() const {
	return true;
}

// TODO
template<class T>
void MyVector<T>::removeDuplicates() {
}

