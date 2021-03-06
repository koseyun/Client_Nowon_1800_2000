#pragma once
#include <windows.h>
#include "SVector2D.h"
#include "CUnit.h"

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
	virtual void OnUpdate(float tDeltaTime);

	// 원그리기 기능은 엔진에서 구현
	void DrawCircle(float tX, float tY, float tRadius);
	void DrawTexture(float tX, float tY, CTexture* tpTexture);

	// 화면을 클리어하는 함수
	void Clear(float tR = 1.0f, float tG = 1.0f, float tB = 1.0f);
	void Present();

	float GetDeltaTime() const
	{
		return mDeltaTime;
	}

	// 프리팹 생성과 해지는 ref 개념을 적용하지 않겠다
	template<typename T>
	T* CreatePrefab(CTexture* tpTex, float tAnchorX, float tAnchorY, SVector2D tPosition)
	{
		T* tpPrefab = new T();

		//tpPrefab->SetEngine(this);
		tpPrefab->Create(this);
		tpPrefab->SetTexture(tpTex);
		tpPrefab->SetAnchors(tAnchorX, tAnchorY);
		tpPrefab->SetPosition(tPosition);

		tpPrefab->SetIsActive(true); // 활성을 기본값으로 하겠다

		return tpPrefab;
	}

	void DestroyPrefab(CUnit*& tPrefab)
	{
		// SAFE_DELETE(tPrefab)
		if (nullptr != tPrefab)
		{
			tPrefab->Destroy();

			delete tPrefab;
			tPrefab = nullptr;
		}
	}

	template<typename T>
	T* InstantObject(CUnit* tpPrefab)
	{
		T* tpUnit = nullptr;
		tpUnit = static_cast<T*>(tpPrefab->clone());
		// tpUnit->AddRef();
		// tpUnit->Release();

		return tpUnit;
	}

	template<typename T>
	void DestroyObject(T*& tUnit)
	{
		if (nullptr != tUnit)
		{
			tUnit->Release();
			tUnit = nullptr;
		}
	}

	// 복사생성과 복사대입을 금지하기 위해서 private로 접근제한하였다
private:
	CAPI_Engine(const CAPI_Engine& tEngine) {};
	CAPI_Engine& operator=(const CAPI_Engine& tEngine) {};

protected:
	ATOM MyRegisterClass(HINSTANCE hInstance);
	BOOL InitInstance(HINSTANCE, int);

	// 전역적인 성격을 가지도록 해당 멤버함수들을 static 예약어를 적용함
	static LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
	//static INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

public:
	WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
	WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.

	// 정적멤버함수인 WndProc에서 사용하고 있으므로 static 예약어를 적용함
	static HINSTANCE hInst;                                // 현재 인스턴스입니다.

	// OnUpdate 에서 그리기를 위한 
	HWND mhWnd;
	HDC mhDC;

	CTexture* mpBackBuffer = nullptr;

	// 시간 기반 진행을 위한 프레임당 시간
	LARGE_INTEGER mSecond;
	LARGE_INTEGER mTime;

	float mDeltaTime = 0.0f;

};

