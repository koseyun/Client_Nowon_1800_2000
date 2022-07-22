#pragma once
#include <windows.h>
#include "SVector2D.h"
#include "CUnit.h"
#include "CCollisionMgr.h"

#define MAX_LOADSTRING 100

class CTexture;

class CAPI_Engine
{
public:
	CAPI_Engine();
	virtual ~CAPI_Engine(); // ����Ҹ���

	BOOL Create(HINSTANCE hInstance, int nCmdShow);
	MSG Run();

	virtual void OnCreate();
	virtual void OnDestroy();
	virtual void OnUpdate(float tDeltaTime);

	// ���׸��� ����� �������� ����
	void DrawCircle(float tX, float tY, float tRadius);
	void DrawTexture(float tX, float tY, CTexture* tpTexture);

	// ȭ���� Ŭ�����ϴ� �Լ�
	void Clear(float tR = 1.0f, float tG = 1.0f, float tB = 1.0f);
	void Present();

	float GetDeltaTime() const
	{
		return mDeltaTime;
	}

	// ������ ������ ������ ref ������ �������� �ʰڴ�
	template<typename T>
	T* CreatePrefab(CTexture* tpTex, float tAnchorX, float tAnchorY, SVector2D tPosition)
	{
		T* tpPrefab = new T();

		//tpPrefab->SetEngine(this);
		tpPrefab->Create(this);
		tpPrefab->SetTexture(tpTex);
		tpPrefab->SetAnchors(tAnchorX, tAnchorY);
		tpPrefab->SetPosition(tPosition);

		// ����
		tpPrefab->SetColliderPosition();

		tpPrefab->SetIsActive(true); // Ȱ���� �⺻������ �ϰڴ�

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

		CCollisionMgr::GetInst()->AddUnit(tpUnit);

		return tpUnit;
	}

	template<typename T>
	void DestroyObject(T*& tUnit)
	{
		//CCollisionMgr::GetInst()->Delete

		if (nullptr != tUnit)
		{
			tUnit->Release();
			tUnit = nullptr;
		}
	}

	// ��������� ��������� �����ϱ� ���ؼ� private�� ���������Ͽ���
private:
	CAPI_Engine(const CAPI_Engine& tEngine) {};
	CAPI_Engine& operator=(const CAPI_Engine& tEngine) {};

protected:
	ATOM MyRegisterClass(HINSTANCE hInstance);
	BOOL InitInstance(HINSTANCE, int);

	// �������� ������ �������� �ش� ����Լ����� static ���� ������
	static LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
	//static INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

public:
	WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.
	WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.

	// ��������Լ��� WndProc���� ����ϰ� �����Ƿ� static ���� ������
	static HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.

	// OnUpdate ���� �׸��⸦ ���� 
	HWND mhWnd;
	HDC mhDC;

	CTexture* mpBackBuffer = nullptr;

	// �ð� ��� ������ ���� �����Ӵ� �ð�
	LARGE_INTEGER mSecond;
	LARGE_INTEGER mTime;

	float mDeltaTime = 0.0f;

};

