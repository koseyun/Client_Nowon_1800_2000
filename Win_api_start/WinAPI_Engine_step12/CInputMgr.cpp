#include "CInputMgr.h"


//// static �����̹Ƿ� ������������ �ʱ�ȭ ǥ��
//CInputMgr* CInputMgr::mpInstance = nullptr;
//
//CInputMgr* CInputMgr::GetInst()
//{
//	if (nullptr == mpInstance)
//	{
//		mpInstance = new CInputMgr();
//	}
//
//	return mpInstance;
//}
//
//void CInputMgr::ReleaseInst()
//{
//	if (nullptr != mpInstance)
//	{
//		delete mpInstance;
//		// mpInstance = nullptr;
//		// ���� �����Ϸ������� �� ǥ���� �������
//	}
//}

SINGLETON_DEFINITION(CInputMgr)

CInputMgr::CInputMgr()
{
	// ���� �����Ϸ������� �� ǥ���� �������
	// mpInstance = nullptr;
}

CInputMgr::~CInputMgr()
{

}


