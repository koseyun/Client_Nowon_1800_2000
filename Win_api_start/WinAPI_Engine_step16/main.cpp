#include "framework.h"
#include "main.h"
#include "CAPI_Engine.h"
#include "CUnit.h"
#include "CTexture.h"
#include "CObjectAPI.h"
#include "APIMacro.h"
#include "CInputMgr.h"
#include "CActor.h"

#include <list>
using namespace std;

/*
    // step16

    프로토타입 패턴을 적용해보기로 한다.

    Prefab 원본객체 라는 개념을 만들고

    이것을 복제하여 새로운 객체를 생성하는 형태를 취하기로 한다

    이러한 패턴을 적용하면
    1. 임의의 데이터 값들을 가지는 객체를 손쉽게 만들어내는 것이 가능하다
    2. 또한, 객체를 생성하는 부분의 코드를 보다 일반화하여 표현하는 것이 가능하다

    PFActor:CUnit 라는 이름으로 프리팹 개념을 만들고 이것을 복제하여
    mpActor:CActor 객체를 생성하여 테스트해본다

*/

class CAPIEngine : public CAPI_Engine
{
public:
    CTexture* mpTexture = nullptr;
    // 프리팹 : 원본객체
    CUnit* PFActor = nullptr;
    
    // 실제 게임얼드에 배치될 주인공 객체
    CActor* mpActor = nullptr;

    
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
        PFActor = new CActor(); 
        PFActor->SetEngine(this);
        PFActor->SetTexture(mpTexture);
        PFActor->SetAnchors(0.5f, 0.5f);
        PFActor->SetPosition(SVector2D(400.0f, 500.0f));

        // 주인공 게임 객체 하나를 복제로 생성
        mpActor = static_cast<CActor*>(PFActor->cloan());
        mpActor->AddRef();
        
    }

    virtual void OnDestroy() override
    {
        if (nullptr != mpActor)
        {
            mpActor->Release();
            mpActor = nullptr;
        }

        
        SAFE_DELETE(PFActor)
        
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
            mpActor->Update();
        }

        if (CInputMgr::GetInst()->KeyPress("OnMoveRight"))
        {
            mpActor->SetVelocity(SVector2D(+250.f, 0.0f));
            mpActor->Update();
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

        mpActor->Render();

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