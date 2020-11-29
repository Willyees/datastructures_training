#pragma once
#include<iostream>
#include "array_deque.h"

template<class T>
class DLList {

	struct Node {
	public:
		Node* previous, *next;
		T data;

		Node(T data) : data(data), previous(nullptr), next(nullptr){}
		Node() : previous(nullptr), next(nullptr), data((T) 0) {}
	};

	Node dummy;
	int n_elements;
	Node* getNode(int i);
public:
	DLList() {
		dummy.next = &dummy;
		dummy.previous = &dummy;
		n_elements = 0;
	}

	T get(int i);
	T set(int i, T x);
	Node* addBefore(Node* w, T x);
	Node* addAfter(Node* w, T x);
	void add(int i, T x);
	void remove(Node* w);
	T remove(int i);
	void display();
};

//find which end is closer to i O(1 + min(i, n- i)). so it is known which direction to iterate through
//helper function that can be used by both get and set methods
template<class T>
typename DLList<T>::Node* DLList<T>::getNode(int i) {//need the typename to specify that the Node is a pointer
	Node* current;
	if (i < n_elements / 2) {
		current = dummy.next;
		for (int k = 0; k < i; ++k) {
			current = current->next;
		}
		return current;
	}
	else {
		current = dummy.previous;
		for (int k = 0; k < (n_elements - i); ++k) {
			current = current->previous;
		}
		return current;
	}
}

template<class T>
T DLList<T>::get(int i) {
	return getNode(i)->data;
}

template<class T>
T DLList<T>::set(int i, T x) {
	Node* n = getNode(i);
	T temp = n.data;
	n->data = x;
	return temp;
}

//add before by broking link and changing previous "next" pointer to newly added element
template<class T>
typename DLList<T>::Node* DLList<T>::addBefore(Node* n, T x) {
//by using dummy node, no special cases must be treated (xes: empty link-list)
	Node* new_node = new Node(x);
	//set next pointers
	n->previous->next = new_node;
	new_node->next = n;
	//set previous pointers
	new_node->previous = n->previous;
	n->previous = new_node;
	n_elements++;
	return new_node;
}

template<class T>
typename DLList<T>::Node* DLList<T>::addAfter(Node* w, T x) {
	
}

template<class T>
void DLList<T>::add(int i, T x) {
	addBefore(getNode(i), x);
}

template<class T>
void DLList<T>::remove(Node* node) {
	node->previous->next = node->next;
	node->next->previous = node->previous;
	delete node;
	n_elements--;
}

template<class T>
T DLList<T>::remove(int i) {
	Node* node = getNode(i);
	T x = node->data;
	remove(node);
	return x;
}

template<class T>
void DLList<T>::display() {
	std::cout << "Doubly linked-list data:" << std::endl;
	for (int k = 0; k < n_elements; ++k) {
		std::cout << get(k) << std::endl;
	}
}

//Space Efficient LinkedList
template<class T>
class SEList {
	int length_deque;
protected:
	class Node {
	public:
		BDeque<T> d;
		Node* previous, * next;
		Node() = default;
		Node(int size) : d(size) {}
	};

	//class used to store info about a specific data node index 
	class Location {
	public:
		Node* node;
		int j;//offset to get the specific index in the bounddeque
		Location() = default;
		Location(Node* node, int j) : node(node), j(j) {
		}
	};
public:
	int n_elements;//total number of elements
	Node dummy;
	SEList(int b);

	void getLocation(int i, Location& ell);//helper to implement get and set
	T get(int i);
	T set(int i, T x);
	void add(T x);
};

template<class T>
 SEList<T>::SEList(int length_deque) : dummy(length_deque) , length_deque(length_deque) , n_elements(0){
	 dummy.next = &dummy;
	 dummy.previous = &dummy;
 }

//pass a location object and it will be loaded with the node pointer and info about the needed location
//int i: index, Location& ell: object storing the node searched info
template<class T>
void SEList<T>::getLocation(int i, Location& ell) {
	//check if the index is in the first half or the second for better performance
	if (i < n_elements / 2) {
		Node* node = dummy.next;
		while (i >= node->d.size()) {//if index i is > current size-> it must mean that is in a successive node
			i -= node->d.size();//keep decreasing index i by the number of elements in the current node being analyzed
			node = node->next;
		}
		ell.node = node;
		ell.j = i;//remaining positions to get to the index i (offset)
	}
	else {//using the n_elements that is the total number of elements in the whole nodes. keep increasing i
		Node* node = &dummy;
		int idx = n_elements;
		while (i < idx) {
			node = node->previous;
			idx -= node->d.size();//keep decreasing the total number of elements until index i is > than it. meaning that 'i' has to be in that node (or the next, but they have been already checked)
		}
		ell.node = node;
		ell.j = i - idx;//offset
	}
}

template<class T>
T SEList<T>::get(int i) {
	Location l;
	getLocation(i, l);
	return l.node->d.get(l.j);
}

template<class T>
T SEList<T>::set(int i, T x) {
	Location l;
	getLocation(i, l);
	T x = l.node->d.get(l.j);
	l.node->d.set(l.j, x);
	return x;
}

//add at the end of the list
template<class T>
void SEList<T>::add(T x) {
	Node* last = dummy.previous;
	if (last == &dummy || last->d.size() == length_deque + 1) {//check if last block is full or no blocks yet
		last = addBefore(&dummy);//todo:create new addbefore method that only insert a new clean node
	}
}
