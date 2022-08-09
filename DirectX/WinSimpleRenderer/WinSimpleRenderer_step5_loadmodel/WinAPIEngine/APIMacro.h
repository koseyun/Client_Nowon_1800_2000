#pragma once

#define SAFE_DELETE(p) if(nullptr != p) { delete p; p = nullptr; }

// ��ũ�� �Լ� ������ �⺻�� �� �������� 
// ������ ǥ���Ϸ��� \�� �̾ �ϸ� ���ٷ� �ν��Ѵ�
#define SAFE_DELETE_RYU(p) \
    if(nullptr != p)\
    { \
        delete p;\
        p = nullptr; \
    }

#define SINGLETON_DECLARE(p) private:\
    static p* mpInstance;\
private:\
    p();\
    ~p();\
public:\
    static p* GetInstance();\
    static void ReleaseInstance();

#define SINGLETON_DEFINITION(p) p* p::mpInstance = nullptr;\
p* p::GetInstance()\
{\
if (nullptr == mpInstance)\
{\
	mpInstance = new p();\
}\
return mpInstance;\
}\
void p::ReleaseInstance()\
{\
	if (nullptr != mpInstance)\
	{\
		delete mpInstance;\
	}\
}

#define ROOT_PATH "root_path"
#define RESOURCES_PATH "resources_path"
// ��ũ�� ���Ƿ� ���� ������ ����� �� �ֵ��� ��
#define FIND_TEX(p) CResourcesMgr::GetInstance()->FindTexture(p)