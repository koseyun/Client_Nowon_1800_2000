/*
    Window API
    윈도우 운영체제에서 제공하는 기능들을 다룰 수 있는 API(Application Programming Interface)

    DirectX API
    그래픽 카드 장치를 빠르게 접근하여 제공하는 기능들을 다룰 수 있는 API
*/

#include "framework.h"
#include "CDX_Engine.h"
using namespace std;

class CDXEngine: public CDX_Engine
{
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
        this->Clear(Colors::MidnightBlue);
        
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
