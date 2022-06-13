#pragma once
#include <windows.h>

#define MAX_LOADSTRING 100

class CAPI_Engine
{
public:
	BOOL Create(HINSTANCE hInstance, int nCmdShow);
	MSG Run();

protected:
	ATOM                MyRegisterClass(HINSTANCE hInstance);
	BOOL                InitInstance(HINSTANCE, int);

	// �������� ������ �������� �ش� ����Լ����� static ���� ������
	static LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
	static INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

public:
	WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.
	WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.

	// ��������Լ��� WndProc���� ����ϰ� �����Ƿ� static ���� ������
	static HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
	


};

