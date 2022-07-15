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
		//OutputDebugString(L"collision\n");

		bool tIsBe = tpThis->DoCheckBeInCollisions(tpOther);
		// �浹�� ���� �� �����ε�, �浹ü ��Ͽ��� ���� ��ϵ��� �ʾҴ�
		// -> ó�� �浹�� �ǰ� �ִ� ���̴�
		if (!tIsBe)
		{
			tpThis->AddToCollisions(tpOther);
			tpOther->AddToCollisions(tpThis);

			OutputDebugString(L"Enter Collision\n");
			
			tpThis->GetOwnerObject()->OnEnterCollision(tpOther);
			tpOther->GetOwnerObject()->OnEnterCollision(tpThis);

			/*tThis->SetIsActive(false);
			tOther->SetIsActive(false);*/
		}
		else
		{
			// �浹�� ���� �� �����ε�, �浹ü ��Ͽ� �̹� ��ϵǾ� �ִ�
			// -> �浹 ���̴�

			//OutputDebugString(L"Stay Collision\n");

			tpThis->GetOwnerObject()->OnStayCollision(tpOther);
			tpOther->GetOwnerObject()->OnStayCollision(tpThis);
		}

		//return true;
	}
	else if (tpThis->DoCheckBeInCollisions(tpOther))
	{
		// ����� �浹���°� �ƴ�����, �������� �浹�̾���
		// ->�浹�� ������ �ִ� ��Ȳ�̴�

		tpThis->AddToCollisions(tpOther);
		tpOther->AddToCollisions(tpThis);

		OutputDebugString(L"Exit Collision\n");

		tpThis->GetOwnerObject()->OnExitCollision(tpOther);
		tpOther->GetOwnerObject()->OnExitCollision(tpThis);

		/*tThis->SetIsActive(false);
		tOther->SetIsActive(false);*/
	}

	return false;
}
