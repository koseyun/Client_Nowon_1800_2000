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

	// 전역적인 성격을 가지도록 해당 멤버함수들을 static 예약어를 적용함
	static LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
	static INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

public:
	WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
	WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.

	// 정적멤버함수인 WndProc에서 사용하고 있으므로 static 예약어를 적용함
	static HINSTANCE hInst;                                // 현재 인스턴스입니다.
	


};

