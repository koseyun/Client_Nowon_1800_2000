/*
    step1
    삼각형을 랜더링해보자

    1. 필요한 기하구조물의 데이터를 만들자
        버퍼(buffer) : 셰이더 프로그램에서 참조하는 데이터를 담는 GPU리소스(자원)
        <- 셰이더 프로그램은 그래픽 카드에서 동작하므로 즉 이 리소스는 비디오램에 있는 것이다
*/

#include "framework.h"
#include "CDX_Engine.h"
using namespace std;

// 이것은 정점을 나타내는 구조체의 정의이다
// float 데이터 3개로 구성된 벡터이다
// 이 정의는 시스템 메모리에 만든 데이터의 형식을 정의하는 것이다
struct SimpleVertex
{
    XMFLOAT3 Pos;
};

class CDXEngine: public CDX_Engine
{
    ID3D11VertexShader* mpVertexShader = nullptr; // vertex shader 담당 객체
    ID3D11PixelShader* mpPixelShader = nullptr; // pixel shader 담당 객체

    ID3D11InputLayout* mpVertexLayout = nullptr; // Input Layout 객체

    ID3D11Buffer* mpVertexBuffer = nullptr; // 비디오램에 있는 임의의 데이어. 이 예시에서는 삼각형 데이터를 담을 것이다

public:
    CDXEngine() {};
    virtual ~CDXEngine() {};
        
    virtual void OnCreate() override
    {
        CDX_Engine::OnCreate();
    }
    virtual void OnDestroy() override
    {
        CDX_Engine::OnDestroy();
    }
    virtual void OnUpdate(float tDeltaTime) override
    {
        CDX_Engine::OnUpdate(tDeltaTime);
        
        //this->Clear(0.1f, 0.1f, 0.3f);
        this->Clear(Colors::BlueViolet);
        
        this->Present();
    }

private:
    CDXEngine(const CDXEngine&) {};

    CDXEngine& operator=(const CDXEngine&) {};
};

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR    lpCmdLine,
                      _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    CDXEngine tEngine;
    tEngine.Create(hInstance, nCmdShow);

    MSG msg = { 0 };

    msg = tEngine.Run();

    return (int) msg.wParam;
}
