#include "CUIBitmap.h"
#include "CDX_Engine.h"
#include "apibuffer.h"
#include "CTextureApi.h"

CUIBitmap::CUIBitmap()
{
    mpVertexBuffer = nullptr;
    mpIndexBuffer = nullptr;

    mCountVertex = 0;
    mCountIndex = 0;

    mpTexture = nullptr;

    mpEngine = nullptr;
}
CUIBitmap::~CUIBitmap()
{

}

void CUIBitmap::Create(ID3D11Device* tpDevice, LPCWSTR tpFileName, int tScreenWidth, int tScreenHeight, int tBitmapWidth, int tBitmapHeight)
{
    mScreenWidth = tScreenWidth;
    mScreenHeight = tScreenHeight;
    mBitmapWidth = tBitmapWidth;
    mBitmapHeight = tBitmapHeight;

    mPrePosX = -1;
    mPrePosY = -1;

    CreateBuffers(tpDevice);

    mpTexture = new CTextureApi();
    mpTexture->Create(tpDevice, tpFileName);
}
void CUIBitmap::Destroy()
{
    if (mpTexture)
    {
        mpTexture->Destroy();

        delete mpTexture;
        mpTexture = nullptr;
    }

    ShutdownBuffers();
}
void CUIBitmap::Render(int tPosX, int tPosY)
{
    UpdateBuffers(mpEngine->GetImmediateContext(), tPosX, tPosY);

    RenderBuffers(mpEngine->GetImmediateContext());
}

void CUIBitmap::CreateBuffers(ID3D11Device* tpDevice)
{
    SimpleVertex* tpVertexs = nullptr;
    WORD* tpIndexs = nullptr;

    D3D11_BUFFER_DESC bd = {};
    D3D11_SUBRESOURCE_DATA InitData = {};

    // 파일로부터 가져온 데이터 그대로 개수를 세어
    // 정점 개수, 인덱스 개수를 결정함
    mCountVertex = 6;
    mCountIndex = 6;

    // 힙메모리에 메모리 확보하고 초기화
    tpVertexs = new SimpleVertex[mCountVertex];
    memset(tpVertexs, 0, sizeof(SimpleVertex) * mCountVertex);

    tpIndexs = new WORD[mCountIndex];
    for (int ti = 0; ti < mCountIndex; ++ti)
    {
        tpIndexs[ti] = ti;
    }

    // 주설명
    bd.Usage = D3D11_USAGE_DYNAMIC; // 동적 용도로 사용하겠다(실행 중에 버퍼에 접근하여 데이터의 값을 써넣는다)

    bd.ByteWidth = sizeof(SimpleVertex) * mCountVertex;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; //데이터의 값을 써넣는다
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
void CUIBitmap::ShutdownBuffers()
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
void CUIBitmap::RenderBuffers(ID3D11DeviceContext* tpDeviceContext)
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

bool CUIBitmap::UpdateBuffers(ID3D11DeviceContext* tpImmediateContext, int tPosX, int tPosY)
{
    // 사각형 관련 변수
    float left;
    float right;
    float top;
    float bottom;

    // vertex buffer에 써넣을 데이터용 (시스템 메모리)
    SimpleVertex* tpVertices = nullptr;

    // vertex buffer 접근용 변수
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    SimpleVertex* verticesPtr = nullptr;

    // 출력위치 변경이 없다면 map, unmap을 이용한 vertex buffer 갱신을 하지 않는다
    // <- 그렇게하면 보다 효율적인 진행이 가능하다(연산이 줄어드므로)
    if ((mPrePosX == tPosX) && (mPrePosY == tPosY))
    {
        return true;
    }

    mPrePosX = tPosX;
    mPrePosY = tPosY;

    left = (mScreenWidth / 2.0f) * (-1.0f) + (float)tPosX;
    right = left + (float)mBitmapWidth;

    top = (mScreenHeight / 2.0f) - (float)tPosY;
    bottom = top - (float)mBitmapHeight;

    tpVertices = new SimpleVertex[mCountVertex];
    // 초기화
    memset(tpVertices, 0, sizeof(SimpleVertex) * mCountVertex);

    // normal 데이터는 설정하지 않았다

    // 첫번째 삼각형
    tpVertices[0].Pos = XMFLOAT3(left, top, 0.0f);
    tpVertices[0].Tex = XMFLOAT2(0.0f, 0.0f);

    tpVertices[1].Pos = XMFLOAT3(right, bottom, 0.0f);
    tpVertices[1].Tex = XMFLOAT2(1.0f, 1.0f);

    tpVertices[2].Pos = XMFLOAT3(left, bottom, 0.0f);
    tpVertices[2].Tex = XMFLOAT2(0.0f, 1.0f);
    // 두번째 삼각형
    tpVertices[3].Pos = XMFLOAT3(left, top, 0.0f);
    tpVertices[3].Tex = XMFLOAT2(0.0f, 0.0f);

    tpVertices[4].Pos = XMFLOAT3(right, top, 0.0f);
    tpVertices[4].Tex = XMFLOAT2(1.0f, 0.0f);

    tpVertices[5].Pos = XMFLOAT3(right, bottom, 0.0f);
    tpVertices[5].Tex = XMFLOAT2(1.0f, 1.0f);

    // 실시간으로 vertex buffer에 위의 데이터 내용을 써넣는다

    // Map, Unmap 짝을 맞춰야만 한다
    // Map은 vertex buffer에 CPU 명령을 통해 작업을 하기 위해 다른 작업들에 대해서는 잠금을 하는 것이다
    // 이 함수를 호출하면 mappedResource에 데이터를 써넣기 위한 포인터 변수값을 설정해준다
    // vertex buffer의 쓰기 제어권을 얻는다
    tpImmediateContext->Map(mpVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

        // void*(범용적인 형태)로 얻어온 vertex buffer의 내용을 우리가 다루는 데이터 형식으로 형변환
        verticesPtr = (SimpleVertex*)mappedResource.pData;
        // 복사해서 써넣는다
        memcpy(verticesPtr, (void*)tpVertices, sizeof(SimpleVertex) * mCountVertex);

    // vertex buffer의 쓰기 제어권을 돌려준다
    tpImmediateContext->Unmap(mpVertexBuffer, 0);

    if (tpVertices)
    {
        delete[] tpVertices;
        tpVertices = nullptr;
    }

    return true;
}

ID3D11ShaderResourceView* CUIBitmap::GetTexture()
{
    return mpTexture->GetTexture();
}
