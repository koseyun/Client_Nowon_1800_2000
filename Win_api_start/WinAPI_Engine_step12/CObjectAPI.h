#pragma once
#include "SVector2D.h"
#include "CRef.h"

class CObjectAPI: public CRef
{
public:
	CObjectAPI();
	virtual ~CObjectAPI();

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

