#pragma once
#include "framework.h"
#include "SVector2D.h"
#include "CObjectAPI.h"
#include "CUnit.h"
#include"CCollisionMgr.h"
// api_colorkey
#pragma comment(lib, "msimg32.lib")
#define MAX_LOADSTRING 100

class CTexture;

class CAPI_Engine
{
public:
	CAPI_Engine();
	virtual ~CAPI_Engine();

private:
	CAPI_Engine(const CAPI_Engine&) {};

	CAPI_Engine& operator=(const CAPI_Engine&) {};

public:
	BOOL Create(HINSTANCE hInstance, int nCmdShow);
	MSG Run();

	virtual void OnCreate();
	virtual void OnDestroy();
	virtual void OnUpdate(float tDeltaTime);

	void DrawCircle(float tX, float tY, float tRadius);

	// api_colorkey
	void DrawTexture(float tX, float tY, CTexture* tpTex, COLORREF tColorKey = RGB(255,255,255));

	// api_ani_spritesheet_i
	void DrawTexturePartial(float tX, float tY, CTexture* tpTex,int tRow, int tCol, int tIndex, COLORREF tColorKey = RGB(255, 255, 255));

	void Clear(float tR = 0.0f, float tG = 0.0f, float tB = 0.0f);
	void Present();
	
	template<typename T>
	T* CreatePrefab(CTexture* tpTex, float tAnchorX, float tAnchorY, SVector2D tPosition)
	{
	    // �����յ��� �����д� (������ü)
		T* tpPrefab = new T();
		
		tpPrefab->Create(this);

		tpPrefab->SetTexture(tpTex);
		tpPrefab->SetAnchorPoint(tAnchorX, tAnchorY);
		tpPrefab->SetPosition(tPosition);

		tpPrefab->SetIsActive(true);

		return tpPrefab;
	}
	void DestroyPrefab(CUnit*& tPrefab)
	{
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
		//tpUnit->AddRef();
		//tpUnit->Release();

		CCollisionMgr::GetInstance()->AddUnit(tpUnit);

		return tpUnit;
	}

	template<typename T>
	void DestroyObject(T*& tUnit)
	{
		if (nullptr != tUnit)
		{
			//CCollisionMgr::GetInstance()->DeleteUnit(tUnit);

			tUnit->Release();
			tUnit = nullptr;
		}
	}
	
	float GetDeltaTime() const
	{
		return mDeltaTime;
	}

	HINSTANCE GetHInst() const
	{
		return hInst;
	}
	HDC GetHDC() const
	{
		return mhDC;
	}

protected:
	ATOM                MyRegisterClass(HINSTANCE hInstance);
	BOOL                InitInstance(HINSTANCE, int);

	static LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
	//static INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

protected:
	WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
	WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

	static HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.

	HWND mhWnd;
	HDC mhDC;

	CTexture* mpBackBuffer = nullptr;

private:
	LARGE_INTEGER mSecond;
	LARGE_INTEGER mTime;

	float mDeltaTime;
};
