#pragma once
#include "SVector2D.h"
#include "CRef.h"

class CCollider;

class CObjectAPI: public CRef
{
public:
	CObjectAPI();
	virtual ~CObjectAPI();

public:
	virtual CObjectAPI* clone() = 0;

	void SetPosition(SVector2D tPosition)
	{
		mPosition = tPosition;
	}
	SVector2D GetPosition() const
	{
		return mPosition;
	}

	virtual void OnEnterCollision(CCollider* tOther) = 0;
	virtual void OnStayCollision(CCollider* tOther) = 0;
	virtual void OnExitCollision(CCollider* tOther) = 0;

protected:
	// ��ġ ����
	SVector2D mPosition;

};

/*
	OOP ���α׷����� 4���� Ư¡

	�߻�ȭ abstraction : �ڵ��� �߻�ȭ + �������� �߻�ȭ --> �������� �߻�ȭ
	����ȭ encapsulation : Data Hiding
	��Ӽ� inheritance :  ����� Ư���� �θ�Ŭ������ �ΰ� �̸� �̾�޾� �ڽ�Ŭ������ �ۼ��ϴ°�, ȣ������ ����
	������ polymorphysm : ���� �޽����� �ٸ� ����
		override + virtual + �θ�Ŭ���� Ÿ���� ������
*/

