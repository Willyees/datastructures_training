#pragma once
#include <vector>
#include <alg.h>
#include <assert.h>
#include <algorithm>

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
void countSort(std::vector<T>&);
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
				v[j - 1] = temp;
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