#pragma once
#include "binary_tree.h"
#include <climits>
#include <cmath>

//specifiying also the Node template class so a children class can still inherit from BSTreeNode
//if it wouldnt allow to specify a different Node, it would be forced to use a Node of type BSTNode also for an inherited class, which might miss some important members
template<class T, class Node>
class BSTNode  : public BTNode<Node> {

public:
	T data;
};

template<class T, class Node>
class BinarySearchTree : public BinaryTree<Node> {
protected:
	int n;//#of elements in the tree
	void splice(Node* node);//removing node and adding its child to node->parent
	T null;
	bool add(Node* node);
public:
	T findEQ(T x);
	Node* findLast(T x);
	bool add(T x);
	bool addChild(Node* previous, Node* u);
	void remove(Node* node);
	void rotateLeft(Node* node);
	void rotateRight(Node* node);
};

//specifiying that for a bstnode class, the used node type is the same class
//still allowing to inherit from it and specify a different type of node
template<class T>
class BSTNodeUsable : public BSTNode<T, BSTNodeUsable<T>> {};

template<class T>
class BinarySearchTreeUsable : public BinarySearchTree<T, BSTNodeUsable<T>> {};

template<class T, class Node>
T BinarySearchTree<T, Node>::findEQ(T x) {
	Node* node = this->r;
	while (node != this->nil) {
		if (x < node->data)
			node = node->left;
		else if (x > node->data)
			node = node->right;
		else
			return node->data;
	}
	return NULL;
}

//will find the last node before x in case it is not found. if x exists in the tree, the node is returned
template<class T, class Node>
Node* BinarySearchTree<T, Node>::findLast(T x) {
	Node* node = this->r, * previous = this->nil;
	while (node != this->nil) {
		previous = node;
		if (node->data < x)
			node = node->left;
		else if (node->data > x)
			node = node->right;
		else
			return node;
	}
	return previous;
}

template<class T, class Node>
bool BinarySearchTree<T, Node>::add(T x) {
	Node* p = findLast(x);
	Node* node = new Node;
	node->data = x;
	return addChild(p, node);
}

//add a new node 'node' to the parent node 'previous'
//same value data not allowed. if new data > parent -> set to the right child, otherwise left
template<class T, class Node>
bool BinarySearchTree<T, Node>::addChild(Node* previous, Node* node) {
	if (previous == this->nil) {
		this->r = this->nil;//inserting in empty tree
	}
	else {
		if (node->data < previous->data)
			previous->left = node;
		else if (node->data > previous->data)
			previous->right = node;
		else
			return false; //node.data is alreadty stored in the tree
		node->parent = previous;
	}
	n++;
	return true;
}

//function to be called only in case to remove node which has ONLY 1 child.
//can be used also to remove leaf nodes (0 children)
template<class T, class Node>
void BinarySearchTree<T, Node>::splice(Node* node) {
	Node* s;//child of the node being removed
	Node* previous;//parent
	if (node->left != this->nil) {//check if left and right are not empty then set node s
		s = node->left;
	}
	else {
		s = node->right;
	}
	if (node == this->r) {//special case if node is the root. child becomes the root
		this->r = s;
		previous = this->nil;//previous set to nil
	}
	else {
		previous = node->parent;//remove the node from parent and replace it with its child
		if (previous->left == node) {
			previous->left = s;
		}
		else {
			previous->right = s;
		}
	}
	if (s != this->nil)//if child not null set reference to the parent
		s->parent = previous;//only modify value of child if is not nil. otherwise it means that the parent ('node') was a leaf
	n--;
}

template<class T, class Node>
bool BinarySearchTree<T, Node>::add(Node* node) {
	Node* parent = findLast(node->data);//this element should not exist, so return leaf
	addChild(parent, node);

}

template<class T, class Node>
void BinarySearchTree<T, Node>::remove(Node* node) {
	if (node->left == this->nil || node->right == this->nil) {//special case: easy replacement in case only 1 child, use splice
		splice(node);
		delete node;
	}
	else {//case in which node has 2 chilren
		Node* w = node->right;
		while (w->left != this->nil)//keep going left until a leaf is found. this is the lowest value in the right subtree (so it is > node.data)
			w = w->left;
		node->data = w->data;//swap the data between node and w
		splice(w);//use splice to remove w (will apply the case for leaf)
		delete w;
	}
}

//w is right child of parent
template<class T, class Node>
void BinarySearchTree<T, Node>::rotateLeft(Node* node) {
	Node* w = node->right;
	w->parent = node->parent;
	if (w->parent != this->nil){
		if (w->parent->right == node)
			w->parent->right = w;
		else
			w->parent->left = w;
	}
	node->right = node->left;
	if (node->right != this->nil)
		node->right->parent = node;
	w->left = node;
	node->parent = w;
	if (node == this->r) {
		this->r = w;
		w->parent = this->nil;
	}

}


//w is left child of parent
template<class T, class Node>
void BinarySearchTree<T, Node>::rotateRight(Node* node) {
	Node* w = node->left;
	Node* parent = node->parent;
	w->parent = node->parent;
	if(node->parent != this->nil)
	node->left = w->right;
	w->right = node;
}


