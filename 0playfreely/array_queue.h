#pragma once
#include "array.h"
#include <iostream>

template<class T>
class ArrayQueue {
	Array<T> _a;
	int _j; //position next element to be removed
	int _n_elements;
public:
	
	bool add(T x);
	T remove();
	void resize();	
	T front();
	T back();
};

//add next element either after the previous element or wrap around at the beginning of the array. This is acheived with the mod operator
//not possible to add at wanted index
template<class T>
bool ArrayQueue<T>::add(T x) {
	if (_n_elements + 1 > _a.size)
		resize();
	_a[(_j + _n_elements) % _a.size] = x;
	_n_elements++;
	return true;
}

//remove next element specified by the _j parameter
template<class T>
T ArrayQueue<T>::remove() {
	T x = _a[_j];
	//removing by moving the _j position index 1 position after. if at the end of array, it will wrap around using mod operator
	_j = (_j + 1) % _a.size;
	_n_elements--;
	if (_a.size > 3 * _n_elements)
		resize();
	return x;
}

//resize will also modify the indexes of the array in a because the next add needs to be successive and not overwrite an old value
// _a: |4|5|6|0|1|2|3|
// _b: |4|5|6|0|1|2|3| | | | | | | |  bad_b. next add would overwrite '0' and it would not be able to use the new spaces
// _b: |0|1|2|3|4|5|6| | | | | | | | correct _b. move the _j at beginning of array
template<class T>
void ArrayQueue<T>::resize() {
	int size = std::max(1, (int)_a.size * 2);
	Array<T> b(size);

	for (int i = 0; i < _n_elements; ++i) {
		b[i] = _a[(_j + i) % _a.size];//looping following the next element to be deleted (they are in order) and then wrap around at the end of '_a' array
	}
	_a = b;
	_j = 0;//resetting the next element to be deleted to correct one
}

//access next element
template<class T>
T ArrayQueue<T>::front() {
	return _a[_j];
}

template<class T>
T ArrayQueue<T>::back() {
	return _a[(_j + _n_elements -1) % _a.size];
}

