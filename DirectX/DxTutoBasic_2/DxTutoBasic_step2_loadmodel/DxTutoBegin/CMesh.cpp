#include "CMesh.h"
#include "CDX_Engine.h"
#include "apibuffer.h"
#include "CTextureApi.h"

CMesh::CMesh()
{
    mpVertexBuffer = nullptr;
    mpIndexBuffer = nullptr;

    mCountVertex = 0;
    mCountIndex = 0;

    mpTexture = nullptr;

    mpEngine = nullptr;
}
CMesh::~CMesh()
{

}

void CMesh::Create(ID3D11Device* tpDevice, LPCWSTR tpFileName)
{
    CreateBuffers(tpDevice);

    mpTexture = new CTextureApi();
    mpTexture->Create(tpDevice, tpFileName);
}
void CMesh::Destroy()
{
    if (mpTexture)
    {
        mpTexture->Destroy();

        delete mpTexture;
        mpTexture = nullptr;
    }

    ShutdownBuffers();
}
void CMesh::Render()
{
    RenderBuffers(mpEngine->GetImmediateContext());
}

void CMesh::CreateBuffers(ID3D11Device* tpDevice)
{
    SimpleVertex* tpVertexs = nullptr;
    WORD* tpIndexs = nullptr;

    D3D11_BUFFER_DESC bd = {};
    D3D11_SUBRESOURCE_DATA InitData = {};

    /*
    // ������ü�� ����
    mCountVertex = 24;
    mCountIndex = 36;

    //���� �����͸� �ý��� �޸𸮿� ���� ����
    tpVertexs = new SimpleVertex[mCountVertex]
    {
        { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f),  XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, -1.0f),  XMFLOAT3(0.0f, 1.0f, 0.0f),  XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, 1.0f),   XMFLOAT3(0.0f, 1.0f, 0.0f),  XMFLOAT2(0.0f, 1.0f) },
        { XMFLOAT3(-1.0f, 1.0f, 1.0f),  XMFLOAT3(0.0f, 1.0f, 0.0f),  XMFLOAT2(1.0f, 1.0f) },

        { XMFLOAT3(-1.0f, -1.0f, -1.0f),XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(1.0f, -1.0f, 1.0f),  XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(0.0f, 1.0f) },

        { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 1.0f) },
        { XMFLOAT3(-1.0f, -1.0f, -1.0f),XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(-1.0f, 1.0f, 1.0f),  XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f) },

        { XMFLOAT3(1.0f, -1.0f, 1.0f),  XMFLOAT3(1.0f, 0.0f, 0.0f),  XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f),  XMFLOAT2(0.0f, 1.0f) },
        { XMFLOAT3(1.0f, 1.0f, -1.0f),  XMFLOAT3(1.0f, 0.0f, 0.0f),  XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, 1.0f),   XMFLOAT3(1.0f, 0.0f, 0.0f),  XMFLOAT2(1.0f, 0.0f) },

        { XMFLOAT3(-1.0f, -1.0f, -1.0f),XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(0.0f, 1.0f) },
        { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(1.0f, 1.0f, -1.0f),  XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(-1.0f, 1.0f,-1.0f),  XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },

        { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f),  XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(1.0f, -1.0f, 1.0f),  XMFLOAT3(0.0f, 0.0f, 1.0f),  XMFLOAT2(0.0f, 1.0f) },
        { XMFLOAT3(1.0f, 1.0f, 1.0f),   XMFLOAT3(0.0f, 0.0f, 1.0f),  XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(-1.0f, 1.0f, 1.0f),  XMFLOAT3(0.0f, 0.0f, 1.0f),  XMFLOAT2(1.0f, 0.0f) }
    };

    tpIndexs = new WORD[mCountIndex]
    {
        3, 1, 0,
        2, 1, 3,

        6, 4, 5,
        7, 4, 6,

        11, 9, 8,
        10, 9, 11,

        14, 12, 13,
        15, 12, 14,

        19, 17, 16,
        18, 17, 19,

        22, 20, 21,
        23, 20, 22
    };*/

    // ���Ϸκ��� �� �����͸� �о����
    //LoadFromObjectFile("resources/test_cube.obj");
    LoadFromObjectFile("resources/slime.obj");

    // ���Ϸκ��� ������ ������ �״�� ������ ����
    // ���� ����, �ε��� ������ ������
    mCountVertex = mVertices.size();
    mCountIndex = mIndexVertices.size();

    // ������ ��ġ ������ ����
    tpVertexs = new SimpleVertex[mCountVertex];
    for (int ti = 0; ti < mCountVertex; ti++)
    {
        tpVertexs[ti].Pos = mVertices[ti];
    }

    for (int ti = 0; ti < mCountIndex; ti++)
    {
        // ������ ������ UV��ǥ ����
        int tIndex = mIndexVertices[ti];
        int tIndexUV = mIndexUVs[ti];
        int tIndexNormal = mIndexNormals[ti];

        tpVertexs[tIndex].Tex = mUVs[tIndexUV];
        tpVertexs[tIndex].Normal = mNormals[tIndexNormal];
    }

    // �ý��� �޸𸮿� �ε��� ������ ����
    // �ý��� �޸𸮿� �ε��� �����͸� ���Ͽ��� �о���� �����ͷ� ����
    tpIndexs = new WORD[mCountIndex];

    for (int ti = 0; ti < mCountIndex; ti++)
    {
        tpIndexs[ti] = mIndexVertices[ti];
    }

    // �ּ���
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(SimpleVertex) * mCountVertex;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    // �μ���
    InitData.pSysMem = tpVertexs;

    tpDevice->CreateBuffer(&bd, &InitData, &mpVertexBuffer);

    // �ּ���
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(WORD) * mCountIndex;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;
    // �μ���
    InitData.pSysMem = tpIndexs;

    tpDevice->CreateBuffer(&bd, &InitData, &mpIndexBuffer);

    // �ý��� �޸𸮿� ���� �����ʹ� ���� �ʿ�����Ƿ� �����Ѵ�
    if (tpIndexs)
    {
        delete[] tpIndexs;
        tpIndexs = nullptr;
    }

    if (tpVertexs)
    {
        delete[] tpVertexs;
        tpVertexs = nullptr;
    }
}
void CMesh::ShutdownBuffers()
{
    if (mpIndexBuffer)
    {
        mpIndexBuffer->Release();
        mpIndexBuffer = nullptr;
    }

    if (mpVertexBuffer)
    {
        mpVertexBuffer->Release();
        mpVertexBuffer = nullptr;
    }
}
void CMesh::RenderBuffers(ID3D11DeviceContext* tpDeviceContext)
{
    UINT stride = sizeof(SimpleVertex);
    UINT offset = 0;

    // IA�� VB, IB, topology����
    tpDeviceContext->IASetVertexBuffers(0, 1, &mpVertexBuffer, &stride, &offset);
    tpDeviceContext->IASetIndexBuffer(mpIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
    tpDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // �ε��� ���� ������ �̿��Ͽ� ������
    //tpDeviceContext->DrawIndexed(mCountIndex, 0, 0);
}

ID3D11ShaderResourceView* CMesh::GetTexture()
{
    return mpTexture->GetTexture();
}
