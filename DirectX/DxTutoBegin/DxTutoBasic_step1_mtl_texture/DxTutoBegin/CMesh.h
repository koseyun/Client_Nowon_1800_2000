#pragma once
#include "framework.h"

class CDX_Engine;

class CMesh
{
public:
    CMesh();
    ~CMesh();

    // delete예약어를 이용한 방법
    CMesh(const CMesh& t) = delete;

// 전통적인 방법
//private:
    //CMesh(const CMesh& t) {};

    // 외부에서 호출될 함수
public:
    void Create(ID3D11Device* tpDevice);
    void Destroy();
    void Render();

    // getter
    int GetCountIndex() const
    {
        return mCountIndex;
    };

    void SetEngine(CDX_Engine* tpEngine)
    {
        mpEngine = tpEngine;
    }

    // 내부에서 호출할 함수, 
    // 랜더링 파이프라인에서 셰이더에서 다루는 buffer라는 개념을 바탕으로 이름지었다
private:
    void CreateBuffers(ID3D11Device* tpDevice);
    void ShutdownBuffers();
    void RenderBuffers(ID3D11DeviceContext* tpDeviceContext);

public:
    ID3D11Buffer* mpVertexBuffer = nullptr; // 비디오램에 있는 임의의 데이터. 이 예시에서는 삼각형 데이터를 담을 것이다

    // VertexBuffer의 내용을 참고하여 그리기할 정보
    ID3D11Buffer* mpIndexBuffer = nullptr;

    int mCountVertex = 0;   // 정점 데이터의 개수
    int mCountIndex = 0;    // 인덱스 데이터의 개수

    CDX_Engine* mpEngine = nullptr;
};

