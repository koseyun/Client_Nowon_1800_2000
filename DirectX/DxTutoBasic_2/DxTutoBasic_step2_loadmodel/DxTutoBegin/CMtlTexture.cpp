#include "CMtlTexture.h"
#include "CDX_Engine.h"

void CMtlTexture::Create(ID3D11Device* tpDevice)
{
    CreateShader(tpDevice, L"VertexShader.hlsl", L"PixelShader.hlsl");
}
void CMtlTexture::Destroy()
{
    ShutdownShader();
}
void CMtlTexture::Render(int tCountIndex, ID3D11ShaderResourceView* tpTexture)
{
    SetShaderParameters(mpEngine->GetImmediateContext(), tpTexture);

    RenderShader(mpEngine->GetImmediateContext(), tCountIndex);
}

void CMtlTexture::CreateShader(ID3D11Device* tpDevice, LPCWSTR szVS, LPCWSTR szPS)
{
    ID3DBlob* pVSBlob = nullptr;
    this->CompileShaderFromFile(szVS, "main", "vs_4_0", &pVSBlob);

    tpDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &mpVertexShader);

    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    UINT numElements = ARRAYSIZE(layout);

    tpDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &mpVertexLayout);
    pVSBlob->Release();

    ID3DBlob* pPSBlob = nullptr;
    this->CompileShaderFromFile(szPS, "main", "ps_4_0", &pPSBlob);

    tpDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &mpPixelShader);
    pPSBlob->Release();

    D3D11_SAMPLER_DESC sampDesc = {};
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR; // ��������
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;  // ��踦 �Ѿ�� �� ó���� �ݺ�
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER; // ���ø� �������� ���Լ��� ���� ����
    sampDesc.MinLOD = 0;                   // LOD�� �ּڰ�
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;   // LOD�� �ִ�
    
    tpDevice->CreateSamplerState(&sampDesc, &mpSamplerLinear);
}
void CMtlTexture::ShutdownShader()
{
    if (mpVertexShader)
    {
        mpVertexShader->Release();
        mpVertexShader = nullptr;
    }

    if (mpPixelShader)
    {
        mpPixelShader->Release();
        mpPixelShader = nullptr;
    }

    if (mpVertexLayout)
    {
        mpVertexLayout->Release();
        mpVertexLayout = nullptr;
    }

    if (mpSamplerLinear)
    {
        mpSamplerLinear->Release();
        mpSamplerLinear = nullptr;
    }
}

bool CMtlTexture::SetShaderParameters(ID3D11DeviceContext* tpDeviceContext, ID3D11ShaderResourceView* tpTexture)
{
    tpDeviceContext->PSSetShaderResources(0, 1, &tpTexture);

    return true;
}
void CMtlTexture::RenderShader(ID3D11DeviceContext* tpDeviceContext, int tCountIndex)
{
    tpDeviceContext->IASetInputLayout(mpVertexLayout);

    tpDeviceContext->VSSetShader(mpVertexShader, nullptr, 0);
    tpDeviceContext->PSSetShader(mpPixelShader, nullptr, 0);
    tpDeviceContext->PSSetSamplers(0, 1, &mpSamplerLinear);

    //�ε��� ���� ������ �̿��Ͽ� ������
    tpDeviceContext->DrawIndexed(tCountIndex, 0, 0);
}

HRESULT CMtlTexture::CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;

    // Disable optimizations to further improve shader debugging
    dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    ID3DBlob* pErrorBlob = nullptr;
    // ���̴� �ҽ��ڵ� ������ ���������ִ� �Լ�
    // Shader SourceCode File --> ������ --> ����Ʈ �ڵ� ByteCode (�߰������)
    hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
        dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
    if (FAILED(hr))
    {
        if (pErrorBlob)
        {
            OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
            pErrorBlob->Release();
        }
        return hr;
    }
    if (pErrorBlob) pErrorBlob->Release();

    return S_OK;
}
