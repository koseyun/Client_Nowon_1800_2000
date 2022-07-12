#pragma once
#include "APIMacro.h"
#include<list>
using namespace std;

class CUnit;

class CCollisionMgr
{
private:
	// ��� ���ֿ� ���� ��ȸ�� �ؾ��Ѵ�
	// ���ֵ��� �� �ڷᱸ���� ����ϰ� �����ϴ� ���� ����ϴ�
	// <-- �̷��� Ư���� ��ũ�帮��Ʈ�� �����ϴ�
	// �ֳ��ϸ�, ��ũ�帮��Ʈ�� �߰������� �ɸ��� �ð��� O(1)�̴� 
	list<CUnit*> mCollisionUnits;

public:
	void AddUnit(CUnit* t);
	void Update(float tDeltaTime);

private:
	bool DoCollision(CUnit* tThis, CUnit* tOther);

	
	// �̱��� ���� ����

	SINGLETON_DECLARE(CCollisionMgr)
};

