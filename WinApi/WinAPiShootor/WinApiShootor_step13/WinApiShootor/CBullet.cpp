#include "CBullet.h"

#include "CCollider.h"

#include "CAnimator.h"

CBullet::CBullet()
{

}
CBullet::CBullet(const CBullet& tBullet)
{
	//CObjectRyu
	mPosition = tBullet.mPosition;

	mpEngine = tBullet.mpEngine;
	mIsActive = tBullet.mIsActive;



	mVelocity = tBullet.mVelocity;

	//CUnit

	mRadius = tBullet.mRadius;

	mAnchorX = tBullet.mAnchorX;
	mAnchorY = tBullet.mAnchorY;

	mDisplayX = tBullet.mDisplayX;
	mDisplayY = tBullet.mDisplayY;

	mWidth = tBullet.mWidth;
	mHeight = tBullet.mHeight;


	//shallow copy
	mpTexture = tBullet.mpTexture;

		// CCollider를 deep copy해야 한다
		//mColliders = tUnit.mColliders;
	/*for (list<CCollider*>::const_iterator tItor = tBullet.mColliders.cbegin(); tItor != tBullet.mColliders.cend(); ++tItor)
	{

		CCollider* tCollider = nullptr;
		tCollider = new CCollider();

		(*tCollider) = (*(*tItor));

		tCollider->SetOwnerObject(this);


		mColliders.push_back(tCollider);

	}*/

	mpCollider = new CCollider();
	(*mpCollider) = (*tBullet.mpCollider);

	mpCollider->SetOwnerObject(this);




	mTag = tBullet.mTag;




	
	if (nullptr != tBullet.mpAnimator)
	{
		mpAnimator = new CAnimator();
		(*mpAnimator) = (*tBullet.mpAnimator);

		mpAnimator->SetOwnerObject(this);
	}


}
CBullet::~CBullet()
{

}