#include "framework.h"
#include "main.h"
#include "CAPI_Engine.h"
#include "CUnit.h"
#include "CTexture.h"
#include "CObjectAPI.h"
#include "APIMacro.h"
#include "CInputMgr.h"
#include "CActor.h"
#include "CBullet.h"

// API ref
#include <list>
#include <vector>
using namespace std;

#pragma comment(lib, "WinApiEngine.lib")

/*
    // winAPIShootor step1

    이번 예시에서는 다음의 사항들을 만들어보자.

    i) 주인공 기체의 일반탄환 발사

       제작시 정해진 방향으로 발사되는 탄환을 '일반탄환' 이라 칭하겠다.
       주인공 기체의 일반탄환 은 '윗쪽 방향'으로 '발사'된다.

        //ryu_0

    ii) 연사

        //ryu_1

    iii) 주인공 기체의 좌우 경계처리

        //ryu_2

*/

class CAPIEngine : public CAPI_Engine
{
public:
    CTexture* mpTexture = nullptr;
    // API bullets
    CTexture* mpTexBullet = nullptr;

    // 프리팹 : 원본객체
    CUnit* PFActor = nullptr;
    // API bullets
    CUnit* PFBullet = nullptr;

    // 실제 게임월드에 배치될 주인공 객체
    CActor* mpActor = nullptr;

    // API bullets
    vector<CBullet*> mBullets;
    
    list<CObjectAPI*> mObjectApi;

public:

    CAPIEngine()
    {

    }
    virtual ~CAPIEngine() // 가상소멸자
    {

    }

    // 복사생성과 복사대입을 금지하기 위해서 private로 접근제한하였다
private:
    CAPIEngine(const CAPIEngine& tEngine) {};
    CAPIEngine& operator=(const CAPIEngine& tEngine) {};

public:
    virtual void OnCreate() override
    {
        CAPI_Engine::OnCreate();
        
        CInputMgr::GetInst()->Create(mhWnd);
        CInputMgr::GetInst()->AddKey("OnMoveLeft", 'A');
        CInputMgr::GetInst()->AddKey("OnMoveRight", 'D');
        CInputMgr::GetInst()->AddKey("OnFire", VK_SPACE);
        CInputMgr::GetInst()->AddKey("OnTest", VK_LCONTROL, 'G');


        // todo
        WCHAR szTemp[256] = { 0 };
        wsprintf(szTemp, L"CAPIEngine::Create\n");
        OutputDebugString(szTemp);

        mpTexture = new CTexture();
        mpTexture->LoadTexture(this->hInst, this->mhDC, TEXT("resources/bongbong_0.bmp"));
        // 원본객체 : CActor 타입의 프리팹 생성
        PFActor = CreatePrefab<CActor>(mpTexture, 0.5f, 0.5f, SVector2D(400.0f, 500.0f));

        mpTexBullet = new CTexture();
        mpTexBullet->LoadTexture(this->hInst, this->mhDC, TEXT("resources/bongbullet.bmp"));
        // 원본객체 : CActor 타입의 프리팹 생성
        PFBullet = CreatePrefab<CBullet>(mpTexBullet, 0.5f, 0.5f, SVector2D(400.0f, 500.0f));

        // 주인공 게임 객체 하나를 복제로 생성
        mpActor = InstantObject<CActor>(PFActor);
        mpActor->AddRef();

        // API bullets
        CBullet* tpBullet = nullptr;
        for (int ti = 0; ti < 10; ++ti)
        {
            tpBullet = InstantObject<CBullet>(PFBullet);
            tpBullet->AddRef();

            // 탄환은 생성시 비활성으로
            tpBullet->SetIsActive(false);


            mBullets.push_back(tpBullet);
            tpBullet->AddRef();

            tpBullet->Release(); // 지역변수 tpBullet에 대한 Release
            tpBullet = nullptr;
        }
        
    }

    virtual void OnDestroy() override
    {
        // API bullets
        vector<CBullet*>::iterator tItorBullet;
        for (tItorBullet = mBullets.begin(); tItorBullet != mBullets.end(); ++tItorBullet)
        {
                DestroyObject(*tItorBullet);
        }
        mBullets.clear();

        DestroyObject(mpActor);

        
        //SAFE_DELETE(PFActor)
        DestroyPrefab(PFActor);
        
        if (nullptr != mpTexture)
        {
            delete mpTexture;
            mpTexture = nullptr;
        }

        CAPI_Engine::OnDestroy();
    }

    virtual void OnUpdate(float tDeltaTime) override
    {
        CAPI_Engine::OnUpdate(tDeltaTime);

        // todo
        
        CInputMgr::GetInst()->Update();

        if (CInputMgr::GetInst()->KeyPress("OnMoveLeft"))
        {            
            mpActor->SetVelocity(SVector2D(-250.f, 0.0f));
            mpActor->Update(tDeltaTime);
        }

        if (CInputMgr::GetInst()->KeyPress("OnMoveRight"))
        {
            mpActor->SetVelocity(SVector2D(+250.f, 0.0f));
            mpActor->Update(tDeltaTime);
        }

        if (CInputMgr::GetInst()->KeyUp("OnFire"))
        {
            OutputDebugString(L"Skill_00\n");

            mpActor->DoFire(mBullets);
        }

        if (CInputMgr::GetInst()->KeyDown("OnTest"))
        {
            OutputDebugString(L"TEST.................\n");
        }

        // update
        vector<CBullet*>::iterator t;
        for (t = mBullets.begin(); t != mBullets.end(); ++t)
        {
            (*t)->Update(tDeltaTime);
        }

        // render
        this->Clear(0.0f, 0.0f, 0.2f);

        mpActor->Render();

        vector<CBullet*>::iterator tItorBullet;
        for (tItorBullet = mBullets.begin(); tItorBullet != mBullets.end(); ++tItorBullet)
        {
            (*tItorBullet)->Render();
        }

        this->Present();
        
    }
};

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    CAPIEngine tEngine;
    tEngine.Create(hInstance, nCmdShow);

    MSG msg = { 0 };
    msg = tEngine.Run();

    //// 이런 경우를 허용하지 말자
    //CAPIEngine tB = tEngine; // 복사생성자
    //CAPIEngine tA;
    //tEngine = tA; // 복사대입연산자

    return (int)msg.wParam;
}

// CObgectTywcmailcom