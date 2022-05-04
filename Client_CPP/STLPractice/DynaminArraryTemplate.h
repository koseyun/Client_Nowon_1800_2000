#pragma once
#include <cassert>

template <typename T>
class DynamicArray
{
private:
	T* _data;
	int _length;
	int _capacity;
	const int DEFAULT_SIZE;

public:

	int Length();
	void Add(T item);
	int Find(T item);
	bool IsExist(T item);
	bool Remove(T item);
	bool RemoveAt(int index);
	void Delete();
	T* GetData();

	DynamicArray();
	~DynamicArray();

	T& operator[] (int index) {
		if (index < 0 &&
			index >= _length) {
			throw "배열 인덱스가 허용범위를 넘어섰습니다";
		}
		return _data[index];
	}

public:
	// inner class
	class Iterator
	{
	public:
		DynamicArray* p_DA;
		T* p_Data;
		int _idx;
	public:
		T& operator * () {
			return p_Data[_idx];
		}

		Iterator& operator ++() {

			// Dynamic Array 의 데이터 주소와 Iterator 가 가지고 있는 데이터 주소가 동일한지
			if ((p_DA == nullptr) ||
				(p_DA->_data != p_Data) ||
				(_idx < 0))
			{
				assert(nullptr);
			}

			// Iterator 의 데이터가 마지막 요소 이상일 경우 end 취급
			if (_idx < p_DA->_length - 1) {
				++_idx;
			}
			else {
				_idx = -1;
			}
			return *this;
		}

		Iterator operator++(int) {
			Iterator tmpIter = *this;
			++(*this);
			return tmpIter;
		}

		bool operator < (const Iterator& other) {
			// this 가 end 일때
			if (_idx < 0)
				return false;

			// other 가 end 일때
			if (other._idx < 0)
				return true;


			// 둘다 end 가 아닐때
			if (_idx < other._idx &&
				p_DA->_data == other.p_DA->_data)
				return true;
			return false;
		}

		bool operator == (const Iterator& other) {
			if (p_DA->_data == other.p_DA->_data &&
				_idx == other._Idx)
				return true;
			return false;
		}

		bool operator != (const Iterator& other) {
			return !(* this == other)
		}

		Iterator()
			: p_DA(nullptr)
			, p_Data(nullptr)
			, _idx(-1)
		{
		}

		Iterator(DynamicArray* da, T* data, int index)
			: p_DA(da)
			, p_Data(data)
			, _idx(index)
		{
			if (data == nullptr)
				index = -1;
		}
	};
public:
	DynamicArray<T>::Iterator Begin();
	DynamicArray<T>::Iterator End();

};

template <typename T>
int DynamicArray<T>::Length() {
	return _length;
}

template<typename T>
inline void DynamicArray<T>::Add(T item)
{
	// 배열의 크기가 충분하지 않으면 현재 길이의 두배로 늘린다.
	if (_length >= _capacity) {
		_capacity *= 2;
		T* tmp = new T[_capacity];
		for (int i = 0; i < _length; i++)
			tmp[i] = _data[i];
		delete[] _data;
		_data = new T[_capacity];
		for (int i = 0; i < _length; i++)
			_data[i] = tmp[i];
		delete[] tmp;
	}
	_data[_length] = item;
	_length++;
}

template<typename T>
inline int DynamicArray<T>::Find(T item)
{
	for (int i = 0; i < _length; i++)
	{
		if (_data[i] == item)
			return i;
	}
	return -1;
}

template<typename T>
inline bool DynamicArray<T>::IsExist(T item)
{
	for (int i = 0; i < _length; i++)
	{
		if (_data[i] == item)
			return true;
	}
	return false;
}

template<typename T>
inline bool DynamicArray<T>::Remove(T item)
{
	for (int i = 0; i < _length; i++)
	{
		if (_data[i] == item)
			return RemoveAt(i);
	}
	return false;
}


template<typename T>
inline bool DynamicArray<T>::RemoveAt(int index)
{
	if (index < _length) {
		for (int i = index; i < _length - 1; i++)
		{
			_data[i] = _data[i + 1];
		}
		_length--;
		return true;
	}

	return false;
}

template<typename T>
inline void DynamicArray<T>::Delete()
{
	delete[] _data;
}

template<typename T>
inline T* DynamicArray<T>::GetData()
{
	return _data;
}

template<typename T>
DynamicArray<T>::DynamicArray()
	:DEFAULT_SIZE(1)// 이니셜라이저, 생성자 함수 내용 실행 전에 멤버 초기화를 할떄 사용한다.
{
	_length = 0;
	_capacity = DEFAULT_SIZE;
	_data = new T[_capacity];
}

template<typename T>
DynamicArray<T>::~DynamicArray()
{
}

template<typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::Begin()
{
	return DynamicArray<T>::Iterator(this, _data, 0);
}

template<typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::End()
{
	return DynamicArray<T>::Iterator(this, _data, -1);
}
