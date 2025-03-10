#pragma once
#include <vector>
#include <alg.h>
#include <assert.h>
#include <algorithm>
#include "binary_heap.h"
#include "array.h"
#include <string>
#include <sstream>

//declarations
namespace SortAlgorithms {
template<class T>
	void bubbleSort(std::vector<T>&); //O(N^2)

template<class T>
	void selectionSort(std::vector<T>&);//O(N^2)

template<class T>
void insertionSort(std::vector<T>&);//O(N^2) worst case

template<class T>
void mergeSort(std::vector<T>&);//O(NlogN)

template<class T>
void quickSort(std::vector<T>&);

template<class T>
void countSort(std::vector<T>&);//O(N + K). N: v K: v1(length: max(v)); O(N + max(v))

template<class T>
void bucketSort(std::vector<T>&);

//T not very flexible: each type of data might need a different radix sort ~ check this
template<class T>//O((N + B) * logb(maxx))
void radixSort(std::vector<T>&);
}


//definitions
namespace SortAlgorithms{
template<class T>
	void bubbleSort(std::vector<T>& v) {
		for (int i = 0; i < v.size(); ++i) {
			for (int k = 0; k < v.size() - i - 1; ++k) {//- 1 because accessing next item in the same iteration of previous index
				if (v[k] > v[k + 1]) {
					//swap
					T temp = v[k];
					v[k] = v[k + 1];
					v[k + 1] = temp;
				}
			}
		}
	}


template<class T>
	void selectionSort(std::vector<T>& v) {
		//find min and max
		size_t min = 0;//indexes
		size_t max = 0;
		for(int j = 0; j < v.size(); ++j){
			for (int i = j; i < v.size() - j; ++i) {
				//get min
				if (v[i] < v[min])
					min = i;
				if (v[i] > v[max])
					max = i;
			}
			//swap min and max with min and max correct positions
			T min_temp = v[j];
			T max_temp = v[v.size() - j - 1];
			v[j] = v[min];
			v[v.size() - j - 1] = v[max];
			v[min] = min_temp;
			v[max] = max_temp;
		}
	}

template<class T>
	void insertionSort(std::vector<T>& v) {
		for (int i = 1; i < v.size(); ++i) {
			
			T temp = v[i];
			int j = i;//index for the current element being moved behind until is at the correct position
			while (j > 0 && v[j] < v[j - 1]) {
				//move previous element forward of one position
				/*v[j - 1] = temp;
				j--;*/
				v[j] = v[j - 1];
				j--;
			}
			v[j] = temp;//moving the element at old position j to its correct position. doing it outside while becasue is only needed to be swapped once
		}
	}
	namespace helper {
		
		//usual implementations remove items from the vectors and check if it is empty
		template<class T>
		std::vector<T> merge(std::vector<T> v1, std::vector<T> v2) {
			//merge and order the two vectors
			std::vector<T> f;
			size_t v1_i = 0, v2_i = 0;
			//check items in both vectors and push them in order in a new array
			while (v1_i < v1.size() && v2_i < v2.size()) {
				if(v1[v1_i] < v2[v2_i]){
					f.push_back(v1[v1_i]);
					++v1_i;
				}
				else {
					f.push_back(v2[v2_i]);
					++v2_i;
				}
			}
			//either v1 or v2 has arrived at the end
			while (v1_i < v1.size())
				f.push_back(v1[v1_i++]);

			while (v2_i < v2.size())
				f.push_back(v2[v2_i++]);




			return f;
		}


		//beg: first index, end: last index
		//mergesort used to recursively call and merge different chunks of the original list
		template<class T>
		std::vector<T> mergeSort(std::vector<T>& v, size_t beg, size_t end) {
			if (beg == end)
				return std::vector<T> {v[beg]};
			std::vector<T> v1 = mergeSort(v, beg, (beg + end) / 2);
			std::vector<T> v2 = mergeSort(v, (beg + end + 1) / 2, end);
			return merge(v1, v2);

		}

		
	}

	template<class T>
	void mergeSort(std::vector<T>& v) {
		v = helper::mergeSort(v, 0, v.size() - 1);
	}

	namespace helper {
		//return random index denoting the pivot chosen. swap pivot with first element and rearrange the others 
		template<class T>
		size_t partition(std::vector<T>& v, size_t beg, size_t end) { //O(N)
			size_t pivot_i = beg + rand() % (end - beg + 1); //adding beg because the minimum random have to be beg.
														   //% (end - beg + 1) the maximum random have to be end - beg, because it is added + beg before, so it must not be exceeded the max
			T pivot = v[pivot_i];
			//swap pivot with first element
			std::swap(v[pivot_i], v[0]); //could also use: std::iter_swap(v.begin(), v.begin() + pivot);
			
			size_t low_i = 0;//is the index of the latest moved element (element < pivot)
			for (int i = 1; i <= end; ++i) {//keeping all the elements < pivot at the beginning of the vector
				if (v[i] < pivot) {//checking if the current element is lower than the pivot, if so move it at beginning of the vector after the latest added low element
					std::swap(v[i], v[low_i + 1]);
					++low_i;
				}
			}
			std::swap(v[0], v[low_i]);//swapping the pivot stored in the first position with the latest moved low element
			
			return pivot_i;
		}

		template<class T>
		void quickSort(std::vector<T>& v, size_t beg, size_t end) {
			if (beg >= end)//stop when start index is the same as the end (1 element) or > end (in case pivot chosen is the end of the vector)
				return;
			size_t pivot = partition(v, beg, end);
			quickSort(v, beg, pivot - 1);
			quickSort(v, pivot + 1, end);	
		}
	}
	template<class T>
	void quickSort(std::vector<T>& v) {
		helper::quickSort(v, 0, v.size() - 1);
	}

	namespace helper{
		template<class T>
		size_t get_max(std::vector<T>& v) {
			size_t index = 0;
			T max = v[index];
			for (int i = 0; i < v.size(); ++i)
				if(v[i] > max){
					index = i, max = v[i];
				}
			return index;
		}
	}

	template<class T>
	void countSort(std::vector<T>& v) {
		T max_e = *std::max_element(v.begin(), v.end());//or use the helper::get_max, both O(N)
		std::vector<int> v1((size_t) max_e + 1);
		for (int i = 0; i < v.size(); ++i) {
			v1[(size_t)v[i]]++;
		}

		auto v_it = v.begin();
		for (int i = 0; i < v1.size(); ++i) {
			while(v1[i] != 0){ //there is at least one element, keep looping until none are left.
				*v_it = (T) i;
				v1[i]--;
				++v_it;
			}
		}

	}

	
	//load the vector in a binary heap. reinforce the max-heap property (parent > both children) looping from the last parent upwards.
	//swap root heap with last element, remove the old root and heapify (trickledown) the new root
	//all the removed values form the ordered vector
	template<class T>
	void heapSort(std::vector<T>& v) {
		Array<T> a(&v[0], v.size());
		BinaryHeap<T>::sort(a);
		a.d_print_structure_a();
		std::copy(a.get_pos(), a.get_pos() + a.size, &v[0]);
	}

	namespace helper {
		int hash(int e, int size);
	}

	template<class T>
	void bucketSort(std::vector<T>& v) {
		std::vector<std::vector<T>> b(v.size());
		for (int i = 0; i < v.size(); ++i) {
			b[helper::hash(v[i], b.size())].push_back(v[i]);
		}
		//sort each bucket 
		int v_index = 0;
		for (int i = 0; i < b.size(); ++i) {
			if (b[i].empty())
				continue;
			insertionSort(b[i]);
			for (int j = 0; j < b[i].size(); ++j)
				v[v_index++] = b[i][j];
		}
	}
	namespace helper {
		//place: index posiotion used to compare the elements in v (xes: one's: 0, ten's: 1, hundred's: 2, etc..)
		//size: frequencies array size (in radixsort is dictated by the number of different possible elements, xes: uinteger: 10 {0..9})
		//it uses a frequencies vector that is loaded with the values from v and set them in the correct freq[index] based on the place specified. could directly input the values in a vector(size:v.size) but much more space than frequencies
		template<class T>
		void radixCountSort(std::vector<T>& v, int place, int size) {
			std::vector<int> frequencies(size, 0);
			for (int i = 0; i < v.size(); ++i) {
				const std::string s_temp = std::to_string(v[i]);
				if (s_temp.size() - 1 < place)//element has not enough values as the maxx element, it will be put in frequencies[0]
					frequencies[0]++;
				else {
					std::stringstream s_stream;
					s_stream << s_temp[s_temp.size() - place - 1];
					int index;
					s_stream >> index;
					frequencies[index]++;//this wont work unless T is integer. todo: group of functions to transform to integer
				}
			}
			std::vector<T> auxiliary(v.size());
			//update the frequencies to reflect the index where the item stored in the frequency should be put in the auxiliary array
			//- 1 because vector is 0 based (this just fixes the positions). for example first element (1) should be in the frequency[0] = 1 - 0 = 0, which is the position that should be put in auxiliary
			frequencies[0] -= 1;
			for (int i = 1; i < frequencies.size(); ++i) {
				frequencies[i] += frequencies[i - 1];
			}
			
			for (int i = v.size() - 1; i >=0; --i) {
				std::string s_temp = std::to_string(v[i]);
				if (s_temp.size() - 1 < place) {//element has not enough values as the maxx element, it will be put in frequencies[0]
					auxiliary[frequencies[0]] = v[i];
					frequencies[0]--;
				}
				else{
					std::stringstream s_stream;
					int index_f;
					s_stream << s_temp[s_temp.size() - place - 1];
					s_stream >> index_f;
					auxiliary[frequencies[index_f]] = v[i];
					frequencies[index_f]--;
				}
			}
			//copy it back in the input vector
			std::copy(auxiliary.begin(), auxiliary.end(), v.begin());
		}
	}

	template<class T>
	void radixSort(std::vector<T>& v) {
		//find the maximum number of digits
		//std::max_element(v.begin(), b.end());
		T max = v[0];
		for (int i = 1; i < v.size(); ++i) {//could do this while calculating first ones's iteration
			if (v[i] > max) max = v[i];
		}
		//count the values in max
		std::string s = std::to_string(max);
		int maxx = s.size();

		for (int i = 0; i <= maxx; ++i) {
			helper::radixCountSort(v, i, 10);//hardcoding 10 for integer sizes
		}
	}

}


//tests
template<class T>
void print_vector(const std::vector<T>&);
void run_all_tests();
void bubble_sort(std::vector<int>&);
void insertion_sort(std::vector<int>&);
void merge_sort(std::vector<int>&);
void quick_sort(std::vector<int>&);
template<class T>
void count_sort(std::vector<T>&);
template<class T>
void heap_sort(std::vector<T>&);
void bucket_sort(std::vector<int>&);
void radix_sort(std::vector<int>&);