#pragma once

#include "LinkedListTemplate.h"
#include <string>
using namespace std;
class HashTable
{
private:
	const int DEFAULT_SIZE;
	LinkedList<string>** _bucket;
	int _tmpHash;

public:
	HashTable();
	void Add(string value); // 인자 value 의 해시키를 구해서 해당 bucket 에 value 를 추가하는 함수
	bool ContainsKey(int key); // 해시키가 존재하는지 체크하는 함수
	bool ContainsKey(string value); // value 에 해당하는 해시키가 존재하는지 체크하는 함수
	bool ContainsValue(string value); // 인자 value 가 존재하는지 체크하는 함수
	bool RemoveKey(int key); // 인자 key 에 해당하는 bucket 을 메모리 해제 하는 함수 
	bool RemoveKey(string value); // 인자 value 에 해당하는 key 에 해당하는 bucket 을 메모리 해제하는 함수
	bool RemoveValue(string value); // 인자 value 를 메모리 해제하는 함수
	void Clear(); // 모든 bucket 메모리 해제
	void Delete(); // hashtable 메모리 해제

private:
	int Hash(string value); // 해시를 구하는 함수

};
