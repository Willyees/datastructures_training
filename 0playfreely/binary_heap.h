#pragma once
#include "array.h"

template<class T>
class BinaryHeap {
protected:
	Array<T> a;
	int n;
	void trickleDown(int i);
	void bubbleUp(int i);
public:
	BinaryHeap() {}
	int left(int i);
	int right(int i);
	int parent(int i);
	bool add(T x);
	T remove();
	void resize();
};



template<class T>
int BinaryHeap<T>::left(int i) {
	return i * 2 + 1;
}

template<class T>
int BinaryHeap<T>::right(int i) {
	return i * 2 + 2;
}

template<class T>
int BinaryHeap<T>::parent(int i) {
	return (i - 1) / 2;
}

//add at the end of the array, then move the previous values to maintain the heap ordered property (parent(i) < i)
template<class T>
bool BinaryHeap<T>::add(T x) {
	if (n + 1 > a.size) resize();
	a[n++] = x;//place x at the end and increase the number of elements by 1 (n++ returns the old n value, not the n + 1)
	bubbleUp(n - 1);
	return true;
}

//restore the heap ordered property by swapping x with its parent until x is no longer less than the parent
template<class T>
void BinaryHeap<T>::bubbleUp(int i) {
	int p = parent(i);
	while (i > 0 && a[i] < a[p]) {
		a.swap(i, p);

	}
}

//remove the smallest value (root)
template<class T>
T BinaryHeap<T>::remove() {
	T x = a[0];//smallest value
	a[0] = a[--n];
	trickleDown(0);
	if (n * 3 < a.size) resize();
	return x;
}

template<class T>
void BinaryHeap<T>::resize() {
	//2 cases: downsize, upsize. They are both based on number of elements n (so is still calculated in the same way: n_new = n * 2)
	//upsize
	int new_size = std::max((int) a.size * 2, 1);
	Array<T> b(new_size);
	std::copy(a + 0, a + n, b + 0);
	a = b;
}

//move downwards the value at position i, until it is the smaller than its two children
//parent is swapped with smalled of the two children
template<class T>
void BinaryHeap<T>::trickleDown(int i) {
	if (left(i) > n || right(i) > n)
		return;
	int l;
	int r;

	while (a[l] < a[i] || a[i] < a[i]) {
		l = left(i);
		r = right(i);
		if (l > n || r > n)
			return;
		//find smallest child and swap
		if (a[l] < a[r]) {
			a.swap(l, i);
		}
		else {
			a.swap(r, i);
		}
	}
}
