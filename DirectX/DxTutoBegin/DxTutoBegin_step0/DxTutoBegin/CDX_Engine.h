#pragma once
#include "framework.h"

#define MAX_LOADSTRING 100

class CDX_Engine
{
public:
	CDX_Engine();
	virtual ~CDX_Engine();

private:
	CDX_Engine(const CDX_Engine&) {};

	CDX_Engine& operator=(const CDX_Engine&) {};

public:
	BOOL Create(HINSTANCE hInstance, int nCmdShow);
	MSG Run();

	virtual void OnCreate();
	virtual void OnDestroy();
	virtual void OnUpdate(float tDeltaTime);

	void Clear(float tR = 0.0f, float tG = 0.0f, float tB = 0.0f);
	void Clear(XMVECTORF32 tColor);
	void Present();
		
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

	int ScreenWidth()
	{
		return 800;
	}
	int ScreenHeight()
	{
		return 600;
	}

protected:
	ATOM                MyRegisterClass(HINSTANCE hInstance);
	BOOL                InitInstance(HINSTANCE, int);

	static LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

protected:
	WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
	WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

	static HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.

	HWND mhWnd;
	HDC mhDC;

private:
	LARGE_INTEGER mSecond;
	LARGE_INTEGER mTime;

	float mDeltaTime;

	// Direct3D
	// ����̹� : �ϵ��� ������ ����Ʈ����
	D3D_DRIVER_TYPE         mDriverType = D3D_DRIVER_TYPE_NULL; // ����̹� ���α׷��� ����
	D3D_FEATURE_LEVEL       mFeatureLevel = D3D_FEATURE_LEVEL_11_0; // FeatureLevel : ������ ��ġ�� �����ϴ� DirectX�� ������� ����

	// ����̽�(��ġ) : �׷��� ó����ġ(�׷��� ī��)�� �߻�ȭ �س��� ��ü : ��Ƽ������(��ɹ��� ����ó���ϴ� ���)�� ������� ���� �κ��� ���
	ID3D11Device* mpd3dDevice = nullptr;
	ID3D11Device1* mpd3dDevice1 = nullptr;

	// ����̽� ���ؽ�Ʈ(��ġ ���ؽ�Ʈ) : �׷��� ó����ġ(�׷��� ī��)�� �߻�ȭ �س��� ��ü
	// : ��Ƽ������(��ɹ��� ����ó���ϴ� ���)�� ����� �κ��� ���. ����̽� ����� �и��Ǿ� �ִ�
	ID3D11DeviceContext* mpImmediateContext = nullptr;
	ID3D11DeviceContext1* mpImmediateContext1 = nullptr;

	// ����ü�� : ������۸� ������ �����ϰ� �� �� ���۰� ���� ��ȯ�Ǵ� ������ �߻�ȭ�� ��ü�̴�
	// window api�� �������� �ۼ��� �� ���� ���� ������ ���� �ΰ��� �����ϰ�(back buffer, front buffer)
	// back buffer���� front buffer�� �̹��� �����͸� �����ϴ� ���·� �۵��߾��ٸ�
	// ���� DirectX���� �����ϴ� ������۴� ���� ��ȭ�� �������ν� �� �� ���۰� ���� ��ȯ�ȴ�
	// �̷��� ������ ��ġ �罽ó�� ���� SwapChain�̶� ���Ǿ���
	IDXGISwapChain* mpSwapChain = nullptr;
	IDXGISwapChain1* mpSwapChain1 = nullptr;

	// ���� Ÿ�� �� ��ü�� back buffer(�ĸ����)�� �̹��� �����͸� ������ �� �� �ִ� ���·� �߻�ȭ �س��� ��ü�̴�
	ID3D11RenderTargetView* mpRenderTargetView = nullptr;

public:
	HRESULT InitDevice();
	void CleanupDevice();
};
