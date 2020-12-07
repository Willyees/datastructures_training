#pragma once
#include <vector>

//declarations
namespace SearchAlgorithms {
	//O(logN)
	template<class T>
	T* linearSearch(std::vector<T>&, T);
	
	//O(logN) vector needs to be sorted. divide and conquer
	template<class T>
	T* binarySearch(std::vector<T>&, T);

	//vector needs to be sorted. divide
	template<class T>
	T* ternarySearch(std::vector<T>&, T);
	namespace helper {
		template<class T>
		T* ternarySearch(std::vector<T>&, int l, int r, T);
	}
}

//definitions 
namespace SearchAlgorithms{
	template<class T>
	 T* linearSearch(std::vector<T>& v, T x) {
		for (int i = 0; i < v.size(); ++i) {
			if (v.at(i) == x)
				return &v.at(i);
		}
		return nullptr;
	}

	 
	 template<class T>
	 T* binarySearch(std::vector<T>& v, T x) {
		 int low = 0;
		 int high = v.size() - 1;
		 while(low < high){
			int median = (low + high) / 2;
			if (x == v.at(median))
				return &v.at(median);
			else if (x > v.at(median))
				low = median + 1;//+1 because skipping the median since, it is checked if it is == median already
			else
				high = median - 1;

		 }
		 return nullptr;
	 }
	 template<class T>
	 T* ternarySearch(std::vector<T>& v, T x) {
		 return helper::ternarySearch(v, 0, v.size(), x);
	 }

	 template<class T>
	 T* helper::ternarySearch(std::vector<T>& v, int l, int r, T x) {
		 //base case
		 if (l > r)
			 return nullptr;
		 //find the two cuts that divide the vector in 3
		 //cut1: begin array + 1/3 of the length
		 int cut1 = l + (r - l) / 3;
		 //cut2: end array - 1/3 of the length
		 int cut2 = r - (r - l) / 3;

		 if (x == v.at(cut1))
			 return &v.at(cut1);
		 if (x == cut2)
			 return &v.at(cut2);
		 if (x < v.at(cut1))
			 ternarySearch(v, l, cut1 - 1, x);
		 else if (x < v.at(cut2))
			 ternarySearch(v, cut1, cut2 - 1, x);
		 else if (x > v.at(cut2))
			 ternarySearch(v, cut2 + 1, r, x);
	 }
}
