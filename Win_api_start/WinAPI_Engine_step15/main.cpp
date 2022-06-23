#include "framework.h"
#include "main.h"
#include "CAPI_Engine.h"
#include "CUnit.h"
#include "CTexture.h"
#include "CObjectAPI.h"
#include "APIMacro.h"
#include "CInputMgr.h"

#include <list>
using namespace std;

/*
    // step15

    이번 예시에서는 '시간기반진행'을 위한 구조를 작성해보자
    이를 위해서  를 사용하기로 한다
    왜냐하면 보다 정밀한 타이머를 이용하기 위해서이다

    QueryPerformanceFrequency(&mSecond);
    QueryPerformanceCounter(&mTime);

    QueryPerformanceCounter(&tTime);

    
    //ryu deltatime

*/

class CAPIEngine : public CAPI_Engine
{
public:
    CUnit* mpUnit = nullptr;
    CTexture* mpTexture = nullptr;

    // API ref
    /*
        Template : 일반화 프로그래밍 기법을 C++에 문법으로 만들어 놓은것 <-- 타입을 매개변수로 다루는 기법

        Standard Template Library
        STL의 3가지 구성요소

        i) 컨테이너 : 자료구조를 일반화시켜 만들어놓은것
        ii) 반복자 : 컨테이너와 알보리즘과 같이 사용할 수 있게 만들어진 일반화된 모니터
        iii) 알고리즘 : 알고리즘을 일반화시켜 만들어 놓은것

    */
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
        
        mpUnit = new CUnit();
        mpUnit->SetEngine(this);
        mpUnit->SetTexture(mpTexture);
        mpUnit->SetAnchors(0.5f, 0.5f);
        mpUnit->SetPosition(SVector2D(400.0f, 500.0f));


        // test
        CObjectAPI* tpObject = nullptr;
        tpObject = new CObjectAPI();
        tpObject->AddRef();

        CObjectAPI* tpA = nullptr;
        tpA = tpObject;
        tpA->AddRef();

        // API ref
        mObjectApi.push_back(tpObject);
        tpObject->AddRef();


        if (nullptr != tpA)
        {
            tpA->Release();
            tpA = nullptr; 
        }

        if (nullptr != tpObject)
        {
            tpObject->Release();
            tpObject = nullptr;
        }
        
    }

    virtual void OnDestroy() override
    {
        for (list<CObjectAPI*>::iterator tItor = mObjectApi.begin(); tItor != mObjectApi.end(); ++tItor)
        {
            if (nullptr != (*tItor))
            {
                (*tItor)->Release();
                (*tItor) = nullptr;
            }
        }

        // todo
        /*if (nullptr != mpUnit)
        {
            delete mpUnit;
            mpUnit = nullptr;
        }*/
        SAFE_DELETE(mpUnit)
        
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
        
        //if (GetAsyncKeyState('A') & 0x8000)
        //{
        //    // 현재위치 = 이전위치 + 속도
        //    //mpUnit->mPosition.mX = mpUnit->mPosition.mX - 0.01f;

        //    mpUnit->SetVelocity(SVector2D(-0.01f, 0.0f));
        //    mpUnit->Update();
        //}

        //if (GetAsyncKeyState('D') & 0x8000)
        //{
        //    //mpUnit->mPosition.mX = mpUnit->mPosition.mX + 0.01f;
        //    mpUnit->SetVelocity(SVector2D(+0.01f, 0.0f));
        //    mpUnit->Update();
        //}

        //if (GetAsyncKeyState(VK_SPACE) & 0x8000)
        //{
        //    OutputDebugString(L"Skill_00\n");
        //    MessageBox(NULL, L"skill_00", L"test", MB_OK);
        //}
        
        CInputMgr::GetInst()->Update();

        if (CInputMgr::GetInst()->KeyPress("OnMoveLeft"))
        {            
            mpUnit->SetVelocity(SVector2D(-250.f, 0.0f));
            mpUnit->Update();
        }

        if (CInputMgr::GetInst()->KeyPress("OnMoveRight"))
        {
            mpUnit->SetVelocity(SVector2D(+250.f, 0.0f));
            mpUnit->Update();
        }

        if (CInputMgr::GetInst()->KeyUp("OnFire"))
        {
            OutputDebugString(L"Skill_00\n");
        }

        if (CInputMgr::GetInst()->KeyDown("OnTest"))
        {
            OutputDebugString(L"TEST.................\n");
        }

        // update


        // render
        this->Clear(0.0f, 0.0f, 0.2f);

        mpUnit->Render();

        //this->DrawTexture(mpUnit->mX, mpUnit->mY, mpTexture);

        // 백버퍼에 그려진 내용을 현재화면 dc에 제출하자
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