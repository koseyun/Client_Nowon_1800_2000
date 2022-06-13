#include <Windows.h>

// API : Application Programming Interface
// �������α׷��� ���α׷����� �ϴµ� �ʿ��� �Լ�������

// step_0
// ������ ����ũž �������α׷��� ������
// 
// hInstance: ������ �������α׷� �ĺ��� �ڵ�, ���� ������ ������� ��� ����.
// hPrevInstance: �� �����찡 ������� ���� �������� �ڵ�
// lpCmdLine: Ŀ�ǵ���� ����
// nCmdShow: �����츦 ��� ������( ������ ����, ... )

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

	// ������ Ŭ���� ��� ������ �ִ� ������
	// �ߺ��� �����͵��� �����Ͽ� �����ϱ� ���� �����̴�
	// �׷���, �ü�� ���忡�� ���� ȿ�������� �ڿ��� �����Ǳ� �����̴�

	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); // �ش� �������� ũ�� (����Ʈ ����)

	wcex.style = CS_HREDRAW | CS_VREDRAW; // ȭ�� ���� �ɼ�
	wcex.lpfnWndProc = nullptr; //WndProc; // ������ ���ν���
	// -> �Լ�������
	wcex.cbClsExtra = 0; // ������ Ŭ���� �߰� ������, 32bit
	wcex.cbWndExtra = 0; // ������ �߰� ������, 32bit
	wcex.hInstance = hinstance; // ������ ���α׷��� �ν��Ͻ��� �ڵ� (�ĺ���)
	wcex.hIcon = LoadIcon(hinstance, nullptr); //MAKEINTRESOURCE(IDI_WINAPIFIRSTCODEREVIEW)); // ������
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW); // Ŀ��
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // �⺻���� ĥ�� ��
	wcex.lpszMenuName = nullptr; //MAKEINTRESOURCEW(IDC_WINAPIFIRSTCODEREVIEW); // �޴��̸�, ���ڿ�
	wcex.lpszClassName = L"win_ryu"; //szWindowClass; // ������ Ŭ���� �̸�
		wcex.hIconSm = LoadIcon(wcex.hInstance, nullptr); //MAKEINTRESOURCE(IDI_SMALL)); // ������(����)

	RegisterClassExW(&wcex); // �ü���� �ش� ������ Ŭ���� �����͸� ����Ѵ�

	return 0;
}
*/

// step_2
#define MAX_LOADSTRING 100

/*int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrecInstance, LPWSTR IpCmdLine, int nCmdShow)
{
	HINSTANCE hInst;

	// ������ Ŭ���� ��� ������ �ִ� ������
	// �ߺ��� �����͵��� �����Ͽ� �����ϱ� ���� �����̴�
	// �׷���, �ü�� ���忡�� ���� ȿ�������� �ڿ��� �����Ǳ� �����̴�

    LPCWSTR szWindowClass = L"win_ryu";
    LPCWSTR szTitle = L"hi, window";
    HINSTANCE hInst;

	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); // �ش� �������� ũ�� (����Ʈ ����)

	wcex.style = CS_HREDRAW | CS_VREDRAW; // ȭ�� ���� �ɼ�
	wcex.lpfnWndProc = nullptr; //WndProc; // ������ ���ν���
	// -> �Լ�������
	wcex.cbClsExtra = 0; // ������ Ŭ���� �߰� ������, 32bit
	wcex.cbWndExtra = 0; // ������ �߰� ������, 32bit
	wcex.hInstance = hinstance; // ������ ���α׷��� �ν��Ͻ��� �ڵ� (�ĺ���)
	wcex.hIcon = LoadIcon(hinstance, nullptr); //MAKEINTRESOURCE(IDI_WINAPIFIRSTCODEREVIEW)); // ������
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW); // Ŀ��
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // �⺻���� ĥ�� ��
	wcex.lpszMenuName = nullptr; //MAKEINTRESOURCEW(IDC_WINAPIFIRSTCODEREVIEW); // �޴��̸�, ���ڿ�
	wcex.lpszClassName = L"win_ryu"; //szWindowClass; // ������ Ŭ���� �̸�
	wcex.hIconSm = LoadIcon(wcex.hInstance, nullptr); //MAKEINTRESOURCE(IDI_SMALL)); // ������(����)

	RegisterClassExW(&wcex); // �ü���� �ش� ������ Ŭ���� �����͸� ����Ѵ�


	hInst = hinstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

	// �����츦 �����Ѵ�
	// szWindowClass : ������ Ŭ����, szTitle : Ÿ��Ʋ�� ���ڿ�
	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow); // �����츦 ��� ������ �����ϴ� �Լ�
	UpdateWindow(hWnd); // ������ ȭ���� �ѹ� �����ϴ� �Լ�

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
//    //wcex.hIconSm = LoadIcon(wcex.hInstance, nullptr);//MAKEINTRESOURCE(IDI_SMALL));//�̰Ͷ����� ������
//
//
//    RegisterClassExW(&wcex);
//
//
//
//
//
//    //hInstance�� �ü���� �����ؼ� �Ѱ��ִ� ���̴�.
//    hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.
//
//    //CreateWindowW �� �����츦 �����. �� �Լ��� ȣ���ϸ� WM_CREATE�޽����� ��������
//    //���� �޽������� �ڵ忡 �������� ���ߴ�.
//    //�� WM_CREATE�� �޽������� �ڵ尡 �۵��ϱ� ���� ��������.
//    //�޽���ť�� ��� ���̴�
//
//    HWND hWnd = CreateWindowW(szWindowClass, L"d", WS_OVERLAPPEDWINDOW,
//        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
//
//    if (!hWnd)
//    {
//        return FALSE;
//    }
//
//    //�����츦 ��� ������ ���Ѵ�. ���̱� �� �⺻�̴�.
//    //SW_SHOW
//    ShowWindow(hWnd, nCmdShow);
//    UpdateWindow(hWnd); //������ ȭ���� �����Ѵ�
//
//    return 0;
//}

//step_3
// 
// ������ ���ν����� �����ϰ� ������Ŭ���� ������ �����Ͽ���.
// 
// ������ ���ν����� ���Ǵ� �䱸�ϴ� ������ ����߸� �Ѵ�.
// ȣ���� �ü���� �ϱ� �����̴�.
// 
//message: ������ �޽��� �ĺ����̴�.  WM_���λ簡 �پ��ִ�.
//wParam WORD PARAMETER 32��Ʈ����ۿ����� 32��Ʈ ũ���̴�.
//lParam LONG PARAMETER 32��Ʈ ũ���̴�
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);    //device context ��ġ, ��ġ�� ������, ��ġ�� ���°� ���� �߻�ȭ�س��� ���̴�
        // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0); //Send~ �ø���� ����Լ�, Post~�ø���� �����Լ�
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
    wcex.hIconSm = LoadIcon(wcex.hInstance, nullptr);//MAKEINTRESOURCE(IDI_SMALL));//�̰Ͷ����� ������


    RegisterClassExW(&wcex);





    //hInstance�� �ü���� �����ؼ� �Ѱ��ִ� ���̴�.
    hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

    //CreateWindowW �� �����츦 �����. �� �Լ��� ȣ���ϸ� WM_CREATE�޽����� ��������
    //���� �޽������� �ڵ忡 �������� ���ߴ�. 
    //�� WM_CREATE�� �޽������� �ڵ尡 �۵��ϱ� ���� ��������.
    //�޽���ť�� ��� ���̴�

    HWND hWnd = CreateWindowW(szWindowClass, L"d", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    //�����츦 ��� ������ ���Ѵ�. ���̱� �� �⺻�̴�.
    //SW_SHOW
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd); //������ ȭ���� �����Ѵ� 

    HACCEL hAccelTable = LoadAccelerators(hInstance, nullptr);

    MSG msg;

    // �⺻ �޽��� �����Դϴ�:
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