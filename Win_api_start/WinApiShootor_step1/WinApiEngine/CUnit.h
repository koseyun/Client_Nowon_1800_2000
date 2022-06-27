 #pragma once
#include "CObjectAPI.h"

class CAPI_Engine;
class CTexture;

class CUnit: public CObjectAPI
{
public:
	CUnit();
	virtual ~CUnit();

	// 복사생성자
	CUnit(const CUnit& t)
	{
		// CObjectAPI
		mPosition = t.mPosition;

		// CUnit
		mRadius = t.mRadius;

		mAnchorX = t.mAnchorX;
		mAnchorY = t.mAnchorY;

		mDisplayX = t.mDisplayX;
		mDisplayY = t.mDisplayY;

		mWidth = t.mWidth;
		mHeight = t.mHeight;

		mVelocity = t.mVelocity;

		// shallow copy
		mpTexture = t.mpTexture;
		mpEngine = t.mpEngine;
	}

	// 복사대입연산자
	void operator = (const CUnit& t)
	{
		// CObjectAPI
		mPosition = t.mPosition;

		// CUnit
		mRadius = t.mRadius;

		mAnchorX = t.mAnchorX;
		mAnchorY = t.mAnchorY;

		mDisplayX = t.mDisplayX;
		mDisplayY = t.mDisplayY;

		mWidth = t.mWidth;
		mHeight = t.mHeight;

		mVelocity = t.mVelocity;

		// shallow copy
		mpTexture = t.mpTexture;
		mpEngine = t.mpEngine;

		mIsActive = t.mIsActive;
	}

public:
	//void Render();

	virtual void Create(CAPI_Engine* tpEngine);
	virtual void Destroy();

	virtual void Update(float tDeltaTime);
	virtual void Render();

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

	//void Update();

	void SetEngine(CAPI_Engine* tpEngine)
	{
		mpEngine = tpEngine;
	}

	void SetIsActive(bool tIsActive)
	{
		mIsActive = tIsActive;
	}

	bool GetIsActive() const
	{
		return mIsActive;
	}

	// API prototype
public:
	virtual CObjectAPI* cloan() = 0;

public:
	// 반지름
	float mRadius = 0.0f;

	// pivot
	float mAnchorX = 0.5f;
	float mAnchorY = 0.5f;

	float mDisplayX = 0.0f;
	float mDisplayY = 0.0f;

	float mWidth = 0.0f;
	float mHeight = 0.0f;

	SVector2D mVelocity;

	CTexture* mpTexture = nullptr;
	CAPI_Engine* mpEngine = nullptr;

	// 활성 여부
	bool mIsActive;

};

