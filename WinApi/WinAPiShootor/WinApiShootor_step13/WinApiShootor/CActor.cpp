#include "CActor.h"


#include "CBullet.h"

#include <windows.h>


#include "playmacro.h"

#include "CCollider.h"

#include "CAnimator.h"



CActor::CActor()
{

}
CActor::CActor(const CActor& tActor)
{
	//CObjectRyu
	mPosition = tActor.mPosition;

	mpEngine = tActor.mpEngine;
	mIsActive = tActor.mIsActive;



	mVelocity = tActor.mVelocity;

	//CUnit

	mRadius = tActor.mRadius;

	mAnchorX = tActor.mAnchorX;
	mAnchorY = tActor.mAnchorY;

	mDisplayX = tActor.mDisplayX;
	mDisplayY = tActor.mDisplayY;

	mWidth = tActor.mWidth;
	mHeight = tActor.mHeight;


	//shallow copy
	mpTexture = tActor.mpTexture;

		// CCollider를 deep copy해야 한다
		//mColliders = tUnit.mColliders;
	/*for (list<CCollider*>::const_iterator tItor = tActor.mColliders.cbegin(); tItor != tActor.mColliders.cend(); ++tItor)
	{

		CCollider* tCollider = nullptr;
		tCollider = new CCollider();

		(*tCollider) = (*(*tItor));

		tCollider->SetOwnerObject(this);


		mColliders.push_back(tCollider);

	}*/

	mpCollider = new CCollider();
	(*mpCollider) = (*tActor.mpCollider);

	mpCollider->SetOwnerObject(this);



	mTag = tActor.mTag;

	//mpAnimator = tActor.mpAnimator;
	if (nullptr != tActor.mpAnimator)
	{
		mpAnimator = new CAnimator();
		(*mpAnimator) = (*tActor.mpAnimator);

		mpAnimator->SetOwnerObject(this);
	}

}
CActor::~CActor()
{

}


void CActor::DoFire(vector<CBullet*>& tBullets)
{
	tBullets[mCurIndexBullet]->SetPosition(SVector2D(this->mPosition.mX, this->mPosition.mY));
	tBullets[mCurIndexBullet]->SetVelocity(SVector2D(0.0f, -200.0f));
	tBullets[mCurIndexBullet]->SetIsActive(true);

	//if (mCurIndexBullet < ACTOR_BULLET_MAX_COUNT - 1)
	if (mCurIndexBullet < tBullets.size() - 1)
	{
		wchar_t tszTemp[64] = { 0 };
		wsprintf(tszTemp, L"DoFire %d\n", mCurIndexBullet);
		OutputDebugString(tszTemp);

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

	//경계처리
	//물론 은닉화를 하면 더욱 좋겠다
	/*if (this->mPosition.mX < 0.0f )
	{
		this->mPosition.mX = 0.0f;
	}

	if (this->mPosition.mX > 800.0f)
	{
		this->mPosition.mX = 800.0f;
	}*/
	//너비까지 고려
	if (this->mPosition.mX - this->mWidth*0.5f < 0.0f)
	{
		this->mPosition.mX = 0.0f + this->mWidth*0.5f;
	}

	if (this->mPosition.mX + this->mWidth * 0.5f > 800.0f)
	{
		this->mPosition.mX = 800.0f - this->mWidth * 0.5f;
	}

}

