#include "CAPIEngine.h"

//#include "Resource.h"


#include "CTexture.h"
#include "CInputMgr.h"

#include "CObjectRyu.h"



#include "CCollisionMgr.h"


HINSTANCE CAPIEngine::hInst = nullptr;

CAPIEngine::CAPIEngine()
{
    memset(szTitle, 0, MAX_LOADSTRING*sizeof(WCHAR));                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
    memset(szWindowClass, 0, MAX_LOADSTRING * sizeof(WCHAR));            // �⺻ â Ŭ���� �̸��Դϴ�.
}
CAPIEngine::~CAPIEngine()
{
}


void CAPIEngine::OnCreate()
{
    //MessageBox()
    WCHAR szTemp[256] = { 0 };
    wsprintf(szTemp, L"Create\n");
    OutputDebugStringW(szTemp);

    

}
void CAPIEngine::OnDestroy()
{
    

    WCHAR szTemp[256] = { 0 };
    wsprintf(szTemp, L"Destroy\n");
    OutputDebugStringW(szTemp);

}
void CAPIEngine::OnUpdate(float tDeltaTime)
{
    
}

void CAPIEngine::DrawCircle(float tX, float tY, float tRadius)
{
    //Ellipse(mpBackBuffer->mhDCMem, tX - tRadius, tY - tRadius, tX + tRadius, tY + tRadius);




    HPEN hPen;
    HPEN hPenOld;

    HBRUSH hBrush;
    HBRUSH hBrushOld;

    HDC thDC = this->mpBackBuffer->mhDCMem;

    hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));	// �� ��Ÿ��, ����, ����
    hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);	//���� ä���� ������ �Ѵٸ� �̰�����
    hBrushOld = (HBRUSH)::SelectObject(thDC, hBrush);
    hPenOld = (HPEN)::SelectObject(thDC, (HGDIOBJ)hPen);


        Ellipse(mpBackBuffer->mhDCMem, tX - tRadius, tY - tRadius, tX + tRadius, tY + tRadius);


    hBrush = (HBRUSH)::SelectObject(thDC, hBrushOld);
    hPen = (HPEN)::SelectObject(thDC, hPenOld);

    DeleteObject(hBrush);
    DeleteObject(hPen);
}

void CAPIEngine::Clear(float tR, float tG, float tB)
{
    HPEN hPen;
    HPEN hPenOld;

    HBRUSH hBrush;
    HBRUSH hBrushOld;

    HDC thDC = this->mpBackBuffer->mhDCMem;

    hBrush = CreateSolidBrush(RGB(tR*255, tG*255, tB*255));
    hPen = CreatePen(PS_SOLID, 2, RGB(tR * 255, tG * 255, tB * 255));	// �� ��Ÿ��, ����, ����
    //hbr = (HBRUSH)GetStockObject(NULL_BRUSH);	//���� ä���� ������ �Ѵٸ� �̰�����
    hBrushOld = (HBRUSH)::SelectObject(thDC, hBrush);
    hPenOld = (HPEN)::SelectObject(thDC, (HGDIOBJ)hPen);

        Rectangle(thDC, 0, 0, 800, 600);

    hBrush = (HBRUSH)::SelectObject(thDC, hBrushOld);
    hPen = (HPEN)::SelectObject(thDC, hPenOld);

    DeleteObject(hBrush);
    DeleteObject(hPen);
}

void CAPIEngine::Present()
{
    BitBlt(mhDC,
        0, 0,
        800, 600,
        mpBackBuffer->mhDCMem,
        0, 0,
        SRCCOPY);
}

void CAPIEngine::DrawTexture(float tX, float tY, CTexture* tpTex, COLORREF tColorKey)
{
    //ryu_colorkey
    /*BitBlt(this->mpBackBuffer->mhDCMem,
        tX, tY,
        tpTex->mBitmapInfo.bmWidth, tpTex->mBitmapInfo.bmHeight,
        tpTex->mhDCMem,
        0, 0, SRCCOPY);*/


    TransparentBlt(this->mpBackBuffer->mhDCMem,
        tX, tY,
        tpTex->mBitmapInfo.bmWidth, tpTex->mBitmapInfo.bmHeight,
        tpTex->mhDCMem,
        0, 0,

        tpTex->mBitmapInfo.bmWidth, tpTex->mBitmapInfo.bmHeight,
        tColorKey);
        //RGB(255,255,255));
}


//ryu_ani_spritesheet_i
void CAPIEngine::DrawTexturePartial(float tX, float tY, CTexture* tpTex, int tRow, int tCol,int tIndex, COLORREF tColorKey)
{
    //�� ��������Ʈ �������� �ʺ�� ���̸� ���Ѵ�
    int tSrcWidth = tpTex->mBitmapInfo.bmWidth/tCol;
    int tSrcHeight = tpTex->mBitmapInfo.bmHeight/tRow;


    //���� ��� ���� ���Ѵ�
    int tCurRow = tIndex / tCol;
    int tCurCol = tIndex % tCol;
    //���� ��������Ʈ �������� ��ġ�� ���Ѵ�
    int tSrcX = tCurCol*tSrcWidth;
    int tSrcY = tCurRow*tSrcHeight;


    TransparentBlt(this->mpBackBuffer->mhDCMem,
        
        tX, tY,
        tSrcWidth, tSrcHeight,
        
        tpTex->mhDCMem,
     
        tSrcX, tSrcY,
        tSrcWidth, tSrcHeight,
       
        tColorKey);




    /*TransparentBlt(this->mpBackBuffer->mhDCMem,
        tX, tY,
        tpTex->mBitmapInfo.bmWidth, tpTex->mBitmapInfo.bmHeight,
        tpTex->mhDCMem,
        0, 0,

        tpTex->mBitmapInfo.bmWidth, tpTex->mBitmapInfo.bmHeight,
        tColorKey);*/
}





BOOL CAPIEngine::Create(HINSTANCE hInstance, int nCmdShow)
{
    /*LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPITRANING00, szWindowClass, MAX_LOADSTRING);*/

    wsprintf(szTitle, L"winAPIShootor");    //�Ű������� �޾� ������ �����ϰڴ�.
    wsprintf(szWindowClass, L"winAPIShootor");    //�Ű������� �޾� ������ �����ϰڴ�.


    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }


	return TRUE;
}


MSG CAPIEngine::Run()
{
   
    MSG msg = { 0 };


    mhDC = GetDC(mhWnd);

    mpBackBuffer = new CTexture();
    mpBackBuffer->CreateBackBuffer(hInst, mhDC);
    //mpBackBuffer->LoadTexture(hInst, mhDC, TEXT("resources/backbuffer_0.bmp"));

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









//
//  �Լ�: MyRegisterClass()
//
//  �뵵: â Ŭ������ ����մϴ�.
//
ATOM CAPIEngine::MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc; // nullptr;//WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, nullptr);//MAKEINTRESOURCE(IDI_WINAPITRANING00));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;//MAKEINTRESOURCEW(IDC_WINAPITRANING00);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, nullptr);//MAKEINTRESOURCE(IDI_SMALL));

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
BOOL CAPIEngine::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.



    mhWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);


    if (!mhWnd)
    {
        return FALSE;
    }


    SetWindowText(mhWnd, L"CAPIEngine test titlebar text");

    
    RECT tRect = { 0,0,800,600 };
    //���� �Լ��� ȣ���ϸ� Ÿ��Ʋ��, �޴� ����� ����Ͽ� �ٽ� ������ش�
    AdjustWindowRect(&tRect, WS_OVERLAPPEDWINDOW, FALSE);

    //������ ũ�⸦ �����Ѵ�
    SetWindowPos(mhWnd, HWND_TOPMOST, 100, 100, tRect.right - tRect.left, tRect.bottom - tRect.top, SWP_NOMOVE | SWP_NOZORDER);



    ShowWindow(mhWnd, nCmdShow);
    UpdateWindow(mhWnd);

    return TRUE;
}



LRESULT CALLBACK CAPIEngine::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    //case WM_COMMAND:
    //{
    //    int wmId = LOWORD(wParam);
    //    // �޴� ������ ���� �м��մϴ�:
    //    switch (wmId)
    //    {
    //    case IDM_ABOUT:
    //        DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
    //        break;
    //    case IDM_EXIT:
    //        DestroyWindow(hWnd);
    //        break;
    //    default:
    //        return DefWindowProc(hWnd, message, wParam, lParam);
    //    }
    //}
    //break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
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




//// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
//INT_PTR CALLBACK CAPIEngine::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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



//
//template<typename T>
//T* CAPIEngine::CreatePrefab(CTexture* tpTex, float tAnchorX, float tAnchorY, SVector2D tPosition)
//{
//    // �����յ��� �����д�( ������ü )
//    T* tpPrefab = new T();
//
//    tpPrefab->SetTexture(tpTex);
//    tpPrefab->SetAnchorPoint(tAnchorX, tAnchorY);
//    tpPrefab->SetPosition(tPosition);
//
//    return tpPrefab;
//}
//void CAPIEngine::DestroyPrefab(CObjectRyu*& tPrefab)
//{
//    if (nullptr != tPrefab)
//    {
//        delete tPrefab;
//        tPrefab = nullptr;
//    }
//}