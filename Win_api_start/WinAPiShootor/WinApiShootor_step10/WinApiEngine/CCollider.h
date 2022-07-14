#pragma once
#include "SVector2D.h"
#include <list>
using namespace std;

class CObjectAPI;

class CCollider
{
public:
	CCollider() : mPosition(), mWidth(0.0f), mHeight(0.0)
	{
	};
	CCollider(const CCollider& tCollider)
	{
		mPosition = tCollider.mPosition;

		mWidth = tCollider.mWidth;
		mHeight = tCollider.mHeight;

		mpObject = tCollider.mpObject;
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
	}

public:

	// �浹ü �� �浹 ó�� �Լ�
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

	void SetOwnerObject(CObjectAPI* tpObject)
	{
		mpObject = tpObject;
	}
	CObjectAPI* GetOwnerObject() const
	{
		return mpObject;
	}

	SVector2D GetPosition() const
	{
		return mPosition;
	}

	// ���� ��ũ�帮��Ʈ�̹Ƿ� �߰�, ������ �ɸ��� �ð��� �����ϴ�, O(1)
	// mCollisions �� ���� �߰�
	void AddToCollisions(CCollider* tpCollider)
	{
		mCollisions.push_back(tpCollider);
	}
	// mCollisions �� ���� ����
	void EraseFromCollisions(CCollider* tpCollider)
	{
		// Ž���� O(n)
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
	
	// �ٸ� ������ �ݶ��̴��� �����Ѵ�
	// ���� �� ��Ͽ� �ִٸ� ������ �浹�� �Ͼ�� ���⿡ �����ص� ������ ���̴�
	bool DoCheckBeInCollisions(CCollider* tpCollider)
	{
		// Ž��, ��ȸ(travers)�Ѵ�
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
	// �����İ����ڸ� �����Ͽ� �ۼ��ϰڴ�
	bool DoCollisionAABB(CCollider* tOther);

private:
	// �簢������ �⵹ü�� �߽��� �׻� �� ������ �����ϰڴ�
	SVector2D mPosition;

	float mWidth = 0.0f;
	float mHeight = 0.0f;

	CObjectAPI* mpObject = nullptr; // �� �浹ü�� ������

	// �浹ü ��� ���� : �浹�� ��� ������ �������� ���並 �ϱ� ���� �ʿ��ϴ�
	list<CCollider*> mCollisions;

};

