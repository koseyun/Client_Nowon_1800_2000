#pragma once
template <typename T>
class DynamicArrary
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

	DynamicArrary();
	~DynamicArrary();
};

template <typename T>
int DynamicArrary<T>::Length() {
	return _length;
}

template<typename T>
inline void DynamicArrary<T>::Add(T item)
{
	// �迭�� ũ�Ⱑ ������� ������ ���� ������ �ι�� �ø���.
	if (_length >= _capacity) {
		_capacity *= 2;
		T* tmp = new T[_capacity];
		for (int i = 0; i < _length; i++)
			tmp[i] = _data[i];
		delete[] _data;
		_data = new int[_capacity];
		for (int i = 0; i < _length; i++)
			_data[i] = tmp[i];
		delete[] tmp;
	}
	_data[_length] = item;
	_length++;
}

template<typename T>
inline int DynamicArrary<T>::Find(T item)
{
	for (int i = 0; i < _length; i++)
	{
		if (_data[i] == item)
			return i;
	}
	return -1;
}

template<typename T>
inline bool DynamicArrary<T>::IsExist(T item)
{
	for (int i = 0; i < _length; i++)
	{
		if (_data[i] == item)
			return true;
	}
	return false;
}

template<typename T>
inline bool DynamicArrary<T>::Remove(T item)
{
	for (int i = 0; i < _length; i++)
	{
		if (_data[i] == item)
			return RemoveAt(i);
	}
	return false;
}

template<typename T>
bool DynamicArrary<T>::RemoveAt(int index)
{
	if (index >= _length) {
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
inline void DynamicArrary<T>::Delete()
{
	delete[] _data;
}

template<typename T>
DynamicArrary<T>::DynamicArrary()
	: DEFAULT_SIZE(1)// �̴ϼȶ�����, ������ �Լ� ���� ���� ���� ��� �ʱ�ȭ�� �Ҷ� ����Ѵ�.
{
	_length = 0;
	_capacity = DEFAULT_SIZE;
	_data = new int[_capacity];
}

template<typename T>
DynamicArrary<T>::~DynamicArrary()
{

}