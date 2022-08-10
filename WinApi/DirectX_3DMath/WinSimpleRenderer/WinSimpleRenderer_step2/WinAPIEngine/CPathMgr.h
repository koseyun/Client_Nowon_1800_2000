#pragma once
#include "APIMacro.h"
#include <windows.h>
#include <unordered_map>
using namespace std;

class CPathMgr
{
private:
	// Ű : ���ڿ� Ÿ��
	// �� : �����ڵ� ���ڿ� Ÿ��
	unordered_map<string, wstring> mPaths;

public:
	bool Create();
	// ������ ��θ� ����� �Լ�
	bool MakePath(const string& tStrKey, const wchar_t* tpPath, const string& tStrBaseKey);

public:
	// Path �˻�
	const wchar_t* FindPath(const string& tStrKey);

	SINGLETON_DECLARE(CPathMgr)
};
