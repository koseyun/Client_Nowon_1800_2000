#include "CUnit.h"
#include "CAPI_Engine.h"
#include "CTexture.h"

// �ʱ�ȭ ����� �̿��Ͽ� �ʱ�ȭ��
// CUnit::CUnit() : mX(400.0f), mY(500.0f), mRadius(30.0f)
CUnit::CUnit() : CObjectAPI(), mRadius(30.0f), mVelocity()
{

}
CUnit::~CUnit()
{

}

void CUnit::Render(CAPI_Engine* tpEngine)
{
	//tpEngine->DrawCircle(mX, mY, mRadius);
	//tpEngine->DrawTexture(mX, mY, mpTexture);

	//float tWidth = 0.0f;
	//float tHeight = 0.0f;

	mWidth = mpTexture->mBitmapInfo.bmWidth;
	mHeight = mpTexture->mBitmapInfo.bmHeight;

	mDisplayX = mPosition.mX - mWidth * mAnchorX;
	mDisplayY = mPosition.mY - mHeight * mAnchorY;

	tpEngine->DrawTexture(mDisplayX, mDisplayY, mpTexture);

	// debug draw
	tpEngine->DrawCircle(mPosition.mX, mPosition.mY, mRadius);
}

void CUnit::SetTexture(CTexture* tpTexture)
{
	mpTexture = tpTexture;
}

void CUnit::SetAnchors(float tAnchorX, float tAnchorY)
{
	mAnchorX = tAnchorX;
	mAnchorY = tAnchorY;
}

void CUnit::Update()
{
	mPosition = mPosition + mVelocity; // ���ͳ����� ����
}
