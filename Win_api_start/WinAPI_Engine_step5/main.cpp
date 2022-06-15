#include "framework.h"
#include "main.h"
#include "CAPI_Engine.h"
#include "CUnit.h"

/*
    // step5

    비트맵을 출력해보자

    이미지 저장방식 :
    i) 비트맵 방식 : 색상의 2차원 배열 모음
    ii) 벡터 방식 : 임의의 데이터를 해석해서 실시간으로 이미지 데이터를 만드는 방식

    비트맵 방식으로 제작된 이미지 데이터를 window api 를 이용해서 출력해보자

    i) memory dc 를 만든다
    ii) 비트맵을 로드한다(로드하여 생성한다) 리턴값은 비트맵 핸들이다
        -비트맵 핸들을 사용하여 비트맵 정보도 가져온다. 이것은 비트맵을 적합하게 출력하기 위해 정보가 필요해서이다

    iii) 비트맵 핸들을 memory dc 에 설정한다

        그린다

    GDI : Graphic Device Interface
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

        // input
        // GetAsyncKeyState 는 현재 키의 상태를 알아오는 함수이다
        /* 
            & 비트연산의 이유
            GetAsyncKeyState 의 리턴값은 다음과 같다
        
            0x0000: 이전에 눌림 없음. 호출시점에 눌림 없음 <-- 안눌림
            0x0001: 이전에 눌림 있음. 호출시점에 눌림 없음 <-- 떼어짐
            0x8000: 이전에 눌림 없음. 호출시점에 눌림 있음 <-- 새롭게 눌림
            0x8001: 이전에 눌림 있음. 호출시점에 눌림 있음 <-- 눌리고 있음

            이것을 알아오기 위함이다
        */

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


        mpUnit->Render(this);

        // memory dc 를 만든다
        HDC thDCMem = CreateCompatibleDC(this->mhDC);

        // 설정할 비트맵 도구를 생성한다
        // 여기서는 파일에서 로드하여 만드는 것을 가정하고 있다
        HBITMAP thBitmap = (HBITMAP)LoadImage(hInst, TEXT("resources/bongbong_0.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

        // 위에서 생성한 비트맵 도구를 현재 비트맵 도구로 설정한다
        // 리턴값으로는 이전에 사용하던 비트맵 도구가 리턴된다
        HBITMAP thOldBitmap = (HBITMAP)SelectObject(thDCMem, thBitmap);

        // 비트맵 도구의 핸들을 이용하여 BITMAP info 정보를 얻는다
        BITMAP tBitmapInfo;
        GetObject(thBitmap, sizeof(tBitmapInfo), &tBitmapInfo);

        OutputDebugString(L"width %d", tBitmapInfo.bmWidth);

        BitBlt(this->mhDC, // 현재화면 DC
            100, 100,
            //0, 0,
            tBitmapInfo.bmWidth, tBitmapInfo.bmHeight,
            thDCMem, // 메모리 DC
            0, 0, SRCCOPY);

        // 이전에 사용하던 비트맵 도구를 다시 현재 비트맵 도구로 설정하고
        SelectObject(thDCMem, thOldBitmap);
        // 현재 사용하던 비트맵 도구는 이제 해제한다
        DeleteObject(thBitmap);

        // DC 도 해제한다
        DeleteDC(thDCMem);

        
    }
};

    // OnUpdate() 함수 내의 todo
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
    //Ellipse(mhDC, 400, 100, 400 + 100, 100 + 100);3


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