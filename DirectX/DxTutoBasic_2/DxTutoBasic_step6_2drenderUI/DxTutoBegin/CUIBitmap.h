#pragma once
#include "framework.h"

class CDX_Engine;
class CTextureApi;

class CUIBitmap
{
public:
    CUIBitmap();
    ~CUIBitmap();

    // delete���� �̿��� ���
    CUIBitmap(const CUIBitmap& t) = delete;

// �������� ���
//private:
    //CUIBitmap(const CUIBitmap& t) {};

    // �ܺο��� ȣ��� �Լ�
public:
    void Create(ID3D11Device* tpDevice, LPCWSTR tpFileName, int tScreenWidth, int tScreenHeight, int tBitmapWidth, int tBitmapHeight);
    void Destroy();
    void Render(int tPosX, int tPosY);

    // getter
    int GetCountIndex() const
    {
        return mCountIndex;
    };

    void SetEngine(CDX_Engine* tpEngine)
    {
        mpEngine = tpEngine;
    }

    ID3D11ShaderResourceView* GetTexture();

    // ���ο��� ȣ���� �Լ�, 
    // ������ ���������ο��� ���̴����� �ٷ�� buffer��� ������ �������� �̸�������
private:
    void CreateBuffers(ID3D11Device* tpDevice);
    void ShutdownBuffers();
    void RenderBuffers(ID3D11DeviceContext* tpDeviceContext);

    // �̹� ���ÿ����� ���� ���� ������ ������ ����� ���̴�
    // ���⼭�� �� �Լ��� �׷��� ������ �� ���̴�
    bool UpdateBuffers(ID3D11DeviceContext* tpImmediateContext, int tPosX, int tPosY);

public:
    ID3D11Buffer* mpVertexBuffer = nullptr; // �������� �ִ� ������ ������. �� ���ÿ����� �ﰢ�� �����͸� ���� ���̴�
    // VertexBuffer�� ������ �����Ͽ� �׸����� ����
    ID3D11Buffer* mpIndexBuffer = nullptr;

    int mCountVertex = 0;   // ���� �������� ����
    int mCountIndex = 0;    // �ε��� �������� ����

    CTextureApi* mpTexture = nullptr;
    CDX_Engine* mpEngine = nullptr;

private:
    int mScreenWidth;   // ��ũ�� �ʺ�
    int mScreenHeight;  // ��ũ�� ����
    int mBitmapWidth;   // UIBitmap �ʺ�
    int mBitmapHeight;  // UIBitmap ����

    // ��ġ���� üũ�� ��ǥ
    int mPrePosX;
    int mPrePosY;
};

