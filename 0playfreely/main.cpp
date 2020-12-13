#define NOMINMAX
#include <iostream>
#include <vector>
#include "objs.h"
#include <assert.h>
#include <vector>
#include <deque>
#include <stack>
#include <queue>
#include <map>
#include <algorithm>
#include <iterator>
#include "excercises.h"
#include "array.h"
#include "array_stack.h"
#include "array_queue.h"
#include "array_deque.h"
#include "dllist.h"
#include "binary_search_tree.h"
#include "treap.h"
#include "search_alg.h"
#include "sort_alg.h"
#include <sstream>
#include <list>
#include "graph.h"


//declaring functions where are contained the excercises (extern is not needed, but gives a better idea)
namespace tut {
	extern void _map();
	extern void _hash_map();
}
using namespace std;

int z = 20;
namespace aa {
	int z = 10;
	namespace cc {
		int x = z;
	}
}

void f(A& a) {
	std::cout << "inside f " << std::endl;
	a.i = 20;
}

void swap(int* i1, int* i2) {
	int tmp = *i1;
	*i1 = *i2;
	*i2 = tmp;
}

auto f(int i, double b) -> decltype(i > b ? i : b) {
	return (i > b ? i : b);
}

void f1(int i = 5) { cout << i << endl; } 

struct a {
	a() {
		cout << "constr" << endl;
	}
	int i = 4;
};
struct c : a{
	void f();
};

template<class T, class V>
class asd{};


template<class T>
class asd<T,T> {};


void t2(int p[]) { cout << p[1] << endl; }
int main() {
	cout << sizeof(char) << endl;
	cout << sizeof(int) << endl;
	cout << sizeof(short) << endl;
	//run_all_tests();
	std::list<int> l;
	std::vector<int> v1{ 5 };
	std::vector<int> v2{ 3 };
	;
	std::vector<int> vi{ 5,6,1,0,9,7,11,4 };
	int a[] = { 5,6,1,0,9,7,11,4 };
	Graph g(9);
	g.addEdge(1, 2);
	g.addEdge(2, 3);
	g.addEdge(3, 4);
	g.addEdge(4, 5);
	g.addEdge(4, 6);
	g.addEdge(0, 1);
	g.addEdge(7, 8);
	std::vector<int> visits;
	std::vector<int> pred;
	deapthFirstSearch(g, 0, visits, pred);
	for (auto e : pred)
		cout << e << endl;

	cout << "***" << endl;
	//find path from 0 to 6
	int first = 0;
	int last = 6;

	while (last != first) {
		cout << (last = pred[last]) << endl;
	}
	//for (auto e : vi1) {
	//	cout << e << endl;
	//}
	//remove items from vector
	//vec.erase(std::remove(vec.begin(), vec.end(), &o), vec.end()); //erase by value

	/*auto it = std::find(vec.begin(), vec.end(), &o);
	std::cout << "A: " << o.name << std::endl;

	if (it != vec.end()) { 
		vec.erase(it); 
		std::cout << "removed A" << std::endl;
	}

	std::cout << "A: " << o.name << std::endl;

	std::cout << std::endl;

	for (auto e : vec) {
		std::cout << "items: " << e->name << std::endl;
	}
	*/
	return 0;
}
