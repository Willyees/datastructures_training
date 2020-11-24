#include <unordered_map>
#include "headers.cpp"

namespace tut {

	size_t f_hash(int i) {
		return i;
	}

	void _hash_map() {

		//**Initialization
		std::unordered_map<char, int> u_map { std::pair<char, int>('c', 5) };
		u_map.insert(std::pair<char, int>('d', 5));
		
		cout << u_map.begin()->first << endl; //first: key
		cout << (u_map.begin())->second << endl; //second: value

		
		//**HASH
		//Default using std::hash<Key>. Returns size_t index of the key. Unique with low probability of collision
		std::hash<char> h;
		cout << "index of key \"c\": " << h('c') << endl;;
		cout << "prob collision hash default function: " << 1.0 / std::numeric_limits<size_t>::max() << endl;
		std::unordered_map<char, int, size_t(*)(int)> h1(10, f_hash); //using function pointer

		//**Aliases
		std::unordered_map<char, int>::hasher;//type of hash function used. default: hash<char>
		
		
		assert(true);
	}

	
}