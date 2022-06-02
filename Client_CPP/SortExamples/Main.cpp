#include <iostream>
#include <stdlib.h>
#include "SortExamples.h"

int main() {

	int arr1[10] = { 7, 6, 2, 4, 5, 1, 3, 9, 8, 0 };
	std::cout << "버블 소트 시작 : " << arr1 << std::endl;
	SortExamples::BubbleSort(arr1, 10);
	
	// 셀렉션 소트가 버블 소트보다 일반적으로 더 빠르다.
	// 둘다 1/2 * N^2 의 시간이 걸리지만 스왑의 총 횟수가
	// 셀렉션 소트가 적기 때문이다.
	int arr2[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	std::cout << "셀렉션 소트 시작 : " << arr2 << std::endl;
	SortExamples::SelectionSort(arr2, 10);

	int arr3[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	std::cout << "인설션 소트 시작 : " << arr3 << std::endl;
	SortExamples::InsertionSort(arr3, 10);

	int const mergeSortArrayCount = 20;
	int arr4[mergeSortArrayCount] = { 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	std::cout << "머지 소트 시작 : " << arr4 << std::endl;
	SortExamples::MergeSort(arr4, 0, mergeSortArrayCount - 1);

	for (int i = 0; i < mergeSortArrayCount; i++)
	{
		std::cout << arr4[i];
	}

	int arr5[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	std::cout << "퀵 소트 시작 : " << arr5 << std::endl;
	SortExamples::QuickSort(arr5, 0, 9);

	for (int i = 0; i < 10; i++)
	{
		std::cout << arr5[i];
	}

	int arr6[10] = { 3, 5, 9, 6, 7, 4, 8, 2, 1, 0 };

	for (int i = 0; i < 10; i++)
	{
		arr6[i] = rand() % 100;
	}

	std::cout << std::endl;

	for (int i = 0; i < 10; i++)
	{
		std::cout << arr6[i];
	}

	std::cout << std::endl;

	std::cout << "힙 소트 시작 : " << arr6 << std::endl;
	SortExamples::HeapSort(arr6, 10);

	std::cout << std::endl;
	for (int i = 0; i < 10; i++)
	{
		std::cout << arr6[i] << ", ";
	}

	return 0;
}