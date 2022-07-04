#include "CCollisionMgr.h"
#include "CUnit.h"
#include "windows.h"

// �̱��� ���� ����
SINGLETON_DEFINITION(CCollisionMgr)

CCollisionMgr::CCollisionMgr()
{

}
CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::AddUnit(CUnit* t)
{
	mCollisionUnits.push_back(t);
}

void CCollisionMgr::Update(float tDeltaTime)
{
	if (mCollisionUnits.size() < 2)
	{
		return;
	}

	list<CUnit*>::iterator tItor;
	for (tItor = mCollisionUnits.begin(); tItor != mCollisionUnits.end(); ++tItor)
	{
		list<CUnit*>::iterator tItor_0 = tItor;
		++tItor_0;

		for (; tItor_0 != mCollisionUnits.end(); ++tItor_0)
		{
			if ((*tItor)->GetIsActive() && (*tItor_0)->GetIsActive())
			{
				DoCollision(*tItor, *tItor_0);
			}
		}
	}
}

bool CCollisionMgr::DoCollision(CUnit* tThis, CUnit* tOther)
{
	// CUnit�� �����Ǿ� �ִ� collider���� �����´�
	CCollider* tpThis = tThis->mpCollider;
	CCollider* tpOther = tOther->mpCollider;

	bool tApi = tpThis->DoCollision(tpOther);
	if (tApi)
	{
		// ���� �� �ۼ��ؾ���
		OutputDebugString(L"collision\n");
		return true;
	}

	return false;
}
