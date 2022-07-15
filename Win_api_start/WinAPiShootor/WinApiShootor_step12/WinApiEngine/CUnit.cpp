#include "CUnit.h"
#include "CAPI_Engine.h"
#include "CTexture.h"
#include "CAnimator.h"

// �ʱ�ȭ ����� �̿��Ͽ� �ʱ�ȭ��
// CUnit::CUnit() : mX(400.0f), mY(500.0f), mRadius(30.0f)
CUnit::CUnit() : CObjectAPI(), mRadius(30.0f), mVelocity()
{

}
CUnit::~CUnit()
{
	if (nullptr != mpCollider)
	{
		delete mpCollider;
		mpCollider = nullptr;
	}
}

void CUnit::Create(CAPI_Engine* tpEngine)
{
	SetEngine(tpEngine);

	mpCollider = new CCollider();
	// ũ��� �⺻������ �����ϰڴ�
	mpCollider->Create(this->GetPosition(), 100.0f, 100.0f);
	mpCollider->SetOwnerObject(this);
}

void CUnit::Destroy()
{
	if (nullptr != mpCollider)
	{
		delete mpCollider;
		mpCollider = nullptr;
	}
}

void CUnit::Update(float tDeltaTime)
{
	if (mIsActive)
	{
		mPosition = mPosition + mVelocity * tDeltaTime;

		mpCollider->Update();
	}
}

void CUnit::Render()
{
	if (mIsActive)
	{
		//mWidth = mpTexture->mBitmapInfo.bmWidth;
		//mHeight = mpTexture->mBitmapInfo.bmHeight;

		mDisplayX = mPosition.mX - mWidth * mAnchorX;
		mDisplayY = mPosition.mY - mHeight * mAnchorY;

		if (nullptr != mpAnimator)
		{
			mpAnimator->UpdateAnimation(mpEngine->GetDeltaTime());
			mpAnimator->Render(mpEngine, mDisplayX, mDisplayY);
		}
		else
		{
			mpEngine->DrawTexture(mDisplayX, mDisplayY, mpTexture);
		}

		// debug draw
		//mpEngine->DrawCircle(mPosition.mX, mPosition.mY, mRadius);
	}
}

void CUnit::SetTexture(CTexture* tpTexture)
{
	mpTexture = tpTexture;

	mWidth = mpTexture->mBitmapInfo.bmWidth;
	mHeight = mpTexture->mBitmapInfo.bmHeight;

	mpCollider->SetSize(this->mWidth, this->mHeight);
}

void CUnit::SetAnchors(float tAnchorX, float tAnchorY)
{
	mAnchorX = tAnchorX;
	mAnchorY = tAnchorY;
}

CAnimator* CUnit::CreateAnimation(const string& tId, CAPI_Engine* tpEngine)
{
	mpAnimator = new CAnimator();

	mpAnimator->SetId(tId);
	if (!mpAnimator->Create(tpEngine))
	{
		return nullptr;
	}

	return mpAnimator;
}

void CUnit::DestroyAnimation()
{
	if (mpAnimator)
	{
		mpAnimator->Destroy();
	}

	if (mpAnimator)
	{
		delete mpAnimator;
		mpAnimator = nullptr;
	}
}

void CUnit::SetDefaultAniSeq(const string& tStrDefaultAniSeq)
{
	mpAnimator->SetDefaultAniSeq(tStrDefaultAniSeq);
}

void CUnit::PlayAni(const string& tStrAniSeq)
{
	mpAnimator->PlayAni(tStrAniSeq);
}