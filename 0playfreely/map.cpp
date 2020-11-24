#pragma once
#include "headers.cpp"
#include <map>

//MAP

//Associative container. Elements stored with (key, value). Key unique. Fast retreive element. Can iterate using key order.
//Default comparison "<" std::less

//ordered map, slower than unordered: more space taken to store info
namespace tut{
	void _map(){

		//**Initialize
		std::map<char, int> m({ make_pair('c', 5), make_pair('d', 7) });
		m.clear();
		m = std::map<char, int>({ {'c', 5}, {'d', 7} });
		decltype(m) m2;
		for (auto e : m)
			cout << e.first << " => " << e.second << endl;

		//**Insertion
		m.insert(pair<char, int>('p', 15)); //O(logN)
	
		map<char, int>::iterator p_pos = m.find('p');
		m.insert(pair<char, int>('q', 12)); //O(1) amortized

		//range insertion
		m2.insert(m.begin(), m.end()); //O (Nlog(size + N)) if elements not sorted


		//**Access
		std::map<char, int>::iterator it_lower, it_upper;
		it_lower = m.lower_bound('d'); //returns first key that keycomp(element_key, k) == false. element_key is not strictly less than k (either k or higher)
		cout << it_lower->first << endl;
		it_upper = m.upper_bound('d');
		cout << it_upper->first << endl;


	
		//**Aliases
		std::map<char, int>::key_type;  //char
		std::map<char, int>::mapped_type;// int
		std::map<char, int>::size_type;	//size_t
		std::map<char, int>::value_type;//std::pair<char, int>



	}
}