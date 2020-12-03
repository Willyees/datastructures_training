#pragma once
#include "array.h"
#include <algorithm>

//resizable array. can add and remove at any position O(n- i)
template<class T>
class ArrayStack {
protected:

public:
	size_t _n_elements;
	Array<T> a;
	int size();
	T get(int index);
	T set(int index, T x);
	virtual void add(int index, T x);
	virtual T remove(int index);
	virtual void resize();

};

//implementation template class member functions

template<class T>
int ArrayStack<T>::size() {
	return _n_elements;
}

template<class T>
T ArrayStack<T>::get(int index) {
	return a[index];
}

//returning the old value so it is not lost
template<class T>
T ArrayStack<T>::set(int index, T x) {
	T x_old = a[index];
	a[index] = x;
	return x_old;
}

template<class T>
void ArrayStack<T>::add(int index, T x) {
	//check that the backing array is not full. otherwise resize it
	if (a.size < _n_elements + 1)
		resize();
	//shift elements 1 position O(n - index). best to do reversed, not as much temporary variables
	//loop starts from last element + 1 in the ArrayStack: should be something like garbage value, and it will be overwritten. This is different from the inner array last index
	for (int i = _n_elements; i > index; --i) {
		a[i] = a[i - 1];
	}
	//adding new value
	a[index] = x;
	_n_elements++;
}

template<class T>
T ArrayStack<T>::remove(int index) {
	T x = a[index];
	//moving 1 position left all the elements until the last element - 1. The last element will not be overwritten but it doesn't matter because is not accessible (_n_elements--), so is treated as garbage
	for (int i = index; i < _n_elements - 1; ++i) {
		a[i] = a[i + 1];
	}
	_n_elements--;
	//checking if many positions are empty, then resize
	if (a.size >= 3 * _n_elements)
		resize();
	return x;
}

template<class T>
void ArrayStack<T>::resize() {
	//setting size to 1 in case the size was 0
	Array<T> b(std::max((int) a.size * 2, 1));
	//deep copy for each element
	for (int i = 0; i < a.size; ++i) {
		b[i] = a[i];
	}
	a = b;
}


//other implementation using std functionalities that should lower the running time (but not asymptotically)
template<class T>
class FastArrayStack : public ArrayStack<T>{
public:
	using ArrayStack<T>::_n_elements; using ArrayStack<T>::a;
	void resize() override;
	void add(int index, T x) override;
	T remove(int index) override;
};

template<class T>
void FastArrayStack<T>::resize() {
	Array<T> b(std::max(1, (int) (2 * _n_elements))); //have to use this pointer to access base member variables in inherited templates. Otherwise can use: using ArrayStack<T>::_n_elements
	std::copy(a + 0, a + _n_elements, b + 0); //sum on the Array<T> returns a pointer
	this->a = b;
}

template<class T>
void FastArrayStack<T>::add(int index, T x) {
	if (_n_elements + 1 > a.size)
		resize();
	std::copy_backward(a + index, a + _n_elements, a + index + 1);//[first, last) : first included, last not included
	a[index] = x;
	_n_elements++;
}

template<class T>
T FastArrayStack<T>::remove(int index) {
	T x = a[index];
	std::copy(a + index + 1, a + _n_elements, a + index);
	_n_elements--;
	if (a.size > 3 * _n_elements)
		resize();
	return x;
}

