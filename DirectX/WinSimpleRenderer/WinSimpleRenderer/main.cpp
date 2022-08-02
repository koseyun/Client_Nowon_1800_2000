/*
    
*/

#pragma once
#include "framework.h"
#include <time.h>
#include <list>
#include <stack>
using namespace std;

#pragma comment(lib, "WinApiEngine.lib")

class CAPIEngine: public CAPI_Engine
{
public:
    CAPIEngine() {};
    virtual ~CAPIEngine() {};
        
    virtual void OnCreate() override
    {
        CAPI_Engine::OnCreate();

    }
    virtual void OnDestroy() override
    {
        
        CAPI_Engine::OnDestroy();
    }
    virtual void OnUpdate(float tDeltaTime) override
    {
        CAPI_Engine::OnUpdate(tDeltaTime);


        //Render
        this->Clear(0.1f, 0.1f, 0.3f);
        
        this->Present();
    }

private:
    CAPIEngine(const CAPIEngine&) {};

    CAPIEngine& operator=(const CAPIEngine&) {};
};

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR    lpCmdLine,
                      _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    CAPIEngine tEngine;
    tEngine.Create(hInstance, nCmdShow);

    MSG msg = { 0 };

    msg = tEngine.Run();

    return (int) msg.wParam;
}
