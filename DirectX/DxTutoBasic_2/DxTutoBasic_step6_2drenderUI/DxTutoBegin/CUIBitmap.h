#pragma once
#include "framework.h"

class CDX_Engine;
class CTextureApi;

class CUIBitmap
{
public:
    CUIBitmap();
    ~CUIBitmap();

    // delete예약어를 이용한 방법
    CUIBitmap(const CUIBitmap& t) = delete;

// 전통적인 방법
//private:
    //CUIBitmap(const CUIBitmap& t) {};

    // 외부에서 호출될 함수
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

    // 내부에서 호출할 함수, 
    // 랜더링 파이프라인에서 셰이더에서 다루는 buffer라는 개념을 바탕으로 이름지었다
private:
    void CreateBuffers(ID3D11Device* tpDevice);
    void ShutdownBuffers();
    void RenderBuffers(ID3D11DeviceContext* tpDeviceContext);

    // 이번 예시에서는 동적 정점 버퍼의 개념을 사용할 것이다
    // 여기서는 이 함수가 그러한 역할을 할 것이다
    bool UpdateBuffers(ID3D11DeviceContext* tpImmediateContext, int tPosX, int tPosY);

public:
    ID3D11Buffer* mpVertexBuffer = nullptr; // 비디오램에 있는 임의의 데이터. 이 예시에서는 삼각형 데이터를 담을 것이다
    // VertexBuffer의 내용을 참고하여 그리기할 정보
    ID3D11Buffer* mpIndexBuffer = nullptr;

    int mCountVertex = 0;   // 정점 데이터의 개수
    int mCountIndex = 0;    // 인덱스 데이터의 개수

    CTextureApi* mpTexture = nullptr;
    CDX_Engine* mpEngine = nullptr;

private:
    int mScreenWidth;   // 스크린 너비
    int mScreenHeight;  // 스크린 높이
    int mBitmapWidth;   // UIBitmap 너비
    int mBitmapHeight;  // UIBitmap 높이

    // 위치변경 체크용 좌표
    int mPrePosX;
    int mPrePosY;
};

