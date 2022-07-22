#pragma once
#include "CUnit.h"

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

};

