#include "framework.h"
#include "main.h"
#include "CAPI_Engine.h"
#include "CUnit.h"
#include "CTexture.h"
#include "CObjectAPI.h"

/*
    // step9

    CUnit을 게임월드에 임의의 객체로 가정하고 지난 코드를 작성했다
    여기서는 CUnit이 가지게될 여러 기능들 중 일부를 구체화하여
    별도의 클래스로 만들고 상속시키겠다.


    i) vector 기본

        게임 프로그래밍에서 벡터의 개념은 필수이다
        여기서는 간단히 해당 예시에서 필요한 정도만 일단 만들어보겠다

        SVector2D


        이 예시에서 만들 연산은 다음과 같다

        -벡터의 덧셈(뺄셈)
        -벡터의 스칼라곱

    ii) reference counting

        여기서는 참조 카운트 reference counting을 이용하여 동적할당하는 메모리의 해제를 관리하는 클래스를 만들어 적용하겠다

        학습의 용도이며 실제로는 스마트 포인터를 사용해도 무방하겠다

        CObjectRyu



    //ryu ref object

    
*/

class CAPIEngine : public CAPI_Engine
{
public:
    CUnit* mpUnit = nullptr;
    CTexture* mpTexture = nullptr;

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


        // test
        CObjectAPI* tpObject = nullptr;
        tpObject = new CObjectAPI();
        tpObject->AddRef();

        CObjectAPI* tpA = nullptr;
        tpA = tpObject;
        tpA->AddRef();

        if (nullptr != tpA)
        {
            tpA->Release();
            tpA = nullptr;
        }

        if (nullptr != tpObject)
        {
            tpObject->Release();
            tpA = nullptr;
        }
        
    }

    virtual void OnDestroy() override
    {
        // todo
        if (nullptr != mpUnit)
        {
            delete mpUnit;
            mpUnit = nullptr;
        }
        
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
            mpUnit->mX = mpUnit->mX - 0.01f;
        }

        if (GetAsyncKeyState('D') & 0x8000)
        {
            mpUnit->mX = mpUnit->mX + 0.01f;
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