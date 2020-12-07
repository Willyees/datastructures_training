#include "sort_alg.h"
#include <vector>
#include <iostream>

template<class T>
void print_vector(const std::vector<T>& v) {
	for (T e : v)
		std::cout << e << " ";
	std::cout << std::endl << "------------" << std::endl;
}
void bubble_sort(std::vector<int>&v) {
	std::cout << "Bubble sort test:" << std::endl;
	SortAlgorithms::bubbleSort(v);
	print_vector(v);
}

void selection_sort(std::vector<int>& v) {
	std::cout << "Selection sort test:" << std::endl;
	SortAlgorithms::selectionSort(v);
	print_vector(v);
}


void insertion_sort(std::vector<int>& v) {
	std::cout << "Insertion sort test:" << std::endl;
	SortAlgorithms::insertionSort(v);
	print_vector(v);
}

void merge_sort(std::vector<int>& v) {
	std::cout << "Merge sort test:" << std::endl;
	SortAlgorithms::mergeSort(v);
	print_vector(v);
}

void quick_sort(std::vector<int>& v) {
	std::cout << "Quick sort test:" << std::endl;
	SortAlgorithms::quickSort(v);
	print_vector(v);
}

template<class T>
void count_sort(std::vector<T>& v) {
	std::cout << "Count sort test:" << std::endl;
	SortAlgorithms::countSort(v);
	print_vector(v);
}

void run_all_tests() {
	//print vector unsorted
	std::cout << "unsorted vector: ";
	std::vector<int> vi{ 5,6,1,0,9,7,11,4 };
	print_vector(vi);
	bubble_sort(vi);
	selection_sort(vi);
	insertion_sort(vi);
	merge_sort(vi);
	count_sort(vi);


}

 