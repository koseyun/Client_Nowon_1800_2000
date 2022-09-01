/*
    dxTutoBasic step6

    이번 예시에서는 2d render를 수행해보자

    1. 직교투영 orthographic projection
    2. Z buffer 해제
    3. 동적 정점 버퍼 Dynamic vertex buffer의 이용
*/

#include "framework.h"
#include "CDX_Engine.h"
#include "DDSTextureLoader.h"
using namespace std;

#include "apibuffer.h"

#include "CMesh.h"
#include "CMtlTexture.h"
#include "CTextureApi.h"

class CDXEngine: public CDX_Engine
{
    //ID3D11VertexShader* mpVertexShader = nullptr;   // vertex shader 담당 객체
    //ID3D11PixelShader* mpPixelShader = nullptr;     // pixel shader 담당 객체
    
    //ID3D11InputLayout* mpVertexLayout = nullptr;    // Input Layout 객체
    // 랜더링에 사용할 자원
    //ID3D11Buffer* mpVertexBuffer = nullptr; // 비디오램에 있는 임의의 데이터. 이 예시에서는 삼각형 데이터를 담을 것이다

    // VertexBuffer의 내용을 참고하여 그리기할 정보
    //ID3D11Buffer* mpIndexBuffer = nullptr;

    CMesh* mpMesh = nullptr;
    CMtlTexture* mpMtlTex = nullptr;
    //extureApi* mpTexture = nullptr;

    // 랜더링에 사용할 자원
    ID3D11Buffer* mpCBTransform = nullptr; // 변환행렬 정보들을 담을 상수버퍼이다

    // 응용프로그램 차원에서 다룰 변환행렬 변수들
    XMMATRIX mMatWorld_0;       // 첫번째 정육면체의 월드변환행렬
    XMMATRIX mMatWorld_1;       // 두번째 정육면체의 월드변환행렬

    XMMATRIX mMatView;
    XMMATRIX mMatProjection;

    // 카메라 위치
    XMFLOAT3 mCameraPosition;

public:
    CDXEngine() {};
    virtual ~CDXEngine() {};
        
    virtual void OnCreate() override
    {
        CDX_Engine::OnCreate();

        HRESULT hr = S_OK;

        /*
            HLSL : High Level Shader Language : 마이크로소프트사에서 만든 DirectX용 셰이더 언어

            GLSL : OpenGL용 셰이더 언어
            CG : 엔비디아사에서 만든 셰이더 언어
        */

        mpMesh = new CMesh();
        //mpMesh->Create(this->GetD3DDevice(), L"resources/testUV256by256.dds");
        mpMesh->Create(this->GetD3DDevice(), L"resources/slimeby.dds");
        //mpMesh->Create(this->GetD3DDevice(), L"resources/seafloor.dds");
        mpMesh->SetEngine(this);

        mpMtlTex = new CMtlTexture();
        mpMtlTex->Create(this->GetD3DDevice());
        mpMtlTex->SetEngine(this);

        /* mpTexture = new CTextureApi();
        mpTexture->Create(GetD3DDevice(), L"resources/testUV256by256.dds");*/

        // 파일로부터 이미지 데이터를 가져와 텍스쳐 뷰 객체에 데이터를 설정한다
        //CreateDDSTextureFromFile(GetD3DDevice(), L"resources/testUV256by256.dds", nullptr, &mpTextureRV);

        D3D11_BUFFER_DESC bd = {};

        // Constant Buffer 상수버퍼 생성
        // 주설명
        bd.Usage = D3D11_USAGE_DEFAULT;      // 버퍼는 기본 용도 버퍼로 사용하겠다
        bd.ByteWidth = sizeof(CBTransform) * 1;
        bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // vertex buffer 용도로 사용하겠다
        bd.CPUAccessFlags = 0;

        // 상수버퍼 생성
        GetD3DDevice()->CreateBuffer(&bd, nullptr, &mpCBTransform);

        // 월드변환행렬
        mMatWorld_0 = XMMatrixIdentity(); // 단위행렬
        mMatWorld_1 = XMMatrixIdentity(); // 단위행렬

        // 뷰변환행렬
        mMatView = XMMatrixIdentity(); // 단위행렬
        // 뷰변환 회전행렬
        float tLength = 15.0f;//2.0f;

        mCameraPosition.x = 0.0f;
        mCameraPosition.y = 1.0f * tLength;
        mCameraPosition.z = -1.0f * tLength;

        XMVECTOR tEye = XMVectorSet(mCameraPosition.x, mCameraPosition.y, mCameraPosition.z, 0.0f);
        XMVECTOR tAt = XMVectorSet(0.0f, 0.5f, 0.0f, 1.0f);
        XMVECTOR tUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);     // 상방벡터

        mMatView = XMMatrixLookAtLH(tEye, tAt, tUp);

        // 투영변환행렬
        mMatProjection = XMMatrixIdentity(); // 단위행렬

        RECT rc;
        GetClientRect(mhWnd, &rc);
        UINT width = rc.right - rc.left;
        UINT height = rc.bottom - rc.top;
        float tAspectRatio = width / (float)height;
        // 시야각, 종횡비, 근평면까지의 거리, 원평면까지의 거리를 기반으로 원근 투영변환 행렬을 만든다
        mMatProjection = XMMatrixPerspectiveFovLH(XM_PIDIV2, tAspectRatio, 0.01f, 100.0f);
    }

    virtual void OnDestroy() override
    {

        /*if (mpVertexShader) mpVertexShader->Release();
        if (mpPixelShader) mpPixelShader->Release();

        if (mpVertexLayout) mpVertexLayout->Release();*/

        //if (mpVertexBuffer) mpVertexBuffer->Release();
        //if (mpIndexBuffer) mpIndexBuffer->Release();

        /*if (mpTexture)
        {
            mpTexture->Destroy();

            delete mpTexture;
            mpTexture = nullptr;
        }*/

        if (mpMtlTex)
        {
            mpMtlTex->Destroy();

            delete mpMtlTex;
            mpMtlTex = nullptr;
        }

        if (mpMesh)
        {
            mpMesh->Destroy();

            delete mpMesh;
            mpMesh = nullptr;
        }

        if (mpCBTransform) mpCBTransform->Release();

        CDX_Engine::OnDestroy();
    }

    virtual void OnUpdate(float tDeltaTime) override
    {
        CDX_Engine::OnUpdate(tDeltaTime);

        static float t = 0.0f;
        t = t + 2.5f * tDeltaTime;
        // 상방축을 회전축으로 회전, 얼마만큼 회전할지는 각도로 주어진다
        // 각도 단위는 라디안
        mMatWorld_0 = XMMatrixRotationY(t * 0.5f);
        //mMatWorld_0 = XMMatrixRotationY(0); // 회전 X

        // 상방축을 회전축으로 회전, 얼마만큼 회전할지는 각도로 주어진다
        //mMatWorld_1 = XMMatrixRotationY(t * 1.5f);

        XMMATRIX tRotation = XMMatrixRotationY(t * 1.0f);
        XMMATRIX tTranslate = XMMatrixTranslation(0.0f, 0.0f, 10.0f);

        // 물체의 입장에서 보면 '자전'운동이 일어난다
        mMatWorld_1 = tRotation * tTranslate; // 행벡터* 회전변환행렬 * 이동변환행렬 // 회전하고 그리고나서 이동한다

        // 행렬의 곱셈은 교환법칙이 성립하지 않는다
        // 물체의 입장에서 보면 '공전'운동이 일어난다
        //mMatWorld_1 = tTranslate * tRotation; // 행벡터* 이동변환행렬 * 회전변환행렬 // 이동하고 그리고나서 회전한다

        // 조명 데이터
        XMFLOAT4 tLightDir = XMFLOAT4(0.0f, 0.0f, 1.0f, 0.0f); // 빛 벡터, 전방 방향으로 가정(z축의 양의 방향)
        //XMFLOAT4 tLightDir = XMFLOAT4(-1.0f, -1.0f, .0f, 0.0f) // 비스듬
        XMFLOAT4 tLightColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f); // 빛 색상, 붉은색으로 가정
        // 빨간색(1.0f, 0.0f, 0.0f, 1.0f) 연두색(0.0f, 1.0f, 0.0f, 1.0f) 파란색(0.0f, 0.0f, 1.0f, 1.0f)
        // 노란색(1.0f, 1.0f, 0.0f, 1.0f) 핑크색(1.0f, 0.0f, 1.0f, 1.0f) 민트색(0.0f, 1.0f, 1.0f, 1.0f)
        // 검정색(0.0f, 0.0f, 0.0f, 1.0f) 하얀색(1.0f, 1.0f, 1.0f, 1.0f)

        // 빛 방향을 뒤집어서 계산해준다
        tLightDir.x = tLightDir.x * (-1.0f);
        tLightDir.y = tLightDir.y * (-1.0f);
        tLightDir.z = tLightDir.z * (-1.0f);

        // 조명을 회전
        XMMATRIX tRotateLight = XMMatrixRotationX(0.0f);
        XMVECTOR tVectorLight = XMLoadFloat4(&tLightDir);           // XMFLOAT4 --> XMVECTOR
        tVectorLight = XMVector3Transform(tVectorLight, tRotateLight); // 행렬과 벡터의 곱셈, 결과는 벡터 (x,y,z,0)
        //XMVector3TransformCoord // 행렬과 벡터(위치)의 곱셈, 결과는 벡터(위치) (x,y,z,1)
        XMStoreFloat4(&tLightDir, tVectorLight);                    // XMVECTOR --> XMFLOAT4

        // 주변광 컬러
        XMFLOAT4 tAmbientColor = XMFLOAT4(0.5f, 0.5f, 1.0f, 1.0f);
        // 연두색(0.5f, 1.0f, 0.5f, 1.0f) 하늘색(0.5f, 0.5f, 1.0f, 1.0f) 핑크색(1.0f, 0.0f, 1.0f, 1.0f)
        // 자주색(1.0f, 0.0f, 0.5f, 1.0f) 살구색(1.0f, 0.5f, 0.5f, 1.0f)
        // 검정색(0.0f, 0.0f, 0.0f, 1.0f) 하얀색(1.0f, 1.0f, 1.0f, 1.0f) ...

        // 정반사광 컬러
        XMFLOAT4 tSpecularColor = XMFLOAT4(0.5f, 0.5f, 1.0f, 1.0f);

        // 정반사광 강도(날카로움)
        float tPower = 45.0f;


        //this->Clear(0.1f, 0.1f, 0.3f);
        this->mpD3D->Clear(Colors::BlueViolet);


        // 상수버퍼를 Vertex Shader에 설정
        GetImmediateContext()->VSSetConstantBuffers(0, 1, &mpCBTransform);
        // 상수버퍼를 Pixel Shader에 설정
        GetImmediateContext()->PSSetConstantBuffers(0, 1, &mpCBTransform);

        // 상수버퍼용 지역변수 선언
        CBTransform cb;

        cb.mWorld = XMMatrixTranspose(mMatWorld_0);            // 전치
        cb.mView = XMMatrixTranspose(mMatView);                // 전치
        cb.mProjection = XMMatrixTranspose(mMatProjection);    // 전치
        cb.LightDir = tLightDir;
        cb.LightColor = tLightColor;
        cb.mAmbientColor = tAmbientColor;       // 주변광
        cb.mSpecularColor = tSpecularColor;     // 정반사광 관련
        cb.mSpecularPower = tPower;
        cb.mCameraPosition = mCameraPosition;   // 카메라 위치

        // UpdateSubresource : 상수버퍼의 내용을 갱신해주는 함수
        GetImmediateContext()->UpdateSubresource(mpCBTransform, 0, nullptr, &cb, 0, 0);

        mpMesh->Render();
        mpMtlTex->Render(mpMesh->GetCountIndex(), mpMesh->GetTexture());

        this->mpD3D->Present();
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
