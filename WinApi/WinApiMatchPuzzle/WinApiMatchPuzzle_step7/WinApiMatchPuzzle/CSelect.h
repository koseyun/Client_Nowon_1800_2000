#pragma once
#include "CUnit.h"

class CSelect: public CUnit
{
public:
	CSelect()
	{

	}
	virtual ~CSelect() // ����Ҹ���
	{

	}
	CSelect(const CSelect& t): CUnit(t)
	{

	}

	void operator=(const CSelect& t)
	{
		CUnit::operator=(t);
	}

public:
	virtual CObjectAPI * clone() override
	{
		return new CSelect(*this);
	};

};
