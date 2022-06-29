
#include "CEnemy.h"
#include "CBullet.h"
#include <windows.h>

CEnemy::CEnemy()
{

}

CEnemy::~CEnemy()
{

}

CEnemy::CEnemy(const CEnemy& t)
{
	*this = t;
}

void CEnemy::DoFire(vector<CBullet*>& tBullets)
{
	// 탄환 발사 알고리즘
	/*
		탄환의 발사 시작지점을 정한다
		탄환의 발사 속도를 지정한다
		탄환을 활성화한다
	*/

	tBullets[mCurIndexBullet]->SetPosition(this->GetPosition());
	tBullets[mCurIndexBullet]->SetVelocity(SVector2D(0.0f, +1.0f) * 200.0f);	
	tBullets[mCurIndexBullet]->SetIsActive(true);

	wchar_t tszTemp[64] = { 0 };
	wsprintf(tszTemp, L"CEnemy::DoFire %d\n", mCurIndexBullet);
	OutputDebugString(tszTemp);

	// 탄환의 연사
	if (mCurIndexBullet < tBullets.size() - 1)
	{
		mCurIndexBullet++;
	}
	else
	{
		mCurIndexBullet = 0;
	}
}

void CEnemy::DoFireAimed(vector<CBullet*>& tBullets, CObjectAPI* tpObject)
{
	// 탄환 발사 알고리즘
	/*
		탄환의 발사 시작지점을 정한다
		탄환의 발사 속도를 지정한다
		탄환을 활성화한다
	*/

	tBullets[mCurIndexBullet]->SetPosition(this->GetPosition());

	// 임의의 크기의 해당 방향의 벡터 구하기 = 목적지점 - 시작지점
	SVector2D tStartP = this->GetPosition();
	SVector2D tTargetP = tpObject->GetPosition();

	SVector2D tVector = tTargetP - tStartP;

	tBullets[mCurIndexBullet]->SetVelocity(SVector2D(0.0f, +1.0f) * 200.0f);

	tBullets[mCurIndexBullet]->SetIsActive(true);

	wchar_t tszTemp[64] = { 0 };
	wsprintf(tszTemp, L"CEnemy::DoFireAimed %d\n", mCurIndexBullet);
	OutputDebugString(tszTemp);

	// 탄환의 연사
	if (mCurIndexBullet < tBullets.size() - 1)
	{
		mCurIndexBullet++;
	}
	else
	{
		mCurIndexBullet = 0;
	}
}

void CEnemy::Update(float tDeltaTime)
{
	CUnit::Update(tDeltaTime);

	// 왼쪽 경계
	if (this->mPosition.mX - this->mWidth * 0.5f < 0.0f)
	{
		this->SetVelocity(SVector2D(+1.0f, 0.0f) * 100.0f);
	}
	// 오른쪽 경계
	if (this->mPosition.mX + this->mWidth * 0.5f > 800.0f)
	{
		this->SetVelocity(SVector2D(-1.0f, 0.0f) * 100.0f);
	}
}
