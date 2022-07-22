#pragma once


#include "CUnit.h"


#include <vector>
using namespace std;


#include <windows.h>

//���⼭�� �׳� CBullet�� �̿��غ� ���ε�, ���� Ŭ������ �ϳ� �� ���� ������� �״�.
class CBullet;



class CEnemy : public CUnit
{
public:
	CEnemy();
	CEnemy(const CEnemy& tActor);
	virtual ~CEnemy();

public:
	virtual CObjectRyu* clone() override
	{
		return new CEnemy(*this);
	}

	virtual void OnEnterCollision(CCollider* tOther) override 
	{
		if (tOther->GetOwnerObject()->GetTag() == "tagActorBullet")
		{

			OutputDebugString(L"CEnemy::OnEnterCollision\n");

			this->SetIsActive(false);
			((CUnit*)tOther->GetOwnerObject())->SetIsActive(false);
		}
	};

	virtual void OnExitCollision(CCollider* tOther) override
	{

		if (tOther->GetOwnerObject()->GetTag() == "tagActorBullet")
		{

			OutputDebugString(L"=====CEnemy::OnExitCollision\n");

			//this->SetIsActive(false);
			//((CUnit*)tOther->GetOwnerObject())->SetIsActive(false);
		}
	};


public:
	void DoFire(vector<CBullet*>& tBullets);
	void DoFireAimed(vector<CBullet*>& tBullets, CObjectRyu* tpObject);

	//ryu_circled
	void DoFireCircled(vector<CBullet*>& tBullets);

	virtual void Update(float tDeltaTime) override;


private:
	int mCurIndexBullet = 0;


public:
	float mTimeTick = 0.0f;
};

