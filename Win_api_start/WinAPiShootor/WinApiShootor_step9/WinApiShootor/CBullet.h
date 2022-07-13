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
	virtual CObjectAPI* clone() override
	{
		return new CBullet(*this);
	}
};

