#pragma once.
#include "CUnit.h"

class CPiece: public CUnit
{
public:
	CPiece()
	{

	}
	virtual ~CPiece() // ����Ҹ���
	{

	}
	CPiece(const CPiece& t): CUnit(t)
	{

	}

	void operator=(const CPiece& t)
	{
		CUnit::operator=(t);
	}

public:
	virtual CObjectAPI* clone() override
	{
		return new CPiece(*this);
	};

};

