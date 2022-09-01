#pragma once
#include "framework.h"

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

    void Create(ID3D11Device* tpDevice, ID3D11DeviceContext* tpDeviceContext);

    // 다음은 셰이더에 관련한 변수들이다
private:
    ID3D11VertexShader* mpVertexShader = nullptr;
    ID3D11PixelShader* mpPixelShader = nullptr;

    ID3D11InputLayout* mpVertexLayout = nullptr;

    ID3D11SamplerState* mpSamplerLinear = nullptr;
};

