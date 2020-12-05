#pragma 
#include <algorithm>
#include "array_queue.h"
//represent a Node in a Binary Tree. Generic template. class N should be a node, but cannot instantiate a BTNode<BTNode>. Have to create a specializated class to be able to use it
template<class N>
class BTNode {
public:
	N* left;//lx child
	N* right;//rx child
	N* parent;//parent node
	BTNode() : left(nullptr), right(nullptr), parent(nullptr) {}
};
//specialization of BTNode that uses it self as a left, right and parent node.
class BTNode_usable : public BTNode<BTNode_usable> {};

template<class Node>
class BinaryTree {
protected:
	Node* r;//root node
	Node* nil;//null-like node
public:
	BinaryTree();
	BinaryTree(Node* nil);
	~BinaryTree();
	void clear();
	int depth(Node* u);
	int size(Node* u);
	int height(Node* u);
	void traverse(Node* u);
	void traverse2();
	void bfTraverse();//breadth - first
};

//set nil value as harcoded nullptr and root as a nil
template<class Node>
BinaryTree<Node>::BinaryTree() {
	nil = nullptr;
	r = nil;
}

//user specifies the nil value
template<class Node>
BinaryTree<Node>::BinaryTree(Node* nil) {
	this->nil = nil;
	r = nil;
}

template<class Node>
BinaryTree<Node>::~BinaryTree() {
	clear();
}

//traverse the tree in order. every new node encountered is deleted until the current node is nil
//order to traverse: parent, left, right
template<class Node>
void BinaryTree<Node>::clear() {
	Node* node = r;
	Node* previous = nil;
	Node* next = nil;

	while (node != nil) {
		if (previous == node->parent) {
			if (node->left != nil)
				next = node->left;
			else if (node->right != nil)
				next = node->right;
			else
				next = node->parent;
		}
		else if (previous == node->left) {
			if (node->right != nil)
				next = node->right;
			else
				next = node->parent;
		}
		else
			next = node->parent;
		previous = node;
		if (next == node->parent)//start deleting when the tree is being unwinded, going up to the parent so it will not delete refenrences to children before visiting them
			delete node;
		node = next;
	}
	r = nil;
}

template<class Node>
int BinaryTree<Node>::depth(Node* u) {
	int d = 0;
	while (u != r) {
		d++;
		u = u->parent;
	}
	return d;
}

template<class Node>
int BinaryTree<Node>::size(Node* u) {
	if (u == nil)
		return 0;
	return 1 + size(u->left) + size(u->right);
}

template<class Node>
int BinaryTree<Node>::height(Node* u) {
	if (u == nil)
		return -1;
	return 1 + std::max(height(u->left), height(u->right));
}

template<class Node>
void BinaryTree<Node>::traverse(Node* u) {
	if (u == nil)
		return;
	traverse(u->left);
	traverse(u->right);
}

//not using recursion to ensure that for large trees, no stack overflow can happen
template<class Node>
void BinaryTree<Node>::traverse2() {
	Node* u = r, * prev = nil, * next;
	while (u != nil) {
		if (prev == u->parent) {
			if (u->left != nil) next = u->left;
			else if (u->right != nil) next = u->right;
			else next = u->parent;
		}
		else if (prev == u->left) {
			if (u->right != nil) next = u->right;
			else next = u->parent;
		}
		else {
			next = u->parent;
		}
		prev = u;
		u = next;
	}
}

//using queue. add u.left and u.right. remove first node and add its u.left and u.right (if not nil).
//Traverse by level, left to right.
template<class Node>
void BinaryTree<Node>::bfTraverse() {
	ArrayQueue<Node*> q;
	if (r != nil)
		q.add(r);
	while (q.size() > 0) {
		Node* u = q.remove();
		if (u->left != nil)
			q.add(u->left);
		if (u->right != nil)
			q.add(u->right);
	}
}

