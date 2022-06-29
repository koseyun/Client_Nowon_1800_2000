#pragma once
#include "CUnit.h"
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

public:
	virtual void Update(float tDeltaTime) override;
	void DoFire(vector<CBullet*>& tBullets);

public:
	int mCurIndexBullet = 0;

public:
	// delta time �� ������ ����
	float mTimeTick = 0.0f;

};
