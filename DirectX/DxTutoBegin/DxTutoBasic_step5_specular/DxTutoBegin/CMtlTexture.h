#pragma once
#include "framework.h"

class CDX_Engine;

// material ���� : How to Shading ������, ���
// ���̴��� �ٷ�� ����Ŭ���� �����̴�
class CMtlTexture
{
public:
    CMtlTexture()
    {
        mpVertexShader = nullptr;
        mpPixelShader = nullptr;

        mpVertexLayout = nullptr;

        mpSamplerLinear = nullptr;
    };
    ~CMtlTexture()
    {

    };

    CMtlTexture(const CMtlTexture& t) = delete;

    //�ܺο��� ȣ��� �Լ�
public:
    void Create(ID3D11Device* tpDevice);
    void Destroy();
    void Render(int tCountIndex, ID3D11ShaderResourceView* tpTexture);

    void SetEngine(CDX_Engine* tpEngine)
    {
        mpEngine = tpEngine;
    }

    //���ο��� ȣ���� �Լ�
private:
    void CreateShader(ID3D11Device* tpDevice, LPCWSTR szVS, LPCWSTR szPS);
    void ShutdownShader();
    // meterial�� �ʿ��� �����͸� �����ϴ� �κ��̴�
    bool SetShaderParameters(ID3D11DeviceContext* tpDeviceContext, ID3D11ShaderResourceView* tpTexture);
    void RenderShader(ID3D11DeviceContext* tpDeviceContext, int tCountIndex);

    HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

    // ������ ���̴��� ������ �������̴�
private:
    ID3D11VertexShader* mpVertexShader = nullptr;
    ID3D11PixelShader* mpPixelShader = nullptr;

    ID3D11InputLayout* mpVertexLayout = nullptr;

    ID3D11SamplerState* mpSamplerLinear = nullptr;

    CDX_Engine* mpEngine = nullptr;
};

