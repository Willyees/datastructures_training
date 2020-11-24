#include <iostream>
#include <vector>
#include "objs.h"
#include <assert.h>
#include <vector>
#include <deque>
#include <stack>
#include <queue>
#include <map>
#include "excercises.h"

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
int main() {

	cout << ex::str_parenthesis_is_balanced("{()()") << endl;
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
