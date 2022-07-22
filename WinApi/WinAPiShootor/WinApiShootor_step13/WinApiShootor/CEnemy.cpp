#include "CEnemy.h"




#include "CBullet.h"
#include <windows.h>


#include "CCollider.h"

#include "CAnimator.h"


CEnemy::CEnemy()
{

}
CEnemy::CEnemy(const CEnemy& t)
{
	//CObjectRyu
	mPosition = t.mPosition;

	mpEngine = t.mpEngine;
	mIsActive = t.mIsActive;



	mVelocity = t.mVelocity;

	//CUnit

	mRadius = t.mRadius;

	mAnchorX = t.mAnchorX;
	mAnchorY = t.mAnchorY;

	mDisplayX = t.mDisplayX;
	mDisplayY = t.mDisplayY;

	mWidth = t.mWidth;
	mHeight = t.mHeight;


	//shallow copy
	mpTexture = t.mpTexture;


		// CCollider를 deep copy해야 한다
		//mColliders = tUnit.mColliders;
	/*for (list<CCollider*>::const_iterator tItor = t.mColliders.cbegin(); tItor != t.mColliders.cend(); ++tItor)
	{

		CCollider* tCollider = nullptr;
		tCollider = new CCollider();

		(*tCollider) = (*(*tItor));

		tCollider->SetOwnerObject(this);

		mColliders.push_back(tCollider);

	}*/

	mpCollider = new CCollider();
	(*mpCollider) = (*t.mpCollider);

	mpCollider->SetOwnerObject(this);





	mTag = t.mTag;


	if (nullptr != t.mpAnimator)
	{
		mpAnimator = new CAnimator();
		(*mpAnimator) = (*t.mpAnimator);

		mpAnimator->SetOwnerObject(this);
	}


}
CEnemy::~CEnemy()
{

}


void CEnemy::DoFire(vector<CBullet*>& tBullets)
{
	tBullets[mCurIndexBullet]->SetPosition(SVector2D(this->mPosition.mX, this->mPosition.mY));
	tBullets[mCurIndexBullet]->SetVelocity(SVector2D(0.0f, +400.0f));
	tBullets[mCurIndexBullet]->SetIsActive(true);

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

//매개변수로 CObjectRyu참조를 받았다. 다르게 할수도 있을 것이다.
void CEnemy::DoFireAimed(vector<CBullet*>& tBullets, CObjectRyu* tpObject)
{
	//조준탄

	/*
		발사시작위치를 지정한다
		속도를 지정한다
		활성화한다
	*/

	tBullets[mCurIndexBullet]->SetPosition(SVector2D(this->mPosition.mX, this->mPosition.mY));



	//속도를 지정한다.
	//그러기 위해서는 속도를 구해야 한다.
	//여기서 조준탄이란 시작지점에서 목표지점까지 날아가는 탄환이다.
	//그러므로, 목표지점까지의 방향을 알아야 한다.
	
	//방향의 개념이 들어가므로 벡터이다.

	//임의의 크기의 벡터 구하기 = 목적지점 - 시작지점
	SVector2D tStartP = this->GetPosition();
	SVector2D tTargetP = tpObject->GetPosition();

	SVector2D tVector = tTargetP - tStartP;


	//해당 방향벡터 구하기 
	//임의의 크기의 벡터 를 '정규화': 벡터의 크기를 1로 만든다

	SVector2D tUnitVector = tVector.Normalize();				//정규화

	float tScalarSpeed = 200.0f;
	SVector2D tVelocity = tUnitVector * tScalarSpeed;			//벡터의 스칼라곱




	tBullets[mCurIndexBullet]->SetVelocity(tVelocity);
	tBullets[mCurIndexBullet]->SetIsActive(true);

	if (mCurIndexBullet < tBullets.size() - 1)
	{
		wchar_t tszTemp[64] = { 0 };
		wsprintf(tszTemp, L"DoFireAimed %d\n", mCurIndexBullet);
		OutputDebugString(tszTemp);

		mCurIndexBullet++;
	}
	else
	{
		mCurIndexBullet = 0;
	}
}

//ryu_circled
void CEnemy::DoFireCircled(vector<CBullet*>& tBullets)
{
	//원형탄

	/*
		발사시작위치를 지정한다
		속도를 지정한다
		활성화한다
	*/

	for (int ti = 0; ti < 8; ti++)
	{
		//탄환의 발사 시작 위치를 설정한다
		tBullets[ti]->SetPosition(SVector2D( this->GetPosition() ));

		//원형탄의 속도(벡터)를 결정하자 

		//원형탄의 각각의 축에 속력을 설정 
		
		//순수한 방향벡터를 구하자
		float tAngleDegree = 45.0f * ti;
		float tDirX = cosf(tAngleDegree * (3.14159f / 180.0f));
		float tDirY = sinf(tAngleDegree * (3.14159f / 180.0f));
		
		//크기를 적용하자
		tBullets[ti]->SetVelocity(SVector2D(tDirX, tDirY) * 200.0f);


		//탄환을 발사한다 
		tBullets[ti]->SetIsActive(true);
	}

}


void CEnemy::Update(float tDeltaTime)
{
	CUnit::Update(tDeltaTime);


	//너비까지 고려
	if (this->mPosition.mX + this->mWidth * 0.5f >= 800.0f)
	{
		SetVelocity(SVector2D(-1.0f, 0.0f) * 100.0f);
	}
	else if (this->mPosition.mX - this->mWidth * 0.5f <= 0.0f)
	{
		SetVelocity(SVector2D(+1.0f, 0.0f) * 100.0f);
	}

	

}