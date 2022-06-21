#pragma once

/*
	�̱��� ����

	�̱��� ������ ���� : ��ü�� �ִ� ���������� 1���� ����
	(�ΰ������� �������� ������ �����͵��� ������ �������ε� ���δ�)

	������ 3���� �������� �̷������

	1. �ش� Ŭ���� ������ Ÿ���� mpInstance ������ static ���� ����ȴ�
	2. �����ڴ� public �� �ƴϴ�
	3. GetInstance() �Լ��� ���ǿ��� ��ü�� �ִ� ���� ������ 1���� �����ϴ� �Ǵ�������� ��ġ�Ѵ�


*/

//step0
/*
class CInputMgr
{
private:
	// static Ű����� ������ ������ ������ �޸� ������ ��ġ�Ѵ�
	// Ŭ������ ����� �ƴϹǷ�? Ŭ������ ��� �ʱ�ȭ ������ ���� �� ����
	static CInputMgr* mpInstance; //= nullptr;

private:
	CInputMgr();
	~CInputMgr();

public:
	static CInputMgr* GetInst();
	static void ReleaseInst();

};
*/

// step1
#include "APIMacro.h"

class CInputMgr
{
	SINGLETON_DECLARE(CInputMgr)
};