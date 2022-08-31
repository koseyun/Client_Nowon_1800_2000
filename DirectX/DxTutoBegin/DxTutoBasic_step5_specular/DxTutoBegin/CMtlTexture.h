#pragma once
#include "framework.h"

class CDX_Engine;

// material 재질 : How to Shading 데이터, 방법
// 셰이더를 다루는 관리클래스 역할이다
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

    //외부에서 호출될 함수
public:
    void Create(ID3D11Device* tpDevice);
    void Destroy();
    void Render(int tCountIndex, ID3D11ShaderResourceView* tpTexture);

    void SetEngine(CDX_Engine* tpEngine)
    {
        mpEngine = tpEngine;
    }

    //내부에서 호출할 함수
private:
    void CreateShader(ID3D11Device* tpDevice, LPCWSTR szVS, LPCWSTR szPS);
    void ShutdownShader();
    // meterial에 필요한 데이터를 설정하는 부분이다
    bool SetShaderParameters(ID3D11DeviceContext* tpDeviceContext, ID3D11ShaderResourceView* tpTexture);
    void RenderShader(ID3D11DeviceContext* tpDeviceContext, int tCountIndex);

    HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

    // 다음은 셰이더에 관련한 변수들이다
private:
    ID3D11VertexShader* mpVertexShader = nullptr;
    ID3D11PixelShader* mpPixelShader = nullptr;

    ID3D11InputLayout* mpVertexLayout = nullptr;

    ID3D11SamplerState* mpSamplerLinear = nullptr;

    CDX_Engine* mpEngine = nullptr;
};

