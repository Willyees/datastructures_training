#pragma once
#include "binary_search_tree.h"

template<class T, class Node>
class RedBlackTree;//forward declare

template<class T, class Node>
class RedBlackNode : public BSTNode<T, Node> {
public://have to set is as public becuase having problems with the friend class access since this class is inherited from redblacknodeusable
	friend class RedBlackTree<T, Node>;
	char colour;
};

int red = 0;
int black = 1;

template<class T, class Node>
class RedBlackTree : public BinarySearchTree<T, Node> {
	using BinarySearchTree<T, Node>::nil;
protected:
	void pushBlack(Node* node);
	void pullBlack(Node* node);
	void flipLeft(Node* node);
	void flipRight(Node* node);
	void swapColours(Node* p, Node* c);
	bool add(T x);
	void addFixup(Node* u);
	//bool remove(T x). skipping because of no point learning all the rotations needed.

public:

};

template<class T>
class RedBlackNodeUsable : public RedBlackNode<T, RedBlackNodeUsable<T>> {
	//friend class RedBlackTree<int, RedBlackNodeUsable<int>>;
};

//node: black, two children to red
//node: transformed to red. 2 children black.
template<class T, class Node>
void RedBlackTree<T, Node>::pushBlack(Node* node) {
	node->colour--;			//black: 1 -> red: 0
	node->left->colour++;	//red -> black
	node->right->colour++;	//red -> black
}


template<class T, class Node>
void RedBlackTree<T, Node>::pullBlack(Node* node) {
	node->colour++;			//red: 0 -> black: 1
	node->left->colour--;	//black -> red
	node->right->colour--;	//black -> red
}

//swaps colours 'node' and 'node'.right, performs left rotation
//swaps colours and reverse relation parent and child
template<class T, class Node>
void RedBlackTree<T, Node>::flipLeft(Node* node) {
	swapColours(node, node->right);
	this->rotateLeft(node);
}

//swap colours 'node' and 'node'.left, perform right rotation
template<class T, class Node>
void RedBlackTree<T, Node>::flipRight(Node* node) {
	swapColours(node, node->left);
	this->rotateRight(node);
}

template<class T, class Node>
void RedBlackTree<T, Node>::swapColours(Node* p, Node* c) {
	char parent_c = p->colour;
	p->colour = c->colour;
	c->colour = parent_c;
}

//add a red node. Will not break the black-height property, but might break the left leaning/
template<class T, class Node>
bool RedBlackTree<T, Node>::add(T x) {
	Node* node = new Node();
	node->left = node->right = node->parent = nil;
	node->data = x;
	node->colour = red;
	bool added = BinarySearchTree<T, Node>::add(node);
	if (added)
		addFixup(node);
	else
		delete node;
	return added;
}

template<class T, class Node>
void RedBlackTree<T, Node>::addFixup(Node* u) {
	while (u->colour == red) {
		if (u == this->r) {//u is root, change colour and return
			u->colour = black;
			return;
		}
		Node* w = u->parent;
		if (w->left->colour == black) { //ensure left leaning. Since left is black, it means that the 'u' was set as a right (it is red) so the leftleaning is not correct
			//correct leftleaning by flipping red and exchaning w with u
			flipLeft(w);//swaps colours w and node u, then rotate left
			u = w;
			w = u->parent;
		}
		if (w->colour == black)
			return;
		Node* g = w->parent;//gran parent node
		if (g->right->colour == black) {//if right is black, left has to be red because w is red
			//flipright will swap colors between g and w, and also g becomes child of w. a black node is set instead of the two red nodes
			flipRight(g);
			return;//balanced
		}
		else {//g->right->colour = red, the two children are both red, pushing a black swapping their colour with the parent
			pushBlack(g);
			u = g;//have to start again because the granparent might be unbalanced as the beginning node.
		}

	}
}
