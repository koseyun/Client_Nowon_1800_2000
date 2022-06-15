#include "framework.h"
#include "main.h"
#include "CAPI_Engine.h"
#include "CUnit.h"

/*
    // step4

    테스트용 게임으로 슈팅게임을 가정하고 있다

    CUnit 클래스를 만들어 게임 오브젝트를 모사해보자

    i) CUnit 클래스를 만들어 추가한다
    기본적으로 이것은 월드에 위치해야 하므로 위치정보가 필요하다
    이 월드는 '연속적인 공간'을 가정하므로 위치정보는 '실수'타입으로 디자인한다
*/

class CAPIEngine : public CAPI_Engine
{
public:
    CUnit* mpUnit = nullptr;

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
        mpUnit = new CUnit();
    }

    virtual void OnDestroy() override
    {
        // todo
        if (nullptr != mpUnit)
        {
            delete mpUnit;
            mpUnit = nullptr;
        }

        CAPI_Engine::OnDestroy();               
    }

    virtual void OnUpdate() override
    {
        CAPI_Engine::OnUpdate();

        // todo
        mpUnit->Render();

        //TextOut(mhDC, 0, 0, TEXT("test text output."), 17);
        //TextOut(mhDC, 0, 25, TEXT("안녕하세요.폭풍류입니다."), 13);
        //TextOut(mhDC, 0, 50, TEXT("I am a good boy."), 16);

        //LPCWSTR tString = TEXT("WCHAR Test"); // const WCHAR*
        //TextOut(mhDC, 0, 100, tString, 10);

        //// 사각형 그리기
        //Rectangle(mhDC, 200, 200, 200 + 100, 200 + 50);

        //// 선분 그리기
        //MoveToEx(mhDC, 350, 200, NULL); // 시작점 설정
        //LineTo(mhDC, 450, 300); // 끝점 설정

        //MoveToEx(mhDC, 200, 50, NULL); // 시작점 설정
        //LineTo(mhDC, 400, 100); // 끝점 설정
        //LineTo(mhDC, 200, 150); // 끝점 설정

        //// 원(타원) 그리기
        //Ellipse(mhDC, 400, 100, 400 + 100, 100 + 100);
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