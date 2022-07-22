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

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    //LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    //LoadStringW(hInstance, IDC_WINAPIENGINESTEP0, szWindowClass, MAX_LOADSTRING);
    wsprintf(szTitle, L"WinApiEngine");
    wsprintf(szWindowClass, L"WinApiEngineWC");

    MyRegisterClass(hInstance);    

    // ���ø����̼� �ʱ�ȭ�� �����մϴ�:
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
        // ������ �޽��� ť�� �޽����� ������ �������� true �� �����Ѵ�
        // ������ �޽��� ť�� �޽����� ������ false �� �����Ѵ� (�ͺ�)
        // 
        // PM_REMOVE ������ �޽��� ť���� �޽����� ���� ���, �ش� �޽����� ť���� �����Ѵ�
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            // DeltaTime(�� �����ӿ� �ɸ��� �ð�)�� ���Ѵ�
            LARGE_INTEGER tTime;
            QueryPerformanceCounter(&tTime);

            mDeltaTime = (float)(tTime.QuadPart - mTime.QuadPart) / (float)mSecond.QuadPart;

            mTime = tTime;
            // ���� ���� ������ �⺻������ �ۼ��Ͽ���
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
//  �Լ�: MyRegisterClass()
//
//  �뵵: â Ŭ������ ����մϴ�.
//
ATOM CAPI_Engine::MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc; // lpfnWndProc �� �����Լ��� �Լ������ʹ�
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
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   �뵵: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   �ּ�:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL CAPI_Engine::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

    mhWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!mhWnd)
    {
        return FALSE;
    }
    
    // Ŭ���̾�Ʈ ������ ũ�⸦ �̰����� �� ���̴�
    RECT tRect = { 0, 0, 800, 600 };
    // Ÿ��Ʋ��, �޴� ���� ����Ͽ� ��ü ������ ������ �ٽ� ������ش�
    AdjustWindowRect(&tRect, WS_OVERLAPPEDWINDOW, FALSE);
    // ������ ����� ���� ������, ������ ũ��� ��ġ�� �ٽ� �����Ѵ�
    SetWindowPos(mhWnd, HWND_TOPMOST, 100, 100, tRect.right - tRect.left, tRect.bottom - tRect.top, SWP_NOMOVE | SWP_NOZORDER);
    //                                                          ����                      ����



    ShowWindow(mhWnd, nCmdShow);
    UpdateWindow(mhWnd);

    return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �뵵: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���ø����̼� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK CAPI_Engine::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    
    // ������ ������� ���, ȭ�鿡 �׸� �ʿ伺�� �ִٸ�, �� �޽����� ���´�
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        // DC(Device Context) �� handle : DC �� �׸��⿡ ����ϴ� ��ġ(��ġ, ��ġ�� ���õ� ������, ��ġ�� ����)�� �߻�ȭ �س��� ���̴�
        HDC hdc = BeginPaint(hWnd, &ps); // �׸��� ��带 ������
        // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...

        
        EndPaint(hWnd, &ps); // �׸��� ��尡 �����ٴ� �ǹ�
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

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
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
    BitBlt(this->mpBackBuffer->mhDCMem, // ����ȭ�� DC
            //100, 100,
        tX, tY,
        //0, 0,
        tpTexture->mBitmapInfo.bmWidth, tpTexture->mBitmapInfo.bmHeight,
        tpTexture->mhDCMem, // �޸� DC
        0, 0, SRCCOPY);
}

void CAPI_Engine::Clear(float tR, float tG, float tB)
{
    //Rectangle(mhDC, 0, 0, 800, 600);
    //Rectangle(mpBackBuffer->mhDCMem, 0, 0, 800, 600);

    // ������ ���� ������ ���������ϴ�
    HPEN hPen; // ���ο� ���ڵ�
    HPEN hPenOld; // ������ ���� ���ڵ� ����

    HBRUSH hBrush; // ���ο� �귯�� �ڵ�
    HBRUSH hBrushOld; // ������ ���� �귯�� �ڵ� ����

    // �����θ� �� �׸���
    HDC thDC = this->mpBackBuffer->mhDCMem;

    hBrush = CreateSolidBrush(RGB(tR * 255, tG * 255, tB * 255)); // RGB ��ũ�δ� 256�ܰ��� ������ �䱸�Ѵ�
    hPen = CreatePen(PS_SOLID, 2, RGB(tR * 255, tG * 255, tB * 255)); // �� ��Ÿ��, ����, ����
    // hbr = (HBRUSH)GetStockObject(NULL_BRUSH); // ���� ä���� ������ �Ѵٸ� �̰�����
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
    BitBlt(mhDC, // ���� dc
        0, 0, 800, 600, mpBackBuffer->mhDCMem, 0, 0, SRCCOPY);
}
