#pragma once
#include "framework.h"

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

    void Create(ID3D11Device* tpDevice, ID3D11DeviceContext* tpDeviceContext);

    // ������ ���̴��� ������ �������̴�
private:
    ID3D11VertexShader* mpVertexShader = nullptr;
    ID3D11PixelShader* mpPixelShader = nullptr;

    ID3D11InputLayout* mpVertexLayout = nullptr;

    ID3D11SamplerState* mpSamplerLinear = nullptr;
};

