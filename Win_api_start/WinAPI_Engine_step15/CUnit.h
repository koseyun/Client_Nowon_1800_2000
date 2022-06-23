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
		mPosition.mX = tUnit.mPosition.mX;
		mPosition.mY = tUnit.mPosition.mY;
		mRadius = tUnit.mRadius;
	}

	// ������Կ�����
	void operator = (const CUnit& tUnit)
	{
		mPosition.mX = tUnit.mPosition.mX;
		mPosition.mY = tUnit.mPosition.mY;
		mRadius = tUnit.mRadius;
	}

public:
	void Render();
	void SetTexture(CTexture* tpTexture);

	void SetAnchors(float tAnchorX = 0.5f, float tAnchorY = 0.5f);

	void SetVelocity(SVector2D tVelocity)
	{
		mVelocity = tVelocity;
	}
	SVector2D GetVelocity() const
	{
		return mVelocity;
	}

	void SetPosition(SVector2D tPosition)
	{
		mPosition = tPosition;
	}
	SVector2D GetPosition() const
	{
		return mPosition;
	}

	void Update();
	void SetEngine(CAPI_Engine* tpEngine)
	{
		mpEngine = tpEngine;
	}

public:
	// �������� 2���� ���踦 �����Ѵ�
	//float mX = 0.0f;
	//float mY = 0.0f;

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

	SVector2D mVelocity;

	CAPI_Engine* mpEngine = nullptr;

};

