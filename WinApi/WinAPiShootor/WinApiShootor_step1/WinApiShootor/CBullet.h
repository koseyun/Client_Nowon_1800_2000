#pragma once
#include "CUnit.h"

class CBullet: public CUnit
{
public:
	CBullet();
	virtual ~CBullet();
	CBullet(const CBullet& t);

public:
	// API prototype
	virtual CObjectAPI* cloan() override
	{
		return new CBullet(*this);
	}
};

