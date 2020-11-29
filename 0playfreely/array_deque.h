#pragma once
#include "array.h"

template<class T>
class ArrayDeque {
	Array<T> _a;
	int _j;
	int _n_elements;
public:
	T get(int i);
	T set(int i, T x);
	void add(int i, T x);
	T remove(int i);
	void resize();
	int size();
};

template<class T>
T ArrayDeque<T>::get(int i) {
	return _a[(_j + i) % _a.size];
}

template<class T>
T ArrayDeque<T>::set(int i, T x) {
	T x_old = _a[(_j + i) % _a.size];
	_a[(_j + i) % _a.size] = x;
	return x_old;
}

template<class T>
void ArrayDeque<T>::add(int i, T x) {
	if (_n_elements + 1 > _a.size)
		resize();
	//checking if i is before or after middle of _n_elements, then make space for it by just moving _n_elements / 2 elements
	if (i < (_n_elements / 2)) { //shift a[0] .. a[i - 1] 1 space left
		_j = (_j == 0) ? _a.size - 1 : _j - 1;
		for (int k = 0; k < i; ++k) {
			_a[(_j + k) % _a.size] = _a[(_j + k + 1) % _a.size];
		}
	}
	else {
		for (int k = _n_elements; k > i; ++k) {
			_a[(_j + k) % _a.size] = _a[(_j + k - 1) % _a.size];
		}
	}
}

template<class T>
T ArrayDeque<T>::remove(int i) {//'i' doesn't denote the inner index. it is calculated with the mod operator!
	T x = _a[i];
	//check which half is 'i' in
	if (i < _n_elements / 2) {//shift right a[0].. a[i - 1] (not i, because it will overwritten)
		for (int k = i; k > 0; --k)
			a[(_j + k) % _a.size] = a[(_j + k - 1) % _a.size];
		_j = (_j + 1) % _a.size;//moving the pointer to first element right of 1 position
	}
	else {//shift left a[i + 1]..a[_n_elements - 1]
		for (int k = i + 1; k < _n_elements; ++k)
			a[(_j + k) % mod _a.size] = a[(_j + k + 1) % mod _a.size];
	}
	_n_elements--;
	if (_a.size > 3 * _n_elements)
		resize();
	return x;
}

//double the inner array length and reorder them
template<class T>
void ArrayDeque<T>::resize() {
	int new_size = std::max(1, _n_elements * 2);
	Array<T> b(new_size);
	//copy all the values into b in the new correct order
	for (int k = 0; k < _n_elements; ++k)
		b[k] = _a[(_j + k) % _a.size];

	_a = b;//steal values from b and change pointer to point b. clear previos values from a
	_j = 0;
}

template<class T>
int ArrayDeque<T>::size() {
	return _n_elements;
}

//bound deque that cannot resize itself
template<class T>
class BDeque : public ArrayDeque<T> {
	Array<int> a;
public:
	int n_elements;
	int j;

	virtual ~BDeque() {}
	BDeque() { std::cout << "default constructor bdeque" << std::endl; }
	BDeque(int size) : n_elements(0), j(0) {
		std::cout << "paramether constructor bdeque" << std::endl;
		Array<int> z(size + 1);
		a = z;
	}
	void add(int i, T x);
	bool add(T x);
	void resize() {};
};

template<class T>
bool BDeque<T>::add(T x) {
	ArrayDeque<int>::add(n_elements, x);
	return true;
}

template<class T>
void BDeque<T>::add(int i, T x) {
	ArrayDeque<T>::add(i, x);
}