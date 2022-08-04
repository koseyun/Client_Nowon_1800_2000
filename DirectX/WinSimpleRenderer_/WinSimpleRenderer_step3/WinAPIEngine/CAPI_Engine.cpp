#include "CAPI_Engine.h"
//#include "Resource.h"
#include "CTexture.h"
#include "CInputMgr.h"
#include "CObjectAPI.h"
#include "CCollisionMgr.h"
#include "CPathMgr.h"
#include "CResourcesMgr.h"

HINSTANCE CAPI_Engine::hInst = nullptr;

CAPI_Engine::CAPI_Engine()
{
    memset(szTitle, 0, MAX_LOADSTRING*sizeof(WCHAR));                  // 제목 표시줄 텍스트입니다.
    memset(szWindowClass, 0, MAX_LOADSTRING * sizeof(WCHAR));            // 기본 창 클래스 이름입니다.
}
CAPI_Engine::~CAPI_Engine()
{
}

void CAPI_Engine::OnCreate()
{
    //MessageBox()
    WCHAR szTemp[256] = { 0 };
    wsprintf(szTemp, L"Create\n");
    OutputDebugStringW(szTemp);
}
void CAPI_Engine::OnDestroy()
{
    WCHAR szTemp[256] = { 0 };
    wsprintf(szTemp, L"Destroy\n");
    OutputDebugStringW(szTemp);
}
void CAPI_Engine::OnUpdate(float tDeltaTime)
{
    
}

void CAPI_Engine::DrawCircle(float tX, float tY, float tRadius)
{
    //Ellipse(mpBackBuffer->mhDCMem, tX - tRadius, tY - tRadius, tX + tRadius, tY + tRadius);

    HPEN hPen;
    HPEN hPenOld;

    HBRUSH hBrush;
    HBRUSH hBrushOld;

    HDC thDC = this->mpBackBuffer->mhDCMem;

    hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));	// 선 스타일, 굵기, 색상
    hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);	//색을 채우지 않으려 한다면 이것으로
    hBrushOld = (HBRUSH)::SelectObject(thDC, hBrush);
    hPenOld = (HPEN)::SelectObject(thDC, (HGDIOBJ)hPen);

        Ellipse(mpBackBuffer->mhDCMem, tX - tRadius, tY - tRadius, tX + tRadius, tY + tRadius);

    hBrush = (HBRUSH)::SelectObject(thDC, hBrushOld);
    hPen = (HPEN)::SelectObject(thDC, hPenOld);

    DeleteObject(hBrush);
    DeleteObject(hPen);
}

void CAPI_Engine::Clear(float tR, float tG, float tB)
{
    HPEN hPen;
    HPEN hPenOld;

    HBRUSH hBrush;
    HBRUSH hBrushOld;

    HDC thDC = this->mpBackBuffer->mhDCMem;

    hBrush = CreateSolidBrush(RGB(tR*255, tG*255, tB*255));
    hPen = CreatePen(PS_SOLID, 2, RGB(tR * 255, tG * 255, tB * 255));	// 선 스타일, 굵기, 색상
    //hbr = (HBRUSH)GetStockObject(NULL_BRUSH);	//색을 채우지 않으려 한다면 이것으로
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
    BitBlt(mhDC,
        0, 0,
        800, 600,
        mpBackBuffer->mhDCMem,
        0, 0,
        SRCCOPY);
}

void CAPI_Engine::DrawTexture(float tX, float tY, CTexture* tpTex, COLORREF tColorKey)
{
    TransparentBlt(this->mpBackBuffer->mhDCMem,
        tX, tY,
        tpTex->mBitmapInfo.bmWidth, tpTex->mBitmapInfo.bmHeight,
        tpTex->mhDCMem,
        0, 0,

        tpTex->mBitmapInfo.bmWidth, tpTex->mBitmapInfo.bmHeight,
        RGB(255, 0, 255));
        //tColorKey);
        //RGB(255,255,255));
}

void CAPI_Engine::DrawTexturePartial(float tX, float tY, CTexture* tpTex, int tRow, int tCol,int tIndex, COLORREF tColorKey)
{
    //한 스프라이트 프레임의 너비와 높이를 구한다
    int tSrcWidth = tpTex->mBitmapInfo.bmWidth/tCol;
    int tSrcHeight = tpTex->mBitmapInfo.bmHeight/tRow;


    //현재 행과 열을 구한다
    int tCurRow = tIndex / tCol;
    int tCurCol = tIndex % tCol;
    //현재 스프라이트 프레임의 위치를 구한다
    int tSrcX = tCurCol*tSrcWidth;
    int tSrcY = tCurRow*tSrcHeight;

    TransparentBlt(this->mpBackBuffer->mhDCMem,
        
        tX, tY,
        tSrcWidth, tSrcHeight,
        
        tpTex->mhDCMem,
     
        tSrcX, tSrcY,
        tSrcWidth, tSrcHeight,
        RGB(255, 0, 255));
        //tColorKey);

    /*TransparentBlt(this->mpBackBuffer->mhDCMem,
        tX, tY,
        tpTex->mBitmapInfo.bmWidth, tpTex->mBitmapInfo.bmHeight,
        tpTex->mhDCMem,
        0, 0,

        tpTex->mBitmapInfo.bmWidth, tpTex->mBitmapInfo.bmHeight,
        tColorKey);*/
}

BOOL CAPI_Engine::Create(HINSTANCE hInstance, int nCmdShow)
{
    /*LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPITRANING00, szWindowClass, MAX_LOADSTRING);*/

    wsprintf(szTitle, L"winAPIShootor");    //매개변수로 받아 설정도 가능하겠다.
    wsprintf(szWindowClass, L"winAPIShootor");    //매개변수로 받아 설정도 가능하겠다.


    MyRegisterClass(hInstance);

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
    mpBackBuffer->CreateBackBuffer(hInst, mhDC);
    //mpBackBuffer->LoadTexture(hInst, mhDC, TEXT("resources/backbuffer_0.bmp"));

    CPathMgr::GetInstance()->Create();
    CResourcesMgr::GetInstance()->Create(this);

    CInputMgr::GetInstance();
    CCollisionMgr::GetInstance();

    OnCreate();

    QueryPerformanceFrequency(&mSecond);
    QueryPerformanceCounter(&mTime);

    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            LARGE_INTEGER tTime;
            QueryPerformanceCounter(&tTime);
            mDeltaTime = (float)(tTime.QuadPart - mTime.QuadPart) / (float)mSecond.QuadPart;
            mTime = tTime;

            CCollisionMgr::GetInstance()->Update(mDeltaTime);

            OnUpdate(mDeltaTime);

        }
    }

    OnDestroy();

    CResourcesMgr::ReleaseInstance();
    CPathMgr::ReleaseInstance();

    CCollisionMgr::ReleaseInstance();
    CInputMgr::ReleaseInstance();

    if (nullptr != mpBackBuffer)
    {
        delete mpBackBuffer;
        mpBackBuffer = nullptr;
    }

    ReleaseDC(mhWnd, mhDC);

    return msg;
}

ATOM CAPI_Engine::MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc; // nullptr;//WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, nullptr); //MAKEINTRESOURCE(IDI_WINAPITRANING00));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr; //MAKEINTRESOURCEW(IDC_WINAPITRANING00);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, nullptr); //MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL CAPI_Engine::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    mhWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!mhWnd)
    {
        return FALSE;
    }

    SetWindowText(mhWnd, L"CAPIEngine test titlebar text");
        
    RECT tRect = { 0,0,800,600 };
    //다음 함수를 호출하면 타이틀바, 메뉴 등까지 고려하여 다시 계산해준다
    AdjustWindowRect(&tRect, WS_OVERLAPPEDWINDOW, FALSE);

    //윈도우 크기를 설정한다
    SetWindowPos(mhWnd, HWND_TOPMOST, 100, 100, tRect.right - tRect.left, tRect.bottom - tRect.top, SWP_NOMOVE | SWP_NOZORDER);

    ShowWindow(mhWnd, nCmdShow);
    UpdateWindow(mhWnd);

    return TRUE;
}

LRESULT CALLBACK CAPI_Engine::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;


    case WM_TIMER:
    {
        OutputDebugString(L">>>>>>WM_TIMER Enemy DoFire~!!!!!\n");
    }
    break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// win api 함수들을 이용하여(여기서는 직선그리기 함수 이용) 선으로만 삼각형을 그린다
void CAPI_Engine::DrawTriangle(int x_0, int y_0, int x_1, int y_1, int x_2, int y_2, float tR, float tG, float tB)
{
    int tThickness = 1;

    HPEN hPen;
    HPEN hPenOld;

    hPen = CreatePen(PS_SOLID, tThickness, RGB(tR * 255, tG * 255, tB * 255));
    hPenOld = (HPEN)::SelectObject(this->mpBackBuffer->mhDCMem, (HGDIOBJ)hPen);

    POINT tPoint = { 0,0 };
    MoveToEx(this->mpBackBuffer->mhDCMem, x_0, y_0, &tPoint);
    LineTo(this->mpBackBuffer->mhDCMem, x_1, y_1);
    LineTo(this->mpBackBuffer->mhDCMem, x_2, y_2);
    LineTo(this->mpBackBuffer->mhDCMem, x_0, y_0);

    hPen = (HPEN)::SelectObject(this->mpBackBuffer->mhDCMem, hPenOld);

    DeleteObject(hPen);
}

void CAPI_Engine::FillTriangle(int x_0, int y_0, int x_1, int y_1, int x_2, int y_2, float tR, float tG, float tB)
{
    // 점들의 정보를 구축
    // 정점의 정보
    TRIVERTEX vertex[3];
    vertex[0].x = x_0;
    vertex[0].y = y_0;
    vertex[0].Red = 0xffff * tR;
    vertex[0].Green = 0xffff * tG;
    vertex[0].Blue = 0xffff * tB;
    vertex[0].Alpha = 0x0000;

    vertex[1].x = x_1;
    vertex[1].y = y_1;
    vertex[1].Red = 0xffff * tR;
    vertex[1].Green = 0xffff * tG;
    vertex[1].Blue = 0xffff * tB;
    vertex[1].Alpha = 0x0000;

    vertex[2].x = x_2;
    vertex[2].y = y_2;
    vertex[2].Red = 0xffff * tR;
    vertex[2].Green = 0xffff * tG;
    vertex[2].Blue = 0xffff * tB;
    vertex[2].Alpha = 0x0000;

    GRADIENT_TRIANGLE tTriangle;
    // 인덱스 : 정점의 정보를 참고하는 번호
    tTriangle.Vertex1 = 0;
    tTriangle.Vertex2 = 1;
    tTriangle.Vertex3 = 2;

    HDC thDC = this->mpBackBuffer->mhDCMem;

    GradientFill(this->mpBackBuffer->mhDCMem, vertex, 3, &tTriangle, 1, GRADIENT_FILL_TRIANGLE);
}
