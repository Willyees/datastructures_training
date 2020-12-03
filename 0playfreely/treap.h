#pragma once
#include "binary_search_tree.h"
#include <iostream>
template<class T, class Node>
class Treap;

template<class T, class Node>
class TreapNode : public BSTNode<T, Node> {
protected:
	friend class Treap<T, Node>;
	int p;//unique random priority number. follow heap property: u.parent.p < u.p (except for the root)

};

template<class T, class Node>
class Treap : public BinarySearchTree<T, Node>{

public:
	using BinarySearchTree<T, Node>::r;
	using BinarySearchTree<T, Node>::nil;
	using BinarySearchTree<T, Node>::null;
	using BinarySearchTree<T, Node>::n;
	bool add(T x);
	void bubbleUp(Node* node);
	bool remove(T x);
	void trickleDown(Node* node);
	//void display(Node* x) { x->p; }
};

template<class T>
class TreapUsable;

template<class T>
class TreapNodeUsable : public TreapNode<T, TreapNodeUsable<T>> { friend class TreapUsable<T>;};

template<class T>
class TreapUsable : public Treap<T, TreapNodeUsable<T>> {
public:
	TreapUsable() = default;
};

//check that the 'node' has correct heap property compared to his parent, if not rotate the tree as many times needed to have node.parent.p < node.p
//stop the rotation when the parent is < node or when the node.parent == nil (meaning that node became the root of the tree)
template<class T, class Node>
void Treap<T, Node>::bubbleUp(Node* node) {
	while (node->parent != nil && node->parent->p > node->p) {
		//figure out if node is left or right parent
		if (node->parent->left == node)
			this->rotateRight(node->parent);
		else {
			this->rotateLeft(node->parent);
		}
	}
	if (node->parent == nil)
		r = node;
}


//adding a new node. using the binarysearchtree add method: will add as a leaf, so binary search tree property is satisfied
//heap property might not be correct, so check by using bubbleup that reorganize the tree to satisfy it
template<class T, class Node>
bool Treap<T, Node>::add(T x) {
	Node* node = new Node();
	node->data = x;
	node->p = rand();
	if (BinarySearchTree<T, Node>::add(x)) {//check if x added. it is possible to not add in case the value already existed
		bubbleUp(node);
		return true;
	}
	delete node;
	return false;
}

template<class T, class Node>
bool Treap<T, Node>::remove(T x) {
	Node* w = this->findLast(x);
	if (w != nil && w->data == x) {//check that the node returned is actually the correct one. (findlast will return the last node if x is not found)
		trickleDown(w);
		this->splice(w);
		delete w;
		return true;
	}
	return false;
}

template<class T, class Node>
void Treap<T, Node>::trickleDown(Node* node) {
	while (node->left != nil || node->right != nil) {
		
		if (node->left == nil)//if left is nil, right must not be nil, otherwise the while loop would have gone out earlier
			this->rotateRight(node);
		else if (node->right == nil)//left is for sure not nil (becuase of previous if)
			this->rotateLeft(node);
		//swap with the lowest between right and left. want to keep the lowest random ('p') in the highest position in the tree
		//both left and right are not nil
		else if (node->left->p < node->right->p)
				this->rotateRight(node);
			else
				this->rotateLeft(node);
		if (r == node)//book says so, I think this is taken care already in the rotation functions
			r = node->parent;
	}
}
