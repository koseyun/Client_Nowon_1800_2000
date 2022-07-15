#pragma once
#include "CObjectAPI.h"
#include "CCollider.h"
#include "CAnimator.h"

class CAPI_Engine;
class CTexture;
class CAnimator;

class CUnit: public CObjectAPI
{
public:
	CUnit();
	virtual ~CUnit();

	// ���������
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
		// mpTexture, mpEngine�� �����ڿ��̹Ƿ�
		mpTexture = t.mpTexture;
		mpEngine = t.mpEngine;

		mIsActive = t.mIsActive;

		// deep copy
		// �ݶ��̴��� ���ָ��� ������ �ڿ��̹Ƿ�
		mpCollider = new CCollider();
		(*mpCollider) = (*t.mpCollider);

		mpCollider->SetOwnerObject(this);

		mTag = t.mTag;

		if (t.mpAnimator)
		{
			mpAnimator = new CAnimator();
			*mpAnimator = *t.mpAnimator;

			mpAnimator->SetOwnerObject(this);
		}
	}

	// ������Կ�����
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

		// deep copy
		// �ݶ��̴��� ���ָ��� ������ �ڿ��̹Ƿ�
		mpCollider = new CCollider();
		(*mpCollider) = (*t.mpCollider);

		mpCollider->SetOwnerObject(this);

		mTag = t.mTag;

		if (t.mpAnimator)
		{
			mpAnimator = new CAnimator();
			*mpAnimator = *t.mpAnimator;

			mpAnimator->SetOwnerObject(this);
		}
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

	/*void SetPosition(SVector2D tPosition)
	{
		mPosition = tPosition;
	}
	SVector2D GetPosition() const
	{
		return mPosition;
	}*/

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

	void SetRadius(float tRadius)
	{
		mRadius = tRadius;
	}
	float GetRadius() const
	{
		return mRadius;
	}

	/*bool Intersects(const CUnit& tOther) const
	{
		// this
		float tLeftX		 = 0.0f;
		float tRightX		 = 0.0f;
		float tTopY			 = 0.0f;
		float tBottomY		 = 0.0f;

		tLeftX	 = mPosition.mX - mWidth * mAnchorX;
		tRightX  = mPosition.mX - mWidth * mAnchorX + mWidth;
		tTopY	 = mPosition.mY - mHeight * mAnchorY;
		tBottomY = mPosition.mY - mHeight * mAnchorY + mHeight;
							 
		// other			 
		float tLeftX_Other	 = 0.0f;
		float tRightX_Other  = 0.0f;
		float tTopY_Other	 = 0.0f;
		float tBottomY_Other = 0.0f;

		tLeftX_Other	= tOther.GetPosition().mX - tOther.mWidth * tOther.mAnchorX;
		tRightX_Other	= tOther.GetPosition().mX - tOther.mWidth * tOther.mAnchorX + tOther.mWidth;
		tTopY_Other		= tOther.GetPosition().mY - tOther.mHeight * tOther.mAnchorY;
		tBottomY_Other  = tOther.GetPosition().mY - tOther.mHeight * tOther.mAnchorY + tOther.mHeight;

		if (tRightX < tLeftX_Other)
		{
			return false;
		}
		if (tLeftX > tRightX_Other)
		{
			return false;
		}
		if (tBottomY < tTopY_Other)
		{
			return false;
		}
		if (tTopY > tBottomY_Other)
		{
			return false;
		}

		return true;
	}*/

	// API prototype
public:
	virtual CObjectAPI* clone() = 0;

	virtual void OnEnterCollision(CCollider* tOther) override {};
	virtual void OnStayCollision(CCollider* tOther) override {};
	virtual void OnExitCollision(CCollider* tOther) override {};

	// ����
	void SetColliderPosition()
	{
		mpCollider->SetPosition(this->GetPosition());
	}

	void SetDefaultAniSeq(const string& tStrDefaultAniSeq);
	void PlayAni(const string& tStrAniSeq);

public:
	// ������
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


	// Ȱ�� ����
	bool mIsActive = false;

public:
	// �浹ü�� �ϳ���� �����ϰڴ�(���� �������� ���� ���� �ִ�)
	CCollider* mpCollider = nullptr;
	
public:
	CAnimator* mpAnimator = nullptr;

	CAnimator* CreateAnimation(const string& tId, CAPI_Engine* tpEngine);
	void DestroyAnimation();
};

