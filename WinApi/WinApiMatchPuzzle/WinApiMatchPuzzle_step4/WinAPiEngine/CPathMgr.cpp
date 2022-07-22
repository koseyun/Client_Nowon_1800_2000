#include "CPathMgr.h"

SINGLETON_DEFINITION(CPathMgr)

CPathMgr::CPathMgr()
{
	mPaths.clear();
}

CPathMgr::~CPathMgr()
{
	mPaths.clear();
}

bool CPathMgr::Create()
{
	// ���� ������ �ִ� ��θ� ��ڴ�
	// ���� ���������� �������� ���丮(����)�� ������ ��ü ��θ� ��´�
	
	wchar_t tStrPath[MAX_PATH] = { 0 };

	GetModuleFileName(nullptr, tStrPath, MAX_PATH);

	WCHAR szTemp[MAX_PATH] = { 0 };
	wsprintf(szTemp, L"%s\n", tStrPath);
	OutputDebugString(szTemp);

	return true;
}

bool CPathMgr::MakePath(const string& tStrKey, const wchar_t* tpPath, const string& tStrBaseKey)
{
	return true;
}

const wchar_t* CPathMgr::FindPath(const string& tStrKey)
{
	return nullptr;
}
