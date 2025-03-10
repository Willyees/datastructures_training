#pragma once
#include <iostream>
#include <assert.h>
#include <algorithm>
/*
implementation of array data structure. similar as [] but keeps a count of number of elements*/
template<class T> 
class Array {
private:
	T* _pos = nullptr;

public:
	size_t size;

	Array();
	Array(size_t size);
	Array(size_t size, T init);
	explicit Array(T b[], size_t);
	Array(const Array<T>&) = default;
	T& operator[](int i);
	void swap(int i, int k);
	void reverse();

	Array<T>* operator=(Array<T>&& b);
	Array<T>* operator=(Array<T>& b);//not using copy, it references the move operator
	T* operator+(int i);
	T* get_pos() { return _pos; }
	//debug
	void d_print_size_a();
	void d_print_structure_a();
};

/*
all the templates member functions have to be defined in the header file. otherwise could include a .tpp file where they are defined*/
template<class T>
Array<T>::Array() {
	std::cout << "default constr" << std::endl;
}

template<class T>
Array<T>::Array(size_t size) : size(size) {
	std::cout << "size_t constr" << std::endl;
	_pos = new T[size];
}

template<class T>
Array<T>::Array(size_t size, T init) {
	this->size = size;
	_pos = new T[size];
	for (int i = 0; i < size; ++i) {
		_pos[i] = init;
	}
}

//copy all the elements in the internal array
template<class T>
Array<T>::Array(T b[], size_t size) {
	_pos = new T[size];
	this->size = size;
	std::copy(b, b + size, _pos);
}

//operators overloading
template<class T>
T& Array<T>::operator[](int i) {
	assert(i < size && i >= 0);
	return _pos[i];
}

template<class T>
void Array<T>::swap(int i, int k) {
	T temp = _pos[i];
	_pos[i] = _pos[k];
	_pos[k] = temp;
}

template<class T>
void Array<T>::reverse() {
	for (int i = 0; i < size / 2; ++i)
		swap(i, size - i - 1);
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
	size = b.size;
	return this;
}

template<class T>
Array<T>* Array<T>::operator=(Array<T>& b) {
	return *this = std::move(b);
}

template<class T>
void Array<T>::d_print_size_a() { std::cout << size << std::endl; }

//DEBUG
template<class T>
void Array<T>::d_print_structure_a() {
	std::cout << "-----" << std::endl;
	for (T* i = _pos; i != (_pos + size); ++i)
		std::cout << *i << std::endl;
	std::cout << "-----" << std::endl;
}