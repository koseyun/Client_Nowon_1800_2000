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
        
    // 파일로부터 모델 데이터를 읽어들임
    //LoadFromObjectFile("resources/test_cube.obj");
    //LoadFromObjectFile("resources/slime.obj");
    LoadFromObjectFile("resources/test_sphere.obj");

    // 파일로부터 가져온 데이터 그대로 개수를 세어
    // 정점 개수, 인덱스 개수를 결정함
    mCountVertex = mVertices.size();
    mCountIndex = mIndexVertices.size();

    // 정점의 위치 데이터 만듦
    tpVertexs = new SimpleVertex[mCountVertex];
    for (int ti = 0; ti < mCountVertex; ++ti)
    {
        tpVertexs[ti].Pos = mVertices[ti];
    }

    // 시스템 메모리에 인덱스 데이터 만듦
    // 시스템 메모리에 인덱스 데이터를 파일에서 읽어들인 데이터로 설정
    tpIndexs = new WORD[mCountIndex];
    // 파일에서 가져온 인덱스 정보들을 그대로 적용하여
    // 정점 데이터에 텍스쳐 정보, 법선 정보도 설정한다
    for (int ti = 0; ti < mCountIndex; ++ti)
    {
        // 임의의 정점의 UV좌표 정보
        int tIndex          = mIndexVertices[ti];
        int tIndexUV        = mIndexUVs[ti];
        int tIndexNormal    = mIndexNormals[ti];

        tpIndexs[ti] = tIndex;

        tpVertexs[tIndex].Tex = mUVs[tIndexUV];
        tpVertexs[tIndex].Normal = mNormals[tIndexNormal];
    }

    for (int ti = 0; ti < mCountIndex; ++ti)
    {
        tpIndexs[ti] = mIndexVertices[ti];
    }

    // 주설명
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(SimpleVertex) * mCountVertex;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    // 부설명
    InitData.pSysMem = tpVertexs;

    tpDevice->CreateBuffer(&bd, &InitData, &mpVertexBuffer);

    // 주설명
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(WORD) * mCountIndex;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;
    // 부설명
    InitData.pSysMem = tpIndexs;

    tpDevice->CreateBuffer(&bd, &InitData, &mpIndexBuffer);

    // 시스템 메모리에 만든 데이터는 이제 필요없으므로 삭제한다
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

    // IA에 VB, IB, topology설정
    tpDeviceContext->IASetVertexBuffers(0, 1, &mpVertexBuffer, &stride, &offset);
    tpDeviceContext->IASetIndexBuffer(mpIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
    tpDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // 인덱스 버퍼 정보를 이용하여 랜더링
    //tpDeviceContext->DrawIndexed(mCountIndex, 0, 0);
}

ID3D11ShaderResourceView* CMesh::GetTexture()
{
    return mpTexture->GetTexture();
}
