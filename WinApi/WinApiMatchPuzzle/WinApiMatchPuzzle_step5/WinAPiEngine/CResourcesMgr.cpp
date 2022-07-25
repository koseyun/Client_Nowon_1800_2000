#include "CResourcesMgr.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CAPI_Engine.h"

SINGLETON_DEFINITION(CResourcesMgr)

CResourcesMgr::CResourcesMgr()
{
	mTexs.clear();
}

CResourcesMgr::~CResourcesMgr()
{
	// �ؽ��� �޸𸮵��� �����Ѵ�
	// �ؽ��� �ڿ��� �����������̹Ƿ� ���⼭ �� ���� �����ϵ��� �ǵ��ߴ�
	unordered_map<string, CTexture*>::iterator tItor;
	for (tItor = mTexs.begin(); tItor != mTexs.end(); ++tItor)
	{
		SAFE_DELETE(tItor->second);
	}

	mTexs.clear();
}

void CResourcesMgr::Create(CAPI_Engine* tpEngine)
{
	mpEngine = tpEngine;
}

CTexture* CResourcesMgr::FindTexture(const string& tStrKey)
{
	unordered_map<string, CTexture*>::iterator tItor;

	tItor = mTexs.find(tStrKey);

	if (mTexs.end() == tItor)
	{
		return nullptr;
	}

	return tItor->second;
}

CTexture* CResourcesMgr::LoadTexture(const string& tStrKey, const wchar_t* tpFileName, const string& tStrPathKey)
{
	CTexture* tpTex = FindTexture(tStrKey);

	// �̹� ��ϵǾ� �ִ� �ؽ��� ���ҽ���� ã�� ���� �ٷ� ����
	if (tpTex)
	{
		return tpTex;
	}

	// ��ϵ� ���� �ƴ϶�� ���Ͽ��� �̹��� �����͸� �ε��Ͽ� ������ ����ϰ� ����
	tpTex = new CTexture();

	const wchar_t* tszTemp = nullptr;
	tszTemp = CPathMgr::GetInstance()->FindPath(tStrPathKey);
	wstring tString = tszTemp;
	tString += tpFileName;

	tpTex->LoadTexture(mpEngine->GetHInst(), mpEngine->GetHDC() , tString.c_str());

	mTexs.insert(make_pair(tStrKey, tpTex));

	return nullptr;
}
