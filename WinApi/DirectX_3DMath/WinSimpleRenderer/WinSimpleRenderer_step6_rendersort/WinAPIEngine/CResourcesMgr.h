#pragma once
#include "APIMacro.h"
#include <windows.h>
#include <unordered_map>
using namespace std;

class CTexture;
class CAPI_Engine;

class CResourcesMgr
{
private:
	// �ؽ���(�̹��� ������)���� �����ϱ� ���� �ڷᱸ��
	// Ű : ���ڿ� Ÿ��
	// �� : CTexture ��ü�� �ּҰ�
	unordered_map<string, CTexture*> mTexs;
	CAPI_Engine* mpEngine = nullptr;

public:
	void Create(CAPI_Engine* tpEngine);
	CTexture* FindTexture(const string& tStrKey);
	// tStrKEy : �ش� �ؽ��� �������� �˻� Ű, ���ڿ�Ÿ��
	// tpFileName : �ش� �ؽ��� ������(�̹��� ������)�� ��� �����̸�, �����ڵ带 ����� C ��Ÿ���� ���ڿ�
	// tStrPathKey : ���� ����� Ű, ���ڿ� Ÿ��
	CTexture* LoadTexture(const string& tStrKey, const wchar_t* tpFileName, const string& tStrPathKey);

	SINGLETON_DECLARE(CResourcesMgr)
};
