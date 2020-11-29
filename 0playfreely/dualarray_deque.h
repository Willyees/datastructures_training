#pragma once
#include "array_stack.h"

template<class T>
class DualArrayDeque {
	ArrayStack<T> _front;
	ArrayStack<T> _back;

public:
	T get(int i);
	void set(int i, T x);
	void add(int i, T x);
};

template<class T>
T DualArrayDeque<T>::get(int i) {
	if (i < _front.size())
		return _front.get(_front.size() - i - 1);
	else
		return _back.get(i - _front.size());
}

template<class T>
void DualArrayDeque<T>::set(int i, T x) {
}

//todo: finish