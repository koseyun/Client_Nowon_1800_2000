#pragma once
#include "framework.h"

class CD3DApi
{
private:
	// D3D : Direct3D
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

	// depth
	// ���̹��� : ���̰��� �����ѵδ� �޸�. �յ� ������ �������̴�
	// ���ٽǹ��� : ������ ȿ���� ����� ���� �޸�
	// DirectX������ �� �� ���۸� �ϳ��� ���ҽ��� ��� ����Ѵ�. ���̹��� 24 + ���ٽǹ��� 8 = 32
	// �׷��� �̸��� DepthStencil �̴�
	ID3D11Texture2D* mpDepthStencil = nullptr;
	ID3D11DepthStencilView* mpDepthStencilView = nullptr;

	// ������ �ڵ�
	HWND mhWnd;

public:
	HRESULT Create(HWND thWnd);
	void Destroy();

	void Clear(float tR = 0.0f, float tG = 0.0f, float tB = 0.0f);
	void Clear(XMVECTORF32 tColor);
	void Present();

	HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	ID3D11Device* GetD3DDevice() const
	{
		return mpd3dDevice;
	}

	ID3D11DeviceContext* GetImmediateContext() const
	{
		return mpImmediateContext;
	}
};
