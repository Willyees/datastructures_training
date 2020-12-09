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


void t1(int* p) { cout << p[1] << endl; }
namespace t3 {
	
	void t1(int* p) { cout << p[1] << endl; }
}
void t2(int p[]) { cout << p[1] << endl; }
int main() {
	//run_all_tests();

	std::vector<int> v1{ 5 };
	std::vector<int> v2{ 3 };
	;
	std::vector<int> vi{ 5,6,1,0,9,7,11,4 };
	int a[] = { 5,6,1,0,9,7,11,4 };
	radix_sort(vi);

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
