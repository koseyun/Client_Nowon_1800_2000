#pragma once
#include <windows.h>
#include <vector>
#include <unordered_map>
#include <string>
#include <typeinfo>
#include "APIMacro.h"

using namespace std;

struct SKeyInfo
{
	string mStrName;			//Ű
	vector<DWORD> mKeyInputs;		//������
	//DWORD mKeyInput;					//������

	bool mIsDown;
	bool mIsPress;
	bool mIsUp;

	SKeyInfo()
		:mIsDown(false), mIsPress(false), mIsUp(false)
	{
		mStrName = "";
		mKeyInputs.clear();
	}
};

class CInputMgr
{
	SINGLETON_DECLARE(CInputMgr)

private:
	HWND mhWnd;

	//�ؽ����̺��� ���� ���̴�. O(1)�� ������ ����
	unordered_map<string, SKeyInfo*> mMapKeys;

	SKeyInfo* mpKeyInfo = nullptr;

public:
	virtual void Create(HWND hWnd);
	void Update();

	SKeyInfo* FindKey(const string& tStrKey) const
	{
		unordered_map<string, SKeyInfo*>::const_iterator tItor =
			mMapKeys.find(tStrKey);

		if (tItor == mMapKeys.end())
		{
			return nullptr;
		}

		return tItor->second;
	}

	bool KeyDown(const string& tStrKey) const;
	bool KeyPress(const string& tStrKey) const;
	bool KeyUp(const string& tStrKey) const;

	template<typename T>
	bool AddKey(const T& tData)
	{
		const char* tpType = typeid(T).name();

		if (strcmp(tpType, "char") == 0 ||
			strcmp(tpType, "int") == 0)
		{
			//Ű ���
			//DWORD�� ��ȯ
			mpKeyInfo->mKeyInputs.push_back((DWORD)tData);
		}
		else
		{
			//�߻�ȭ �̸� ��� 
			mpKeyInfo->mStrName = tData;

			mMapKeys.insert(
				make_pair(mpKeyInfo->mStrName, mpKeyInfo)
			);
		}

		return true;
	}

	template<typename T, typename... Types>
	bool AddKey(const T& tData, const Types&... arg)
	{
		if (!mpKeyInfo)
		{
			mpKeyInfo = new SKeyInfo();
		}

		const char* tpType = typeid(T).name();

		if (strcmp(tpType, "char") == 0 ||
			strcmp(tpType, "int") == 0)
		{
			//Ű ���
			//DWORD�� ��ȯ
			mpKeyInfo->mKeyInputs.push_back((DWORD)tData);
		}
		else
		{
			//�߻�ȭ �̸� ��� 
			mpKeyInfo->mStrName = tData;

			mMapKeys.insert(
				make_pair(mpKeyInfo->mStrName, mpKeyInfo)
			);
		}

		//��������� ȣ�� recursive case
		AddKey(arg...);

		//������� ���� ���ȣ���� ���� ���̴� 
		if (mpKeyInfo)
		{
			mpKeyInfo = nullptr;
		}

		return true;
	}
};
