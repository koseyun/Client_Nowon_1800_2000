 #pragma once
#include "CObjectAPI.h"

class CAPI_Engine;
class CTexture;

class CUnit: public CObjectAPI
{
public:
	CUnit();
	virtual ~CUnit();

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
	void SetTexture(CTexture* tpTexture);

	void SetAnchors(float tAnchorX = 0.5f, float tAnchorY = 0.5f);

public:
	// �������� 2���� ���踦 �����Ѵ�
	float mX = 0.0f;
	float mY = 0.0f;

	// ������
	float mRadius = 0.0f;

	CTexture* mpTexture = nullptr;

	// pivot
	float mAnchorX = 0.5f;
	float mAnchorY = 0.5f;

	float mDisplayX = 0.0f;
	float mDisplayY = 0.0f;

	float mWidth = 0.0f;
	float mHeight = 0.0f;

};

