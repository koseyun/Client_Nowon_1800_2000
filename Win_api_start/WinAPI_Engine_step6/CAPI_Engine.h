#pragma once
#include <windows.h>

#define MAX_LOADSTRING 100

class CTexture;

class CAPI_Engine
{
public:
	CAPI_Engine();
	virtual ~CAPI_Engine(); // 가상소멸자

	BOOL Create(HINSTANCE hInstance, int nCmdShow);
	MSG Run();

	virtual void OnCreate();
	virtual void OnDestroy();
	virtual void OnUpdate();

	// 원그리기 기능은 엔진에서 구현
	void DrawCircle(float tX, float tY, float tRadius);
	void DrawTexture(float tX, float tY, CTexture* tpTexture);

	// 화면을 클리어하는 함수
	void Clear();
	void Present();

	// 복사생성과 복사대입을 금지하기 위해서 private로 접근제한하였다
private:
	CAPI_Engine(const CAPI_Engine& tEngine) {};
	CAPI_Engine& operator=(const CAPI_Engine& tEngine) {};

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

	// OnUpdate 에서 그리기를 위한 
	HWND mhWnd;
	HDC mhDC;

	CTexture* mpBackBuffer = nullptr;

};

