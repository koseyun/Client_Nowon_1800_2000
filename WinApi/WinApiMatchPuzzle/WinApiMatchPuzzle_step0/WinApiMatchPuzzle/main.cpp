
/*

*/

#include "framework.h"

#include <list>
using namespace std;

#pragma comment(lib, "winAPIEngine.lib")




class CAPI_Engine : public CAPIEngine
{
private:
    
public:
    CAPI_Engine() {};
    virtual ~CAPI_Engine() {};


    virtual void OnCreate() override
    {
        CAPIEngine::OnCreate();

        // todo
    }
    virtual void OnDestroy() override
    {
        // todo

        CAPIEngine::OnDestroy();
    }
    virtual void OnUpdate(float tDeltaTime) override
    {
        CAPIEngine::OnUpdate(tDeltaTime);

        //Render
        this->Clear(0.1f, 0.1f, 0.3f);
        
        this->Present();
    }

private:
    CAPI_Engine(const CAPI_Engine&) {};

    CAPI_Engine& operator=(const CAPI_Engine&) {};


};


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    CAPI_Engine tEngine;
    tEngine.Create(hInstance, nCmdShow);


    MSG msg = { 0 };

    msg = tEngine.Run();

    return (int) msg.wParam;
}

