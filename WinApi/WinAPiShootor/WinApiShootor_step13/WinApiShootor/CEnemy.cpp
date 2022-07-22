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


		// CCollider�� deep copy�ؾ� �Ѵ�
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

//�Ű������� CObjectRyu������ �޾Ҵ�. �ٸ��� �Ҽ��� ���� ���̴�.
void CEnemy::DoFireAimed(vector<CBullet*>& tBullets, CObjectRyu* tpObject)
{
	//����ź

	/*
		�߻������ġ�� �����Ѵ�
		�ӵ��� �����Ѵ�
		Ȱ��ȭ�Ѵ�
	*/

	tBullets[mCurIndexBullet]->SetPosition(SVector2D(this->mPosition.mX, this->mPosition.mY));



	//�ӵ��� �����Ѵ�.
	//�׷��� ���ؼ��� �ӵ��� ���ؾ� �Ѵ�.
	//���⼭ ����ź�̶� ������������ ��ǥ�������� ���ư��� źȯ�̴�.
	//�׷��Ƿ�, ��ǥ���������� ������ �˾ƾ� �Ѵ�.
	
	//������ ������ ���Ƿ� �����̴�.

	//������ ũ���� ���� ���ϱ� = �������� - ��������
	SVector2D tStartP = this->GetPosition();
	SVector2D tTargetP = tpObject->GetPosition();

	SVector2D tVector = tTargetP - tStartP;


	//�ش� ���⺤�� ���ϱ� 
	//������ ũ���� ���� �� '����ȭ': ������ ũ�⸦ 1�� �����

	SVector2D tUnitVector = tVector.Normalize();				//����ȭ

	float tScalarSpeed = 200.0f;
	SVector2D tVelocity = tUnitVector * tScalarSpeed;			//������ ��Į���




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
	//����ź

	/*
		�߻������ġ�� �����Ѵ�
		�ӵ��� �����Ѵ�
		Ȱ��ȭ�Ѵ�
	*/

	for (int ti = 0; ti < 8; ti++)
	{
		//źȯ�� �߻� ���� ��ġ�� �����Ѵ�
		tBullets[ti]->SetPosition(SVector2D( this->GetPosition() ));

		//����ź�� �ӵ�(����)�� �������� 

		//����ź�� ������ �࿡ �ӷ��� ���� 
		
		//������ ���⺤�͸� ������
		float tAngleDegree = 45.0f * ti;
		float tDirX = cosf(tAngleDegree * (3.14159f / 180.0f));
		float tDirY = sinf(tAngleDegree * (3.14159f / 180.0f));
		
		//ũ�⸦ ��������
		tBullets[ti]->SetVelocity(SVector2D(tDirX, tDirY) * 200.0f);


		//źȯ�� �߻��Ѵ� 
		tBullets[ti]->SetIsActive(true);
	}

}


void CEnemy::Update(float tDeltaTime)
{
	CUnit::Update(tDeltaTime);


	//�ʺ���� ���
	if (this->mPosition.mX + this->mWidth * 0.5f >= 800.0f)
	{
		SetVelocity(SVector2D(-1.0f, 0.0f) * 100.0f);
	}
	else if (this->mPosition.mX - this->mWidth * 0.5f <= 0.0f)
	{
		SetVelocity(SVector2D(+1.0f, 0.0f) * 100.0f);
	}

	

}