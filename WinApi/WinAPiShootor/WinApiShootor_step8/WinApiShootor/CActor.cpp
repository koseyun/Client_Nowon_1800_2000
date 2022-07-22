#include "CActor.h"
#include "CBullet.h"
#include <Windows.h>

CActor::CActor()
{

}

CActor::~CActor()
{

}

CActor::CActor(const CActor& t)
{
	*this = t;

	//// CObjectAPI
	//mPosition = t.mPosition;

	//// CUnit
	//mRadius = t.mRadius;

	//mAnchorX = t.mAnchorX;
	//mAnchorY = t.mAnchorY;

	//mDisplayX = t.mDisplayX;
	//mDisplayY = t.mDisplayY;

	//mWidth = t.mWidth;
	//mHeight = t.mHeight;

	//mVelocity = t.mVelocity;

	//// shallow copy
	//mpTexture = t.mpTexture;
	//mpEngine = t.mpEngine;
}

// ���ΰ� ��ü�� �Ϲ�źȯ �߻�
void CActor::DoFire(vector<CBullet*>& tBullets)
{
	// źȯ �߻� �˰���
	/*
		źȯ�� �߻� ���������� ���Ѵ�
		źȯ�� �߻� �ӵ��� �����Ѵ�
		źȯ�� Ȱ��ȭ�Ѵ�
	*/
	tBullets[mCurIndexBullet]->SetPosition(this->GetPosition());
	tBullets[mCurIndexBullet]->SetVelocity(SVector2D(0.0f, -1.0f) * 200.0f);
	tBullets[mCurIndexBullet]->SetIsActive(true);

	wchar_t tszTemp[64] = { 0 };
	wsprintf(tszTemp, L"DoFire %d\n", mCurIndexBullet);
	OutputDebugString(tszTemp);

	// źȯ�� ����
	if (mCurIndexBullet < tBullets.size() - 1)
	{
		mCurIndexBullet++;
	}
	else
	{
		mCurIndexBullet = 0;
	}
}

void CActor::Update(float tDeltaTime)
{
	CUnit::Update(tDeltaTime);
	
	// �¿� ���ó��
	/*if (this->mPosition.mX < 0.0f)
	{
		this->mPosition.mX = 0.0f;
	}

	if (this->mPosition.mX > 800.0f)
	{
		this->mPosition.mX = 800.0f;
	}*/

	if (this->mPosition.mX  - this->mWidth * 0.5f < 0.0f)
	{
		this->mPosition.mX = 0.0f + this->mWidth * 0.5f;
	}

	if (this->mPosition.mX + this->mWidth * 0.5f > 800.0f)
	{
		this->mPosition.mX = 800.0f - this->mWidth * 0.5f;
	}
}