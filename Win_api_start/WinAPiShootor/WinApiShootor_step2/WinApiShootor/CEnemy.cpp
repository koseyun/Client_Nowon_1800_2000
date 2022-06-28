
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
