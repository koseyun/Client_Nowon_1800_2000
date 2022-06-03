#pragma once
class SortExamples
{
private:
	static int testCount1;
	static int testCount2;

public:
	// Bubble Sort
	static void BubbleSort(int arr[], int length);
	static void SelectionSort(int arr[], int length);
	static void InsertionSort(int arr[], int length);
	static void MergeSort(int arr[], int start, int end); // MergeSort ÀÇ ºÐÇÒ
	static void QuickSort(int arr[], int start, int end);
	static void HeapSort(int arr[], int length);

private:
	static void Merge(int arr[], int start, int end, int mid);
	static int Partition(int arr[], int start, int end);
	static void Heapify_TopDown(int arr[], int length);
	static void Heapify_BottomUp(int arr[], int length);
	static void SIFT_Up(int arr[], int root, int current);
	static void SIFT_Down(int arr[], int end, int current);
};

