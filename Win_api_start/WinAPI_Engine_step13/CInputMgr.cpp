#include "CInputMgr.h"


//// static 변수이므로 전역공간에서 초기화 표현
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
//		// 요즘 컴파일러에서는 이 표현도 문법통과
//	}
//}

SINGLETON_DEFINITION(CInputMgr)

CInputMgr::CInputMgr()
{
	mhWnd = 0;
	mMapKeys.clear();
	mpKeyInfo = nullptr;
}
CInputMgr::~CInputMgr()
{
	unordered_map<string, SKeyInfo*>::iterator tItor;
	
	for (tItor = mMapKeys.begin(); tItor != mMapKeys.end(); ++tItor)
	{
		if (nullptr != tItor->second)
		{
			delete tItor->second;
		}
	}

	mMapKeys.clear();
}

void CInputMgr::Create(HWND hWnd)
{
	mhWnd = hWnd;
}

void CInputMgr::Update()
{
	// todo
	unordered_map<string, SKeyInfo*>::const_iterator tItor;

	for (tItor = mMapKeys.begin(); tItor != mMapKeys.end(); ++tItor)
	{
		int tPushConst = 0;

		// 0x8000 이전에 눌림 없음, 호출당시에 눌림 있음
		if (GetAsyncKeyState(tItor->second->mKeyInput) & 0x8000)
		{
			++tPushConst;
		}

		if (tPushConst >= 1)
		{
			if (!tItor->second->mIsDown && !tItor->second->mIsPress)
			{
				// 처음 눌린 것이다 DOWN
				tItor->second->mIsDown = true;
			}
			else if (tItor->second->mIsDown && !tItor->second->mIsPress)
			{
				// 눌리고 있는 중이다 PRESS
				tItor->second->mIsDown = false;
				tItor->second->mIsPress = true;
			}
		}
		else // 여기까지 왔다면 현재 눌린 상태가 아니라는 것이다
		{
			if (tItor->second->mIsDown || tItor->second->mIsPress)
			{
				// 떼어지고 있는 것이다
				tItor->second->mIsDown = false;
				tItor->second->mIsPress = false;
				tItor->second->mIsUp = true;
			}
			else if (tItor->second->mIsUp)
			{
				// 아무 입력도 없는 상태이다
				tItor->second->mIsDown = false;
				tItor->second->mIsPress = false;
				tItor->second->mIsUp = false;
			}
		}
	}
}

SKeyInfo* CInputMgr::FindKey(const string& tStrKey) const
{
	// O(1)로 검색
	unordered_map<string, SKeyInfo*>::const_iterator tItor = mMapKeys.find(tStrKey);
	
	if (tItor == mMapKeys.end())
	{
		return nullptr;
	}

	// first : 키, second : 값(실제 데이터)
	return tItor->second;
}

bool CInputMgr::KeyDown(const string& tStrKey) const
{
	SKeyInfo* tpInfo = FindKey(tStrKey);

	if (nullptr == tpInfo)
	{
		return false;
	}

	return tpInfo->mIsDown;
}

bool CInputMgr::KeyPress(const string& tStrKey) const
{
	SKeyInfo* tpInfo = FindKey(tStrKey);

	if (nullptr == tpInfo)
	{
		return false;
	}

	return tpInfo->mIsPress;
}

bool CInputMgr::KeyUp(const string& tStrKey) const
{
	SKeyInfo* tpInfo = FindKey(tStrKey);

	if (nullptr == tpInfo)
	{
		return false;
	}

	return tpInfo->mIsUp;
}
