#include "HashTable.h"
#include "LinkedListTemplate.h"

HashTable::HashTable()
	: DEFAULT_SIZE(100)
{
	/*int arr[100];
	int* a = arr;*/
	_bucket = new LinkedList<string>*[DEFAULT_SIZE];
	for (int i = 0; i < DEFAULT_SIZE; i++)
		_bucket[i] = nullptr;

	_tmpHash = 0;
}

void HashTable::Add(string value)
{
	_tmpHash = Hash(value); // 추가하려는 value 의 해시 구하기

	// bucket 내에 해당 해시에 대한 링크드리스트가 없으면 생성
	if (_bucket[_tmpHash] == nullptr)
		_bucket[_tmpHash] = new LinkedList<string>();

	_bucket[_tmpHash]->AddLast(value); // bucket 내에 해당 해시에 해당하는 링크드리스트에 인자 추가.
}

bool HashTable::ContainsKey(int key)
{
	if ((_bucket[key] == nullptr) ||
		(key >= DEFAULT_SIZE - 1))
		return false;
	else
		return true;
}

bool HashTable::ContainsKey(string value)
{
	return ContainsKey(Hash(value));
}

bool HashTable::ContainsValue(string value)
{
	int key = Hash(value); // 인자에 대한 해시 키 구함

	// 버킷에 해당 키 링크드리스트가 있으면
	if (_bucket[key] != nullptr) {
		// 링크드리스트에서 인자 검색후 없으면 false, 있으면 true 반환
		return (&_bucket[key]->Find(value) == nullptr) ? false : true;
	}
	return false;
}

bool HashTable::RemoveKey(int key)
{
	// 인자 키에 해당하는 링크드리스트가 있으면
	if (_bucket[key] != nullptr) {
		_bucket[key]->Delete(); // 링크드리스트의 노드들 해제
		delete _bucket[key]; // 링크드리스트 해제
		return true;
	}

	return false;
}

bool HashTable::RemoveKey(string value)
{
	return RemoveKey(Hash(value));
}

bool HashTable::RemoveValue(string value)
{
	int key = Hash(value);  // 인자로 해시 구함

	// 해당 키의 링크드리스트가 있으면
	if (_bucket[key] != nullptr) {

		// 인자와 같은 데이터를 가진 노드 삭제
		bool isRemoved = _bucket[key]->RemoveLast(value);

		// 삭제했는데 링크드리스트의 노드가 없으면 링크드리스트 해제
		if (isRemoved &&
			_bucket[key]->Count() <= 0)
			delete _bucket[key];

		return isRemoved;
	}
	return false;
}

void HashTable::Clear()
{
	for (int i = 0; i < DEFAULT_SIZE; i++)
	{
		if (_bucket[i] != nullptr)
		{
			_bucket[i]->Delete();
			delete _bucket[i];
		}
	}
}

void HashTable::Delete()
{
	Clear();
	delete[] _bucket;
}
// 충돌을 더 줄일 수 있는 추가 패턴 예시(일정 자릿수 까지 10승수 곱함)
//hollow
//_tmpHash += h;
//_tmpHash += o * 10;
//_tmpHash += l * 10^2;
//_tmpHash += l * 10^3;
//_tmpHash += o * 10^4;
//_tmpHash += w;
//...
int HashTable::Hash(string value)
{
	_tmpHash = 0;
	for (int i = 0; i < value.length(); i++)
	{
		_tmpHash += value[i];
	}
	_tmpHash %= DEFAULT_SIZE;
	return _tmpHash;
}
