#include "CInputMgr.h"

/*
// static 변수이므로 전역공간에서 초기화 표현
CInputMgr* CInputMgr::mpInstance = nullptr;

CInputMgr::CInputMgr()
{
	// 요즘 컴파일러에서는 이 표현도 문법통과
	// mpInstance = nullptr;
}

CInputMgr::~CInputMgr()
{
}

CInputMgr* CInputMgr::GetInst()
{
	if (nullptr == mpInstance)
	{
		mpInstance = new CInputMgr();
	}

	return mpInstance;
}

void CInputMgr::ReleaseInst()
{
	if (nullptr != mpInstance)
	{
		delete mpInstance;
		// mpInstance = nullptr;
		// 요즘 컴파일러에서는 이 표현도 문법통과
	}
}
*/