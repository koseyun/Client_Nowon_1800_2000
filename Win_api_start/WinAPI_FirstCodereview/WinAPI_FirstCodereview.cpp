// WinAPI_FirstCodereview.cpp : 애플리케이션에 대한 진입점을 정의합니다.

#include "framework.h"
#include "WinAPI_FirstCodereview.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
// 함수의 형태를 지켜서 제작해야한다
// 왜냐하면 운영체제가 백그라운드에서 호출해주는 것이기 때문이다
// 
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// 핸들 handle
// 윈도우 응용프로그래밍에서 사용하는 간접참조의 도구
// 포인터변수를 이용한 간접참조 방식은 운영체제가 제공하는 자원의 안정성을 
// 


// 윈도우 데스크탑 응용프로그램의 기본구조(의 중심)

// WinMain 함수의 정의
// 윈도우 데스크탑 응용 프로그램의 진입점
// 호출은 운영체제가 해준다
// 
// 매개변수는 운영체제가 그 값을 구해서 넘겨준다
// 
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, // 윈도우 프로그램의 인스턴스
                     _In_opt_ HINSTANCE hPrevInstance, // 어디에서부터 왔는지 그 원조 윈도우 프로그램의 인스턴스
                     _In_ LPWSTR    lpCmdLine, // 실행파일 실행시 넘겨받는 인자, 문자열 타입
                     _In_ int       nCmdShow) // 윈도우를 어떻게 보일거냐? 라는 옵션의 인자
{
    UNREFERENCED_PARAMETER(hPrevInstance); // 사용되지 않는 변수 라는 warning 안나게 하는 매크로
    UNREFERENCED_PARAMETER(lpCmdLine); // ""

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPIFIRSTCODEREVIEW, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // 해당 함수는 단축키, 자원 정보를 로드하고 핸들을 반환한다
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPIFIRSTCODEREVIEW));

    MSG msg;

    // 기본 메시지 루프입니다:
    // GetMessage : 윈도우 메시지 큐에서 메시지를 하나씩 가져온다
    // 윈도우 메시지 큐에 메시지 데이터가 없으면 대기한다
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        // 엑셀러레이터 처리를 우선한다
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            // 윈도우 메시지를 해석한다
            TranslateMessage(&msg);
            // 윈도우 메시지를 프로시저로 넘긴다
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    // 윈도우 클래스 데이터 : 같은 윈도우 프로그램의 중복되는 데이터들의 모음
    // (클래스 : 분류)
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX); // 해당 데이터의 크기 (바이트 단위)
    
    wcex.style          = CS_HREDRAW | CS_VREDRAW; // 화면 갱신 옵션
    wcex.lpfnWndProc    = WndProc; // 윈도우 프로시저
    // -> 함수포인터
    wcex.cbClsExtra     = 0; // 윈도우 클래스 추가 데이터, 32bit
    wcex.cbWndExtra     = 0; // 윈도우 추가 데이터, 32bit
    wcex.hInstance      = hInstance; // 윈도우 프로그램의 인스턴스의 핸들 (식별자)
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPIFIRSTCODEREVIEW)); // 아이콘
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW); // 커서
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1); // 기본으로 칠할 색
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPIFIRSTCODEREVIEW); // 메뉴이름, 문자열
    wcex.lpszClassName  = szWindowClass; // 윈도우 클래스 이름
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL)); // 아이콘(스몰)

    return RegisterClassExW(&wcex); // 운영체제에 해당 윈도우 클래스 데이터를 등록한다
}

// 함수포인터의 사용이유 :
// 실행 중에 호출할 함수의 결정

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
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   // 윈도우를 생성한다
   // szWindowClass : 윈도우 클래스, szTitle : 타이틀바 문자열
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow); // 윈도우를 어떻게 보일지 결정하는 함수
   UpdateWindow(hWnd); // 윈도우 화면을 한번 갱신하는 함수

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
// 윈도우 응용프로그램은 윈도우 메시지 기반으로 동작한다
// 여기서 윈도우 메시지들은 메시지 큐에 순서대로 들어가고 순서대로 나와서 처리된다
// 그 처리를 담당하는 함수가 바로 윈도우 프로시저 함수이다
// 
// hWnd : 윈도우 핸들 : 윈도우 식별자
// message : 메시지 식별자
// wParam : 부가적인 데이터, 32bit
// IParam : 부가적인 데이터, 32bit
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
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
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
