#pragma once

#include "CUnit.h"

class CBullet: public CUnit
{
public:
	CBullet();
	CBullet(const CBullet& tActor);
	virtual ~CBullet();

	virtual CObjectRyu* clone() override
	{
		return new CBullet(*this);
	}
};

