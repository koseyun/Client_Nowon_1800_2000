#include "CCollisionMgr.h"
#include "CUnit.h"
#include <windows.h>

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

		for (/*tItor_0 = mCollisionUnits.begin()*/; tItor_0 != mCollisionUnits.end(); ++tItor_0)
		{
			if ((*tItor)->GetIsActive() && (*tItor_0)->GetIsActive())
			{
				DoCollision((*tItor), (*tItor_0));
			}
		}

		//mCollisionUnits.clear();
	}
}

bool CCollisionMgr::DoCollision(CUnit* tThis, CUnit* tOther)
{
	//CUnit�� �����Ǿ� �ִ� collider���� �����´�
	CCollider* tpThis = tThis->mpCollider;
	CCollider* tpOther = tOther->mpCollider;

	bool tIsCollision = false;
	
	bool tRyu = tpThis->DoCollision(tpOther);
	if (tRyu)
	{
		//���� �浹 �����̴�.
		tIsCollision = true;

			bool tIsBe = tpThis->DoCheckBeInCollisions(tpOther);
			//ó�� �浹�ϴ°��̴�
			if (!tIsBe)
			{
				tpThis->AddToCollisions(tpOther);
				tpOther->AddToCollisions(tpThis);

				//OutputDebugString(L"Enter Collision\n");

				//Ȱ��ȭ�� ��쿡�� ȣ���ϸ� ���� ���ڴ�.
				tpThis->GetOwnerObject()->OnEnterCollision(tpOther);
				tpOther->GetOwnerObject()->OnEnterCollision(tpThis);

			}
			else//�浹���� ���̴�
			{
				////OutputDebugString(L"Stay Collision\n");
			}
	}
	else if (tpThis->DoCheckBeInCollisions(tpOther) )	//�浹�� ���� ���̴� 
	{
		tpThis->EraseFromCollisions(tpOther);
		tpOther->EraseFromCollisions(tpThis);

		//OutputDebugString(L"Exit Collision\n");

		//Ȱ��ȭ�� ��쿡�� ȣ���ϸ� ���� ���ڴ�.
		tpThis->GetOwnerObject()->OnExitCollision(tpOther);
		tpOther->GetOwnerObject()->OnExitCollision(tpThis);
	}
		
	return false;
}

//bool CCollisionMgr::DoCollision(CUnit* tThis, CUnit* tOther)
//{
//	//CUnit�� �����Ǿ� �ִ� collider���� �����´�
//	const list<CCollider*>* tpThis = tThis->GetCollider();
//	const list<CCollider*>* tpOther = tOther->GetCollider();
//
//	list<CCollider*>::const_iterator tItorThis;
//	list<CCollider*>::const_iterator tItorOther;
//
//	bool tIsCollision = false;
//
//	for (tItorThis = tpThis->begin(); tItorThis != tpThis->end(); ++tItorThis)
//	{
//		for (tItorOther = tpOther->begin(); tItorOther != tpOther->end(); ++tItorOther)
//		{
//			bool tRyu = (*tItorThis)->DoCollision((*tItorOther));
//			if (tRyu)
//			{
//				tIsCollision = true;
//
//				bool tIsBe = (*tItorThis)->DoCheckBeInCollisions(*tItorOther);
//				
//				//ó�� �浹�ϴ°��̴�
//				if (!tIsBe)
//				{
//					(*tItorThis)->AddToCollisions(*tItorOther);
//					(*tItorOther)->AddToCollisions(*tItorThis);
//
//					OutputDebugString(L"Enter Collision");
//				}
//				else//�浹���� ���̴�
//				{
//					OutputDebugString(L"Stay Collision");
//
//				}
//			}
//			else if( (*tItorThis)->DoCheckBeInCollisions(*tItorOther) )	//�浹�� ���� ���̴� 
//			{
//				(*tItorThis)->EraseFromCollisions(*tItorOther);
//				(*tItorOther)->EraseFromCollisions(*tItorThis);
//
//				OutputDebugString(L"Exit Collision");
//
//			}
//		}
//	}
// 
//	return false;
//}
