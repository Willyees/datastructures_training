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
	int depth(Node* u);
	int size(Node* u);
	int height(Node* u);
	void traverse(Node* u);
	void traverse2();
	void bfTraverse();//breadth - first
};

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

