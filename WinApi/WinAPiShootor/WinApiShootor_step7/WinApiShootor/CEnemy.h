#pragma once
#include "CUnit.h"
#include <windows.h>
#include <vector>
using namespace std;

class CBullet;

class CEnemy:public CUnit
{
public:
	CEnemy();
	virtual ~CEnemy();

	CEnemy(const CEnemy& t);

public:
	// API prototype
	virtual CObjectAPI* clone() override
	{
		return new CEnemy(*this);
	}

	// �����ο��� �浹������ �����ϰ� �������� �̿��ؼ� �������α׷� ����������
	// ���ϴ� CUnit ������ Ŭ��������
	// OnEnterCollision, OnStayCollision, OnExitCollision ���� ��Ȳ�� �°� �����Ͽ� ����ϸ� �ȴ�
	virtual void OnEnterCollision(CCollider* tOther) override
	{
		OutputDebugString(L"CEnemy::OnEnterCollision\n");

		/*this->SetIsActive(false);
		((CUnit*)tOther->GetOwnerObject())->SetIsActive(false);*/
	}

	virtual void OnExitCollision(CCollider* tOther) override
	{
		OutputDebugString(L"CEnemy::OnExitCollision\n");

		this->SetIsActive(false);
		((CUnit*)tOther->GetOwnerObject())->SetIsActive(false);
	}

public:
	virtual void Update(float tDeltaTime) override;
	void DoFire(vector<CBullet*>& tBullets);
	void DoFireAimed(vector<CBullet*>& tBullets, CObjectAPI* tpObject);
	void DoFireCircled(vector<CBullet*>& tBullets);

public:
	int mCurIndexBullet = 0;

public:
	// delta time �� ������ ����
	float mTimeTick = 0.0f;

};
