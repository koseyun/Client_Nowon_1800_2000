#include "DynamicArrary.h"

int DynamicArrary::Length()
{
	return _length;
}

void DynamicArrary::Add(int item)
{
	// �迭�� ũ�Ⱑ ������� ������ ���� ������ �ι�� �ø���.
	if (_length >= _capacity) {
		_capacity *= 2;
		int* tmp = new int[_capacity];
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

/// <summary>
/// ������ �˻� ������ �ش� ������ �ε��� ��ȯ , ���н� -1 ��ȯ
/// </summary>
int DynamicArrary::Find(int item)
{
	for (int i = 0; i < _length; i++)
	{
		if (_data[i] == item)
			return i;
	}
	return -1;
}

// Camel case : �� �ܾ��� ���� ���ĺ��� �빮�ڷ� ǥ���ϴ� ���
// ���� �����̸� ���� ���ĺ��� �ҹ���, �׿� �빮�� ǥ����

bool DynamicArrary::IsExist(int item)
{
	for (int i = 0; i < _length; i++)
	{
		if (_data[i] == item)
			return true;
	}
	return false;
}

/// <summary>
/// Ư�� �������� ����� �Լ�
/// ����µ� �����ϸ� true, �����ϸ� false ��ȯ
/// </summary>
bool DynamicArrary::Remove(int item)
{
	for (int i = 0; i < _length; i++)
	{
		if (_data[i] == item)
			return RemoveAt(i);
	}
	return false;
}

/// <summary>
/// Ư�� �ε����� ����� �Լ�
/// ����µ� �����ϸ� true, �����ϸ� false ��ȯ
/// </summary>
bool DynamicArrary::RemoveAt(int index)
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

void DynamicArrary::Delete()
{
	delete[] _data;
}

DynamicArrary::DynamicArrary()
	: DEFAULT_SIZE(1)// �̴ϼȶ�����, ������ �Լ� ���� ���� ���� ��� �ʱ�ȭ�� �Ҷ� ����Ѵ�.
{
	_length = 0;
	_capacity = DEFAULT_SIZE;
	_data = new int[_capacity];
}

DynamicArrary::~DynamicArrary()
{

}
