#pragma once
#include "array_stack.h"
#include "array.h"


template<class T>
class ChainedHashTable {
protected:
	Array<ArrayStack<T>> t;
	int n_elements;

public:
	bool add(T x);
	T find(T x);
	int hash(T x);
	void resize() {}
	T remove(T x);
};

template<class T>
bool ChainedHashTable<T>::add(T x) {
	if (find(x) != NULL) return false;//check that x is not present already
	if (n_elements + 1 > t.size) resize();//check if array is full
	t[hash(x)].add(x);//directly add new value
	n_elements++;
	return true;
}

//iterate over the arraystack at index given by the hash. O(lengtharray at index)
template<class T>
T ChainedHashTable<T>::remove(T x) {
	int index = hash(x);
	for (int i = 0; i < t[index].size(); ++i) {
		T y = t[index].get(i);
		if (x == y) {
			t[index].remove(i);
			n_elements--;
			return y;
		}
	}
	return NULL;
}

template<class T>
T ChainedHashTable<T>::find(T x) {
	int j = hash(x);//index of arraystack
	for (int i = 0; i < t[j].size(); i++)
		if (x == t[j].get(i))
			return t[j].get(i);
	return NULL;
}