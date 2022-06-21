#include "framework.h"
#include "main.h"
#include "CAPI_Engine.h"
#include "CUnit.h"
#include "CTexture.h"
#include "CObjectAPI.h"
#include "APIMacro.h"

#include <list>
using namespace std;

/*
    // step12

    이번 예시에서는
    input 관리자를 만들도록 하자. 

    CInputMgr 클래스를 추가하고 
        singleton 패턴을 적용하도록 한다.

    i) singleton pattern을 적용하여 CInputMgr클래스를 작성한다

    ii) 매크로를 이용하여 코드량을 줄여본다.
    ( 다른 클래스에도 싱글턴 패턴을 적용하는 것을 가정 )

        ryumacro.h

        -먼저 SAFE_DELETE 로 테스트
        -SINGLETON_DECLARE, SINGLE_DEFINITION 
    
    //ryu singleton

*/

/*
    디자인 패턴 : 프로그램 구조 설계 방법 모음집
        <-- OOP를 기반으로 한다
        --> OOP의 모법답안집
    C언어의 프로그래밍 패러다임 : 구조화 프로그래밍 structured programming
    C++ 언어에서의 도입된 프로그래밍 패러다임 : OOP Object Oriented Programming 객체지향 프로그래밍

    타입을 매개변수로 다루는 기법
    일반화 프로그래밍 General Programming

     C++은 멀티프로그래밍 패러다임 의 언어이다



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

        // todo
        WCHAR szTemp[256] = { 0 };
        wsprintf(szTemp, L"CAPIEngine::Create\n");
        OutputDebugString(szTemp);


        mpTexture = new CTexture();
        mpTexture->LoadTexture(this->hInst, this->mhDC, TEXT("resources/bongbong_0.bmp"));
        
        mpUnit = new CUnit();
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

    virtual void OnUpdate() override
    {
        CAPI_Engine::OnUpdate();

        // todo
        
        if (GetAsyncKeyState('A') & 0x8000)
        {
            // 현재위치 = 이전위치 + 속도
            //mpUnit->mPosition.mX = mpUnit->mPosition.mX - 0.01f;
            
            mpUnit->SetVelocity(SVector2D(-0.01f, 0.0f));
            mpUnit->Update();
        }

        if (GetAsyncKeyState('D') & 0x8000)
        {
            //mpUnit->mPosition.mX = mpUnit->mPosition.mX + 0.01f;
            mpUnit->SetVelocity(SVector2D(+0.01f, 0.0f));
            mpUnit->Update();
        }

        if (GetAsyncKeyState(VK_SPACE) & 0x8000)
        {
            OutputDebugString(L"Skill_00\n");
            MessageBox(NULL, L"skill_00", L"test", MB_OK);
        }

        // update


        // render
        this->Clear(0.0f, 0.0f, 0.2f);

        mpUnit->Render(this);

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