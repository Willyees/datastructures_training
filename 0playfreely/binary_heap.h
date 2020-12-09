#pragma once
#include "array.h"
#include <algorithm>

template<class T>
class BinaryHeap {
protected:
	Array<T> a;
	int n;
	void trickleDown(int i);
	void bubbleUp(int i);
public:
	BinaryHeap() : n(0) {}
	BinaryHeap(Array<T>&);
	int left(int i);
	int right(int i);
	int parent(int i);
	bool add(T x);
	T remove();
	void resize();
	void display();//display by level order
	static void sort(Array<T>&);
	Array<T> get_array();
};



template<class T>
BinaryHeap<T>::BinaryHeap(Array<T>& b) {
	//copy values from b into internal array (move constructor)
	a = b;
	n = a.size;
	//starting from the last parent available because if it would start from the root the heap property would not be respected
	//each level contains double the previous. last level has only children so cannot trickle down. # children = total / 2 + 1
	//so only iterating over parents reversed
	for (int i = n / 2 - 1; i >= 0; --i) {
		trickleDown(i);
	}
}

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
	int new_size = (std::max)((int)a.size * 2, 1);
	Array<T> b(new_size);
	std::copy(a + 0, a + n, b + 0);
	a = b;
}

template<class T>
void BinaryHeap<T>::display() {
	a.d_get_structure_a();
}

template<class T>
void BinaryHeap<T>::sort(Array<T>& b) {
	BinaryHeap<T> h(b);
	while (h.n > 1) {
		h.a.swap(0, h.n - 1);
		h.n--;
		h.trickleDown(0);
	}
	b = h.get_array();
	b.reverse();
}

template<class T>
Array<T> BinaryHeap<T>::get_array() {
	return a;
}

//move downwards the value at position i, until it is the smaller than its two children
//parent is swapped with smalled of the two children
template<class T>
void BinaryHeap<T>::trickleDown(int i) {//heapify

	int swap_i = 0;//flag like value that is only set in case the right or left child can be swapped
	//before accessing either left or right child, have to be sure that they are not available. cannot set this condition in while statement because it would not let to trickledown on a subtree with only 1 child
	while (i>=0) {//have to check that both left and right are available, it could be that the right child is not set
		swap_i = -1;

		int l = left(i);
		int r = right(i);
		
		if (r < n && a[r] < a[i]) {//start with r, because its internal index > left. so next if statement don't need to check if l < n
			//find smallest child and swap
			if (a[r] < a[l])
				swap_i = r;
			else
				swap_i = l;
		}
		else {
			if (l < n && a[l] < a[i])
				swap_i = l;
		}
		if (swap_i >= 0)
			a.swap(i, swap_i);
		i = swap_i;
	}
}
