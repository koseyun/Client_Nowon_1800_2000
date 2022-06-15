#pragma once

class CAPI_Engine;

class CUnit
{
public:
	CUnit();
	~CUnit();

	// ���������
	CUnit(const CUnit& tUnit)
	{
		mX = tUnit.mX;
		mY = tUnit.mY;
		mRadius = tUnit.mRadius;
	}

	// ������Կ�����
	void operator = (const CUnit& tUnit)
	{
		mX = tUnit.mX;
		mY = tUnit.mY;
		mRadius = tUnit.mRadius;
	}

public:
	void Render(CAPI_Engine* tpEngine);


public:
	// �������� 2���� ���踦 �����Ѵ�
	float mX = 0.0f;
	float mY = 0.0f;

	// ������
	float mRadius = 0.0f;


};

