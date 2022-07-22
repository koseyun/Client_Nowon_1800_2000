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

		// Ű �Է��� ���������� ���
		for (int ti = 0; ti < tItor->second->mKeyInputs.size(); ++ti)
		{
			// 0x8000 ������ ���� ����, ȣ���ÿ� ���� ����
			if (GetAsyncKeyState(tItor->second->mKeyInputs[ti]) & 0x8000)
			{
				++tPushConst;
			}
		}

		//if (tPushConst >= 1) // ���������� ����Ǿ� ���� >=1
		// Ű�Է��� ���������� ���, Ű������ Ű ������ŭ, �� Ű���� �Է¿� ����
		if(tPushConst == tItor->second->mKeyInputs.size())
		{
			if (!tItor->second->mIsDown && !tItor->second->mIsPress)
			{
				// ó�� ���� ���̴� DOWN
				tItor->second->mIsDown = true;
			}
			else if (tItor->second->mIsDown && !tItor->second->mIsPress)
			{
				// ������ �ִ� ���̴� PRESS
				tItor->second->mIsDown = false;
				tItor->second->mIsPress = true;
			}
		}
		else // ������� �Դٸ� ���� ���� ���°� �ƴ϶�� ���̴�
		{
			if (tItor->second->mIsDown || tItor->second->mIsPress)
			{
				// �������� �ִ� ���̴�
				tItor->second->mIsDown = false;
				tItor->second->mIsPress = false;
				tItor->second->mIsUp = true;
			}
			else if (tItor->second->mIsUp)
			{
				// �ƹ� �Էµ� ���� �����̴�
				tItor->second->mIsDown = false;
				tItor->second->mIsPress = false;
				tItor->second->mIsUp = false;
			}
		}
	}
}

SKeyInfo* CInputMgr::FindKey(const string& tStrKey) const
{
	// O(1)�� �˻�
	unordered_map<string, SKeyInfo*>::const_iterator tItor = mMapKeys.find(tStrKey);
	
	if (tItor == mMapKeys.end())
	{
		return nullptr;
	}

	// first : Ű, second : ��(���� ������)
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
