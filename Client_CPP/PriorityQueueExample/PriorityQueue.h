#pragma once
#include <iostream>

#define INIT_SIZE 10
using namespace std;

template <typename T>
class PriorityQueue {

public:
	PriorityQueue();
	~PriorityQueue();
	void Enqueue(const T& data);
	T& Dequeue();
	void PrintData();

private:
	T* _heap;
	int _size;
	int _capacity;
};

template<typename T>
inline PriorityQueue<T>::PriorityQueue()
{
	_heap = new T[INIT_SIZE];
	_size = 0;
	_capacity = INIT_SIZE;
}

template<typename T>
inline PriorityQueue<T>::~PriorityQueue()
{
	delete _heap;
}

template<typename T>
inline void PriorityQueue<T>::Enqueue(const T& data)
{
	if (_size >= _capacity)
	{
		_capacity = _size * 2;
		T* tmpHeap = new T[_capacity];
		for (int i = 0; i < _size; i++)
			tmpHeap[i] = _heap[i];
		delete _heap;

		_heap = new T[_capacity];
		for (int i = 0; i < _capacity; i++)
			_heap[i] = tmpHeap[i];
		delete tmpHeap;
	}
	_heap[_size] = data;

	int parent = _size / 2;
	int child = _size;

	// 밑에서 위로 정렬 (SIFT - UP)
	while (_heap[parent] < _heap[child])
	{
		T tmpData = _heap[parent];
		_heap[parent] = _heap[child];
		_heap[child] = tmpData;

		child = parent;
		parent = child / 2;
	}

	_size++;
}

template<typename T>
inline T& PriorityQueue<T>::Dequeue()
{
	T top = _heap[0];
	_heap[0] = _heap[_size - 1];

	int parent = 0;
	int child = parent * 2 + 1;
	int doSwap = false;

	// 위에서 아래로 정렬 (SIFT - DOWN)
	while (child < _size - 1)
	{
		// 왼쪽 자식노드 vs 오른쪽 자식노드 중 큰걸로 비교할거임
		if ((child + 1) < (_size - 1) &&
			_heap[child] < _heap[child + 1])
			child++;

		// 자식보다 부모가 작으면 스왑할거임
		if (_heap[parent] < _heap[child])
		{
			doSwap = true;
		}

		if (doSwap)
		{
			T tmpData = _heap[parent];
			_heap[parent] = _heap[child];
			_heap[child] = tmpData;
			doSwap = false;

			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}

	_size--;
	return top;
}

template<typename T>
inline void PriorityQueue<T>::PrintData()
{
	cout << "Prioriry Queue Elements: ";
	for (int i = 0; i < _size; i++)
		cout << _heap[i];
	cout << endl;
}