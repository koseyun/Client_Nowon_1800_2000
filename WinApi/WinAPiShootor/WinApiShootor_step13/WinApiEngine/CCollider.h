#pragma once


#include "SVector2D.h"

class CObjectRyu;


#include <list>
using namespace std;

class CCollider
{
public:
	CCollider():
		mPosition(), mWidth(0.0f), mHeight(0.0)
	{
	};
	CCollider(const CCollider& tCollider)
	{
		mPosition = tCollider.mPosition;

		mWidth = tCollider.mWidth;
		mHeight = tCollider.mHeight;

		mpObject = tCollider.mpObject;

		//���Ѵٸ� �̷��� ǥ���� ����, ���� �����ؾ���. shallow copy
		//*this = tCollider;
	};

	~CCollider()
	{
	};


	void operator=(const CCollider& tCollider)
	{
		mPosition = tCollider.mPosition;

		mWidth = tCollider.mWidth;
		mHeight = tCollider.mHeight;

		mpObject = tCollider.mpObject;

		//���Ѵٸ� �̷��� ǥ���� ����, ���� �����ؾ���. shallow copy
		//*this = tCollider;
	}


public:
	//�浹ü �� �浹 ó�� �Լ� 
	bool DoCollision(CCollider* tColliderOther);

	void Create(SVector2D tPosition, float tWidth, float tHeight);
	void Update();


	void SetPosition(SVector2D tPosition)
	{
		mPosition = tPosition;
	}

	void SetSize(float tWidth, float tHeight)
	{
		mWidth = tWidth;
		mHeight = tHeight;
	}


	void SetOwnerObject(CObjectRyu* tpObject)
	{
		mpObject = tpObject;
	}
	CObjectRyu* GetOwnerObject() const
	{
		return mpObject;
	}


	void AddToCollisions(CCollider* tpCollider)
	{
		mCollisions.push_back(tpCollider);
	}
	void EraseFromCollisions(CCollider* tpCollider)
	{
		list<CCollider*>::iterator tItor;
		for (tItor = mCollisions.begin(); tItor != mCollisions.end(); ++tItor)
		{
			if (*tItor == tpCollider)
			{
				mCollisions.erase(tItor);
				break;
			}
		}
	}
	bool DoCheckBeInCollisions(CCollider* tpCollider)
	{
		list<CCollider*>::iterator tItor;
		for (tItor = mCollisions.begin(); tItor != mCollisions.end(); ++tItor)
		{
			if (*tItor == tpCollider)
			{
				return true;
			}
		}

		return false;
	}



private:
	//
	//�����İ����ڸ� �����Ͽ� �ۼ��ϰڴ�.
	bool DoCollisionAABB(CCollider* tOther);

	//���Ѵٸ� �� �浹ü�� ������ �͵� ���� �� �ְڴ�.


	


private:
	
	//�簢������ �浹ü�� �߽��� �׻� �� ������ �����ϰڴ�.
	SVector2D mPosition;

	float mWidth = 0.0f;
	float mHeight = 0.0f;


	CObjectRyu* mpObject = nullptr;	//�� �浹ü�� ������


	//�浹����
	list<CCollider*> mCollisions;
};

