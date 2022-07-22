#pragma once
#include "CUnit.h"
#include <vector>
using namespace std;

class CBullet;

class CActor: public CUnit
{
public:
	CActor();
	virtual ~CActor();

	CActor(const CActor& t);
	
public:
	// API prototype
	virtual CObjectAPI* cloan() override
	{
		return new CActor(*this);
	}

public:
	virtual void Update(float tDeltaTime) override;
	void DoFire(vector<CBullet*>& tBullets);

public:
	int mCurIndexBullet = 0;

};

