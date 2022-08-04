#pragma once

#include "ryumacro.h"

#include <windows.h>

#include <unordered_map>
using namespace std;

class CTexture;
class CAPIEngine;

class CResourcesMgr
{
private:
	//�ؽ���(�̹��� ������)���� �����ϱ� ���� �ڷᱸ��
	//Ű: ���ڿ� Ÿ��
	//��: CTexture��ü�� �ּҰ�
	unordered_map<string, CTexture*> mTexs;

	CAPIEngine* mpEngine = nullptr;

public:

	void Create(CAPIEngine* tpEngine);

	CTexture* FindTexture(const string& tStrKey);

	//tStrKey: �ش� �ؽ��� �������� �˻� Ű, ���ڿ� Ÿ�� 
	//tpFileName: �ش� �ؽ��� ������(�̹��� ������)�� ��� �����̸�, �����ڵ带 ����� C ��Ÿ�� ���ڿ�
	//tStrPathKey: ���� ��� �� Ű, ���ڿ� Ÿ�� 
	CTexture* LoadTexture(const string& tStrKey, const wchar_t* tpFileName, const string& tStrPathKey);



	SINGLETON_DECLARE(CResourcesMgr)
};

