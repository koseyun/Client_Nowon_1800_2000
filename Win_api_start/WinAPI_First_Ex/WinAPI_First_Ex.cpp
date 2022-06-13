#include <Windows.h>

// API : Application Programming Interface
// 응용프로그램의 프로그래밍을 하는데 필요한 함수모음집

// step_0
// 윈도우 데스크탑 응용프로그램의 진입점
// 
// hInstance: 윈도우 응용프로그램 식별자 핸들, 같은 윈도우 종류라면 모두 같다.
// hPrevInstance: 이 윈도우가 만들어진 원래 윈도우의 핸들
// lpCmdLine: 커맨드라인 인자
// nCmdShow: 윈도우를 어떻게 보일지( 보일지 말지, ... )

/*
int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrecInstance, LPWSTR IpCmdLine, int nCmdShow)
{

	return 0;
}
*/

// step_1
/*
int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrecInstance, LPWSTR IpCmdLine, int nCmdShow)
{
	HINSTANCE hInst;

	// 윈도우 클래스 라는 개념이 있는 이유는
	// 중복된 데이터들을 공유하여 관리하기 위한 개념이다
	// 그러면, 운영체제 입장에서 보다 효율적으로 자원이 관리되기 때문이다

	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); // 해당 데이터의 크기 (바이트 단위)

	wcex.style = CS_HREDRAW | CS_VREDRAW; // 화면 갱신 옵션
	wcex.lpfnWndProc = nullptr; //WndProc; // 윈도우 프로시저
	// -> 함수포인터
	wcex.cbClsExtra = 0; // 윈도우 클래스 추가 데이터, 32bit
	wcex.cbWndExtra = 0; // 윈도우 추가 데이터, 32bit
	wcex.hInstance = hinstance; // 윈도우 프로그램의 인스턴스의 핸들 (식별자)
	wcex.hIcon = LoadIcon(hinstance, nullptr); //MAKEINTRESOURCE(IDI_WINAPIFIRSTCODEREVIEW)); // 아이콘
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW); // 커서
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // 기본으로 칠할 색
	wcex.lpszMenuName = nullptr; //MAKEINTRESOURCEW(IDC_WINAPIFIRSTCODEREVIEW); // 메뉴이름, 문자열
	wcex.lpszClassName = L"win_ryu"; //szWindowClass; // 윈도우 클래스 이름
		wcex.hIconSm = LoadIcon(wcex.hInstance, nullptr); //MAKEINTRESOURCE(IDI_SMALL)); // 아이콘(스몰)

	RegisterClassExW(&wcex); // 운영체제에 해당 윈도우 클래스 데이터를 등록한다

	return 0;
}
*/

// step_2
#define MAX_LOADSTRING 100

/*int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrecInstance, LPWSTR IpCmdLine, int nCmdShow)
{
	HINSTANCE hInst;

	// 윈도우 클래스 라는 개념이 있는 이유는
	// 중복된 데이터들을 공유하여 관리하기 위한 개념이다
	// 그러면, 운영체제 입장에서 보다 효율적으로 자원이 관리되기 때문이다

    LPCWSTR szWindowClass = L"win_ryu";
    LPCWSTR szTitle = L"hi, window";
    HINSTANCE hInst;

	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); // 해당 데이터의 크기 (바이트 단위)

	wcex.style = CS_HREDRAW | CS_VREDRAW; // 화면 갱신 옵션
	wcex.lpfnWndProc = nullptr; //WndProc; // 윈도우 프로시저
	// -> 함수포인터
	wcex.cbClsExtra = 0; // 윈도우 클래스 추가 데이터, 32bit
	wcex.cbWndExtra = 0; // 윈도우 추가 데이터, 32bit
	wcex.hInstance = hinstance; // 윈도우 프로그램의 인스턴스의 핸들 (식별자)
	wcex.hIcon = LoadIcon(hinstance, nullptr); //MAKEINTRESOURCE(IDI_WINAPIFIRSTCODEREVIEW)); // 아이콘
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW); // 커서
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // 기본으로 칠할 색
	wcex.lpszMenuName = nullptr; //MAKEINTRESOURCEW(IDC_WINAPIFIRSTCODEREVIEW); // 메뉴이름, 문자열
	wcex.lpszClassName = L"win_ryu"; //szWindowClass; // 윈도우 클래스 이름
	wcex.hIconSm = LoadIcon(wcex.hInstance, nullptr); //MAKEINTRESOURCE(IDI_SMALL)); // 아이콘(스몰)

	RegisterClassExW(&wcex); // 운영체제에 해당 윈도우 클래스 데이터를 등록한다


	hInst = hinstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

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

	return 0;
}*/

//step_2

//int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
//{
//    wcex.style = CS_HREDRAW | CS_VREDRAW;
//    wcex.lpfnWndProc = nullptr;//WndProc;
//    wcex.cbClsExtra = 0;
//    wcex.cbWndExtra = 0;
//    wcex.hInstance = hInstance;
//    //wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPITEST2022061000));
//    wcex.hIcon = LoadIcon(hInstance, nullptr);//MAKEINTRESOURCE(IDI_WINAPITEST2022061000));
//    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
//    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
//    //wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINAPITEST2022061000);
//    wcex.lpszMenuName = nullptr;//MAKEINTRESOURCEW(IDC_WINAPITEST2022061000);
//    //wcex.lpszClassName = szWindowClass;
//    wcex.lpszClassName = szWindowClass;//L"win_ryu";//szWindowClass;
//    //wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
//    //wcex.hIconSm = LoadIcon(wcex.hInstance, nullptr);//MAKEINTRESOURCE(IDI_SMALL));//이것때문에 에러남
//
//
//    RegisterClassExW(&wcex);
//
//
//
//
//
//    //hInstance는 운영체제가 생성해서 넘겨주는 것이다.
//    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
//
//    //CreateWindowW 는 윈도우를 만든다. 이 함수를 호출하면 WM_CREATE메시지가 보내진다
//    //아직 메시지루프 코드에 도달하지 못했다.
//    //즉 WM_CREATE는 메시지루프 코드가 작동하기 전에 보내진다.
//    //메시지큐에 담길 것이다
//
//    HWND hWnd = CreateWindowW(szWindowClass, L"d", WS_OVERLAPPEDWINDOW,
//        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
//
//    if (!hWnd)
//    {
//        return FALSE;
//    }
//
//    //윈도우를 어떻게 보일지 정한다. 보이기 가 기본이다.
//    //SW_SHOW
//    ShowWindow(hWnd, nCmdShow);
//    UpdateWindow(hWnd); //윈도우 화면을 갱신한다
//
//    return 0;
//}

//step_3
// 
// 윈도우 프로시저를 정의하고 윈도우클래스 정보에 설정하였다.
// 
// 윈도우 프로시저의 정의는 요구하는 형식을 맞춰야만 한다.
// 호출은 운영체제가 하기 때문이다.
// 
//message: 윈도우 메시지 식별자이다.  WM_접두사가 붙어있다.
//wParam WORD PARAMETER 32비트응용앱에서는 32비트 크기이다.
//lParam LONG PARAMETER 32비트 크기이다
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);    //device context 장치, 장치의 설정값, 장치의 상태값 등을 추상화해놓은 것이다
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0); //Send~ 시리즈는 대기함수, Post~시리즈는 비대기함수
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    
    LPCWSTR szWindowClass = L"win_ryu";
    LPCWSTR szTitle = L"hi, window";
    HINSTANCE hInst;



    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    //wcex.lpfnWndProc = nullptr;//WndProc;
    wcex.lpfnWndProc = WndProc;

    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    //wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPITEST2022061000));
    wcex.hIcon = LoadIcon(hInstance, nullptr);//MAKEINTRESOURCE(IDI_WINAPITEST2022061000));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    //wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINAPITEST2022061000);
    wcex.lpszMenuName = nullptr;//MAKEINTRESOURCEW(IDC_WINAPITEST2022061000);
    //wcex.lpszClassName = szWindowClass;
    wcex.lpszClassName = szWindowClass;//L"win_ryu";//szWindowClass; 
    //wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    wcex.hIconSm = LoadIcon(wcex.hInstance, nullptr);//MAKEINTRESOURCE(IDI_SMALL));//이것때문에 에러남


    RegisterClassExW(&wcex);





    //hInstance는 운영체제가 생성해서 넘겨주는 것이다.
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    //CreateWindowW 는 윈도우를 만든다. 이 함수를 호출하면 WM_CREATE메시지가 보내진다
    //아직 메시지루프 코드에 도달하지 못했다. 
    //즉 WM_CREATE는 메시지루프 코드가 작동하기 전에 보내진다.
    //메시지큐에 담길 것이다

    HWND hWnd = CreateWindowW(szWindowClass, L"d", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    //윈도우를 어떻게 보일지 정한다. 보이기 가 기본이다.
    //SW_SHOW
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd); //윈도우 화면을 갱신한다 

    HACCEL hAccelTable = LoadAccelerators(hInstance, nullptr);

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return 0;
    //return (int)msg.wParam;
}