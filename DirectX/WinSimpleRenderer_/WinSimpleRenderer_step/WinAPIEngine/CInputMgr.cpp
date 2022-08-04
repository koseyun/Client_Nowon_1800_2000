#include "CInputMgr.h"






SINGLETON_DEFINITION(CInputMgr)
//CInputMgr* CInputMgr::mpInstance = nullptr;

CInputMgr::CInputMgr()
{
	mhWnd = 0;

	mMapKeys.clear();

	mpKeyInfo = nullptr;
}
CInputMgr::~CInputMgr()
{
}



void CInputMgr::Create(HWND hWnd)
{
	mhWnd = hWnd;

}

void CInputMgr::Update()
{
	unordered_map<string, SKeyInfo*>::iterator tItor;

	for (tItor = mMapKeys.begin(); tItor != mMapKeys.end(); ++tItor)
	{
		int tPushCount = 0;

		//Ű�Է��� ���������� ���
		for (int ti = 0; ti < tItor->second->mKeyInputs.size(); ++ti)
		{
			// 0x8000 ������ ��������, ȣ���ÿ� ��������
			if (GetAsyncKeyState(tItor->second->mKeyInputs[ti]) & 0x8000)
			{
				++tPushCount;
			}
		}


		//if (1 <= tPushCount) //==
		//Ű�Է��� ���������� ���, Ű������ Ű������ŭ, �� Ű���� �Է¿� ���� 
		if( tPushCount == tItor->second->mKeyInputs.size() )
		{
			if (!tItor->second->mIsDown && !tItor->second->mIsPress)
			{
				//ó�� ���� ���̴�
				tItor->second->mIsDown = true;
			}
			else if (tItor->second->mIsDown && !tItor->second->mIsPress)
			{
				//������ �ִ� ���̴�
				tItor->second->mIsDown = false;
				tItor->second->mIsPress = true;
			}
		}
		else
		{
			if (tItor->second->mIsDown || tItor->second->mIsPress)
			{
				//������ ���̴�
				tItor->second->mIsDown = false;
				tItor->second->mIsPress = false;
				tItor->second->mIsUp = true;
			}
			else if (tItor->second->mIsUp)
			{
				//���� �ƹ� �Էµ� ���� ���̴�
				tItor->second->mIsUp = false;
			}
		}
	}


}



bool CInputMgr::KeyDown(const string& tStrKey) const
{
	SKeyInfo* tpInfo = FindKey(tStrKey);

	if (!tpInfo)
	{
		return false;
	}

	return tpInfo->mIsDown;
}
bool CInputMgr::KeyPress(const string& tStrKey) const
{
	SKeyInfo* tpInfo = FindKey(tStrKey);

	if (!tpInfo)
	{
		return false;
	}

	return tpInfo->mIsPress;
}
bool CInputMgr::KeyUp(const string& tStrKey) const
{
	SKeyInfo* tpInfo = FindKey(tStrKey);

	if (!tpInfo)
	{
		return false;
	}

	return tpInfo->mIsUp;
}
