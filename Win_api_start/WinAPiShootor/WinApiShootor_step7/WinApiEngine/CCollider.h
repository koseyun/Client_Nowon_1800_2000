#pragma once
#include "SVector2D.h"

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

	// 충돌체 간 충돌 처리 함수
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

private:
	// 축정렬경계상자를 가정하여 작성하겠다
	bool DoCollisionAABB(CCollider* tOther);

private:
	// 사각영역의 출돌체의 중심은 항상 정 가운데라고 가정하겠다
	SVector2D mPosition;

	float mWidth = 0.0f;
	float mHeight = 0.0f;

	CObjectAPI* mpObject = nullptr; // 이 충돌체의 소유자
};

