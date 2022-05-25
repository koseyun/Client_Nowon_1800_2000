#include <iostream>
#include "SortExamples.h"

int main() {

	int arr1[10] = { 3, 6, 2, 4, 5, 1, 7, 9, 8, 0 };
	std::cout << "버블 소트 시작 : " << arr1 << std::endl;
	SortExamples::BubbleSort(arr1, 10);

	int arr2[10] = { 7, 6, 2, 4, 5, 1, 7, 9, 8, 0 };
	std::cout << "셀렉션 소트 시작 : " << arr1 << std::endl;
	SortExamples::SelectionSort(arr2, 10);

	int arr3[10] = { 7, 6, 2, 4, 5, 1, 7, 9, 8, 0 };
	std::cout << "인설션 소트 시작 : " << arr1 << std::endl;
	SortExamples::InsertionSort(arr3, 10);


	return 0;
}