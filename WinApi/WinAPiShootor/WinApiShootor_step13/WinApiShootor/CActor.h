#pragma once

#include "CUnit.h"


#include <vector>
using namespace std;

class CBullet;

class CActor: public CUnit
{
public:
	CActor();
	CActor(const CActor& tActor);
	virtual ~CActor();

public:
	virtual CObjectRyu* clone() override
	{
		return new CActor(*this);
	}


public:
	void DoFire(vector<CBullet*>& tBullets);


	virtual void Update(float tDeltaTime) override;

private:
	int mCurIndexBullet = 0;
};

