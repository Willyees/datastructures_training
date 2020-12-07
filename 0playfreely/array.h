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
	size_t size;

	Array();
	Array(size_t size);
	Array(size_t size, T init);
	T& operator[](int i);
	void swap(int i, int k);

	Array<T>* operator=(Array<T>&& b);
	Array<T>* operator=(Array<T>& b);//not using copy, it references the move operator
	T* operator+(int i);

	//debug
	void d_get_size_a();
	void d_get_structure_a();
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
void Array<T>::d_get_size_a() { std::cout << size << std::endl; }

//DEBUG
template<class T>
void Array<T>::d_get_structure_a() {
	std::cout << "-----" << std::endl;
	for (T* i = _pos; i != (_pos + size); ++i)
		std::cout << *i << std::endl;
	std::cout << "-----" << std::endl;
}