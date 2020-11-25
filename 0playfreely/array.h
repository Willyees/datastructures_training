#pragma once
#include <iostream>
#include <assert.h>
/*
implementation of array data structure. similar as [] but keeps a count of number of elements*/
template<class T> 
class Array {
private:
	T* _pos = nullptr;

public:
	size_t _size;

	Array();
	Array(size_t size);
	T& operator[](int i);

	Array<T>* operator=(Array<T>&& b);
	Array<T>* operator=(Array<T>& b);//not using copy, it references the move operator
	T* operator+(int i);
};

/*
all the templates member functions have to be defined in the header file. otherwise could include a .tpp file where they are defined*/
template<class T>
Array<T>::Array() {
	std::cout << "default constr" << std::endl;
}

template<class T>
Array<T>::Array(size_t size) : _size(size) {
	std::cout << "size_t constr" << std::endl;
	_pos = new T[size];
}

//operators overloading
template<class T>
T& Array<T>::operator[](int i) {
	assert(i < _size && i >= 0);
	return _pos[i];
}

//returns a pointer to the element at ith position
template<class T>
T* Array<T>::operator+(int i) {
	return &_pos[i];
}

//second array has its references removed. not copy assignement but move
template<class T>
Array<T>* Array<T>::operator=(Array<T>&& b) {
	if (_pos != nullptr)
		delete[] _pos;
	_pos = b._pos;
	b._pos = nullptr;
	_size = b._size;
	return this;
}

template<class T>
Array<T>* Array<T>::operator=(Array<T>& b) {
	return *this = std::move(b);
}
