#include "HashTable.h"
#include "LinkedListTemplate.h"
HashTable::HashTable()
	: DEFAULT_SIZE(100)
{
	*_bucket = new LinkedList<string>[DEFAULT_SIZE];
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
	return false;
}

bool HashTable::ContainsKey(string value)
{
	return false;
}

bool HashTable::ContainsValue(string value)
{
	return false;
}

bool HashTable::RemoveKey(int key)
{
	return false;
}

bool HashTable::RemoveKey(string value)
{
	return false;
}

bool HashTable::RemoveValue(string value)
{
	return false;
}

bool HashTable::Clear()
{
	return false;
}

bool HashTable::Delete()
{
	return false;
}

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
