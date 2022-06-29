#include "CAPI_Engine.h"
//#include "Resource.h"
#include "CTexture.h"
#include "CInputMgr.h"

HINSTANCE CAPI_Engine::hInst = nullptr;

CAPI_Engine::CAPI_Engine()
{
    memset(szWindowClass, 0, MAX_LOADSTRING * sizeof(WCHAR));
}

CAPI_Engine::~CAPI_Engine()
{
}

BOOL CAPI_Engine::Create(HINSTANCE hInstance, int nCmdShow)
{

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    //LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    //LoadStringW(hInstance, IDC_WINAPIENGINESTEP0, szWindowClass, MAX_LOADSTRING);
    wsprintf(szTitle, L"WinApiEngine");
    wsprintf(szWindowClass, L"WinApiEngineWC");

    MyRegisterClass(hInstance);    

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

	return TRUE;
}

MSG CAPI_Engine::Run()
{
	MSG msg = { 0 };

    mhDC = GetDC(mhWnd);
    
    mpBackBuffer = new CTexture();
    //mpBackBuffer->LoadTexture(hInst, mhDC, TEXT("resources/backbuffer_0.bmp"));
    mpBackBuffer->CreateBackBuffer(hInst, mhDC);
    
    CInputMgr::GetInst();

    OnCreate();

    //HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPIENGINESTEP0));
    //HACCEL hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(IDC_WINAPIENGINESTEP0));

    // API deltatime
    QueryPerformanceFrequency(&mSecond);
    QueryPerformanceCounter(&mTime);

    while (WM_QUIT != msg.message)
    {
        // PeekMessage
        // 윈도우 메시지 큐에 메시지가 있으면 가져오고 true 를 리턴한다
        // 윈도우 메시지 큐에 메시지가 없으면 false 를 리턴한다 (넌블럭)
        // 
        // PM_REMOVE 윈도우 메시지 큐에서 메시지의 값을 얻고, 해당 메시지를 큐에서 삭제한다
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            // DeltaTime(한 프레임에 걸리는 시간)을 구한다
            LARGE_INTEGER tTime;
            QueryPerformanceCounter(&tTime);

            mDeltaTime = (float)(tTime.QuadPart - mTime.QuadPart) / (float)mSecond.QuadPart;

            mTime = tTime;
            // 게임 루프 패턴의 기본구조를 작성하였다
            //OutputDebugString(L"game loop\n");
            OnUpdate(mDeltaTime);
        }
    }

    OnDestroy();

    CInputMgr::GetInst()->ReleaseInst();

    ReleaseDC(mhWnd, mhDC);


    //return (int)msg.wParam;

	return msg;
}

void CAPI_Engine::OnCreate()
{
    WCHAR szTemp[256] = { 0 };
    wsprintf(szTemp, L"CAPI_Engine::Create\n");
    OutputDebugString(szTemp);
}

void CAPI_Engine::OnDestroy()
{
    WCHAR szTemp[256] = { 0 };
    wsprintf(szTemp, L"CAPI_Engine::Destroy\n");
    OutputDebugString(szTemp);
}

void CAPI_Engine::OnUpdate(float tDeltaTime)
{
    //WCHAR szTemp[256] = { 0 };
    //wsprintf(szTemp, L"CAPI_Engine::OuUpdate\n");
    //OutputDebugString(szTemp);
}

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM CAPI_Engine::MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc; // lpfnWndProc 는 전역함수용 함수포인터다
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, nullptr); //MAKEINTRESOURCE(IDI_WINAPIENGINESTEP0));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName = nullptr; //MAKEINTRESOURCEW(IDC_WINAPIENGINESTEP0);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, nullptr); //MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL CAPI_Engine::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    mhWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!mhWnd)
    {
        return FALSE;
    }
    
    // 클라이언트 영역의 크기를 이것으로 쓸 것이다
    RECT tRect = { 0, 0, 800, 600 };
    // 타이틀바, 메뉴 등을 고려하여 전체 윈도우 영역을 다시 계산해준다
    AdjustWindowRect(&tRect, WS_OVERLAPPEDWINDOW, FALSE);
    // 위에서 계산한 값을 가지고, 윈도우 크기와 위치를 다시 세팅한다
    SetWindowPos(mhWnd, HWND_TOPMOST, 100, 100, tRect.right - tRect.left, tRect.bottom - tRect.top, SWP_NOMOVE | SWP_NOZORDER);
    //                                                          가로                      세로



    ShowWindow(mhWnd, nCmdShow);
    UpdateWindow(mhWnd);

    return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK CAPI_Engine::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    
    // 윈도우 응용앱의 경우, 화면에 그릴 필요성이 있다면, 이 메시지가 들어온다
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        // DC(Device Context) 의 handle : DC 는 그리기에 사용하는 장치(장치, 장치에 관련된 설정값, 장치의 상태)를 추상화 해놓은 것이다
        HDC hdc = BeginPaint(hWnd, &ps); // 그리기 모드를 시작함
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

        
        EndPaint(hWnd, &ps); // 그리기 모드가 끝났다는 의미
    }
    break;
    case WM_TIMER:
    {
        OutputDebugString(L">>>>>>WM_TIMER Enemy DoFire~!!!!!\n");
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
//INT_PTR CALLBACK CAPI_Engine::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    UNREFERENCED_PARAMETER(lParam);
//    switch (message)
//    {
//    case WM_INITDIALOG:
//        return (INT_PTR)TRUE;
//
//    case WM_COMMAND:
//        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//        {
//            EndDialog(hDlg, LOWORD(wParam));
//            return (INT_PTR)TRUE;
//        }
//        break;
//    }
//    return (INT_PTR)FALSE;
//}

void CAPI_Engine::DrawCircle(float tX, float tY, float tRadius)
{
    //Ellipse(mhDC, tX - tRadius, tY - tRadius, tX + tRadius, tY + tRadius);
    Ellipse(mpBackBuffer->mhDCMem, tX - tRadius, tY - tRadius, tX + tRadius, tY + tRadius);
}

void CAPI_Engine::DrawTexture(float tX, float tY, CTexture* tpTexture)
{
    BitBlt(this->mpBackBuffer->mhDCMem, // 현재화면 DC
            //100, 100,
        tX, tY,
        //0, 0,
        tpTexture->mBitmapInfo.bmWidth, tpTexture->mBitmapInfo.bmHeight,
        tpTexture->mhDCMem, // 메모리 DC
        0, 0, SRCCOPY);
}

void CAPI_Engine::Clear(float tR, float tG, float tB)
{
    //Rectangle(mhDC, 0, 0, 800, 600);
    //Rectangle(mpBackBuffer->mhDCMem, 0, 0, 800, 600);

    // 다음과 같이 색상을 설정가능하다
    HPEN hPen; // 새로운 펜핸들
    HPEN hPenOld; // 이전에 쓰던 펜핸들 기억용

    HBRUSH hBrush; // 새로운 브러쉬 핸들
    HBRUSH hBrushOld; // 이전에 쓰던 브러쉬 핸들 기억용

    // 선으로만 원 그리기
    HDC thDC = this->mpBackBuffer->mhDCMem;

    hBrush = CreateSolidBrush(RGB(tR * 255, tG * 255, tB * 255)); // RGB 매크로는 256단계의 색상을 요구한다
    hPen = CreatePen(PS_SOLID, 2, RGB(tR * 255, tG * 255, tB * 255)); // 선 스타일, 굵기, 색상
    // hbr = (HBRUSH)GetStockObject(NULL_BRUSH); // 색을 채우지 않으려 한다면 이것으로
    hBrushOld = (HBRUSH)::SelectObject(thDC, hBrush);
    hPenOld = (HPEN)::SelectObject(thDC, (HGDIOBJ)hPen);

        Rectangle(thDC, 0, 0, 800, 600);

    hBrush = (HBRUSH)::SelectObject(thDC, hBrushOld);
    hPen = (HPEN)::SelectObject(thDC, hPenOld);

    DeleteObject(hBrush);
    DeleteObject(hPen);
}

void CAPI_Engine::Present()
{
    BitBlt(mhDC, // 현재 dc
        0, 0, 800, 600, mpBackBuffer->mhDCMem, 0, 0, SRCCOPY);
}
