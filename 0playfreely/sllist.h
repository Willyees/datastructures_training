#pragma once

template<class T>
class Node {
public:
	T data;
	Node* next;

	Node() : next(nullptr) {}
	Node(T data) : data(data), next(nullptr) {}
};

template<class T>
class SLList {
	Node<T>* head;//first element
	Node<T>* tail;//last element
	int _n_elements;//efficiency variables. not needed for functional sllist

public:
	T push(T data);//add at last position
	T pop();
	Node<T>* getHead() { return head; }
	//need destructor freeing the memory taken from all the nodes
};

template<class T>
T SLList<T>::push(T data) {
	Node<T>* node = new Node<T>(data);
	node->next = head;
	head = node;
	if (_n_elements == 0)
		tail = node;
	_n_elements++;
	return data;
}

template<class T>
T SLList<T>::pop() {
	if (_n_elements == 0)
		return 0;
	T x = head->data;
	Node<T>* node = head;
	head = head->next;
	delete node;
	if (--_n_elements == 0)
		tail = nullptr;
	return x;
}


template<class T>
class SLListQueue {
	Node<T>* head;
	Node<T>* tail;
	int _n_elements;
public:
	void push(T data);//push from the tail
	T pop();//pop from the head
};

template<class T>
void SLListQueue<T>::push(T data) {
	Node* node = new Node(data);
	if (_n_elements == 0)
		head = node;
	else
		tail->next = node;
	tail = node;
	_n_elements++;
}

template<class T>
T SLListQueue<T>::pop() {
	if (_n_elements == nullptr)
		return 0;
	T x = head->data;
	Node<T>* next = head->next;
	delete head;
	head = next;

	if (--_n_elements == 0)//both reducing by 1 the # elements and checking if it is 0
		tail = nullptr;
	return x;
}


template<class T>
class SLListStack {
protected:
	class Node {
	public:
		Node* next;
		T data;
		Node(T data) : data(data) , next(nullptr) {}
	};

	Node* head;
public:
	void push(T data);
	T pop();
	T peek();

};

template<class T>
void SLListStack<T>::push(T data) {

}

template<class T>
T SLListStack<T>::pop() {
	return T();
}

template<class T>
T SLListStack<T>::peek() {
	return T();
}
