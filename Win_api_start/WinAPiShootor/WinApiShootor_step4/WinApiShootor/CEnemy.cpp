
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
	// źȯ �߻� �˰���
	/*
		źȯ�� �߻� ���������� ���Ѵ�
		źȯ�� �߻� �ӵ��� �����Ѵ�
		źȯ�� Ȱ��ȭ�Ѵ�
	*/

	tBullets[mCurIndexBullet]->SetPosition(this->GetPosition());
	tBullets[mCurIndexBullet]->SetVelocity(SVector2D(0.0f, +1.0f) * 200.0f);	
	tBullets[mCurIndexBullet]->SetIsActive(true);

	wchar_t tszTemp[64] = { 0 };
	wsprintf(tszTemp, L"CEnemy::DoFire %d\n", mCurIndexBullet);
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

void CEnemy::DoFireAimed(vector<CBullet*>& tBullets, CObjectAPI* tpObject)
{
	// źȯ �߻� �˰���
	/*
		źȯ�� �߻� ���������� ���Ѵ�
		źȯ�� �߻� �ӵ��� �����Ѵ�
		źȯ�� Ȱ��ȭ�Ѵ�
	*/

	tBullets[mCurIndexBullet]->SetPosition(this->GetPosition());

	// ������ ũ���� �ش� ������ ���� ���ϱ� = �������� - ��������
	SVector2D tStartP = this->GetPosition();
	SVector2D tTargetP = tpObject->GetPosition();

	SVector2D tVector = tTargetP - tStartP;

	// ������ ���� ���͸� ���Ѵ�(ũ�Ⱑ 1�� ��������)
	SVector2D tUnitVector = tVector.Normalize(); // ����ȭ

	float tScalarSpeed = 200.0f; // �ӷ��� ����
	SVector2D tVelocity = tUnitVector * tScalarSpeed; // �ӵ��� ����, ������ ��Į���

	tBullets[mCurIndexBullet]->SetVelocity(tVelocity);
	//tBullets[mCurIndexBullet]->SetVelocity(SVector2D(0.0f, +1.0f) * 200.0f);

	tBullets[mCurIndexBullet]->SetIsActive(true);

	wchar_t tszTemp[64] = { 0 };
	wsprintf(tszTemp, L"CEnemy::DoFireAimed %d\n", mCurIndexBullet);
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

void CEnemy::DoFireCircled(vector<CBullet*>& tBullets)
{
	// źȯ �߻� �˰���
	/*
		źȯ�� �߻� ���������� ���Ѵ�
		źȯ�� �߻� �ӵ��� �����Ѵ�
		źȯ�� Ȱ��ȭ�Ѵ�
	*/

	for (int ti = 0; ti < 8; ti++)
	{
		tBullets[ti]->SetPosition(this->GetPosition());

		tBullets[ti]->SetIsActive(true);
	}
}

void CEnemy::Update(float tDeltaTime)
{
	CUnit::Update(tDeltaTime);

	// ���� ���
	if (this->mPosition.mX - this->mWidth * 0.5f < 0.0f)
	{
		this->SetVelocity(SVector2D(+1.0f, 0.0f) * 100.0f);
	}
	// ������ ���
	if (this->mPosition.mX + this->mWidth * 0.5f > 800.0f)
	{
		this->SetVelocity(SVector2D(-1.0f, 0.0f) * 100.0f);
	}
}
