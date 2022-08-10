/*
    이번 예시에서는 소프트웨어 랜더러 예시 작성의 가장 기본적인 코드를 테스트해보자
        '삼각형 두개를 이용하여 사각형을 그릴 것이다'

    좌표계는 윈도우 좌표계를 가정한다
    (원점은 좌측상단, y축은 하방이 양의 방향)
*/

#pragma once
#include "framework.h"
#include <time.h>
#include <list>
#include <stack>
#include <vector>
using namespace std;

#pragma comment(lib, "WinApiEngine.lib")

// 3차원 공간에서의 벡터와 점?(위치)을 다루기 위해 정의
struct SApiVector3
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

// 삼각형, 정점 세 개로 만든 도형, 모델의 최소 기본 단위
struct SApiTriangle
{
    SApiVector3 p[3];
};

//메쉬
struct SApiMesh
{
    std::vector<SApiTriangle> tris; // 삼각형들의 모음
};


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
                
        SApiMesh tMesh;
        tMesh.tris =
        {
            // CCW로 나열하였지만 윈도우 좌표계를 사용하고 있으므로 데카르트 좌표계에서는 CW
            // CW : 해당 삼각형의 정점은 시계방향을 가정하고 데이터를 설정하였다 (y축이 뒤집어 있는 점을 주의하자)
            {0.0f, 0.0f, 0.0f,			0.0f, 1.0f, 0.0f,		1.0f, 0.0f, 0.0f},
            {1.0f, 0.0f, 0.0f,			0.0f, 1.0f, 0.0f,		1.0f, 1.0f, 0.0f}
        };
        
        //스케일 변환 행렬 
        float tScaleScalar = 1.0f;
        float tMatScale[4][4] = { 0 };

        tMatScale[0][0] = 1.0f * tScaleScalar;
        tMatScale[1][1] = 1.0f * tScaleScalar;
        tMatScale[2][2] = 1.0f * tScaleScalar;
        tMatScale[3][3] = 1.0f;

        //스케일 변환 적용
        SApiMesh tMeshScale;
        tMeshScale.tris =
        {
            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f}
        };
        //벡터와 스케일 변환 행렬을 곱하자 
        for (int ti = 0; ti < 2; ++ti)
        {
            MultiplyMatrixVectorApi(tMesh.tris[ti].p[0], tMeshScale.tris[ti].p[0], tMatScale);
            MultiplyMatrixVectorApi(tMesh.tris[ti].p[1], tMeshScale.tris[ti].p[1], tMatScale);
            MultiplyMatrixVectorApi(tMesh.tris[ti].p[2], tMeshScale.tris[ti].p[2], tMatScale);
        }

        float tMatRotate[4][4] = { 0 };
        // x축 회전축을 가정하고 회전
        /*tMatRotate[0][0] = 1.0f;
        tMatRotate[1][1] = 1.0f;
        tMatRotate[2][2] = 1.0f;
        tMatRotate[3][3] = 1.0f;*/

        static float mTheta = 0.0f;
        mTheta += 1.0f * tDeltaTime;

        tMatRotate[0][0] = 1.0f;
        tMatRotate[1][1] = cosf(mTheta);
        tMatRotate[1][2] = sinf(mTheta);
        tMatRotate[2][1] = -1.0f * sinf(mTheta);
        tMatRotate[2][2] = cosf(mTheta);
        tMatRotate[3][3] = 1.0f;


        //회전 변환 적용
        SApiMesh tMeshRotate;
        tMeshRotate.tris =
        {
            {0.0f, 0.0f, 0.0f,          0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f,          0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f}
        };
        //벡터와 회전 변환 행렬을 곱하자 
        for (int ti = 0; ti < 2; ++ti)
        {
            MultiplyMatrixVectorApi(tMeshScale.tris[ti].p[0], tMeshRotate.tris[ti].p[0], tMatRotate);
            MultiplyMatrixVectorApi(tMeshScale.tris[ti].p[1], tMeshRotate.tris[ti].p[1], tMatRotate);
            MultiplyMatrixVectorApi(tMeshScale.tris[ti].p[2], tMeshRotate.tris[ti].p[2], tMatRotate);
        }


        // 이동변환행렬
        float tMatTranslate[4][4] = { 0 };

        tMatTranslate[0][0] = 1.0f;
        tMatTranslate[1][1] = 1.0f;
        tMatTranslate[2][2] = 1.0f;
        tMatTranslate[3][3] = 1.0f;

        tMatTranslate[3][0] = 0.0f;
        tMatTranslate[3][1] = 0.0f;
        tMatTranslate[3][2] = 6.0f; // z축 전방으로 6만큼 이동

        // 이동 변환 적용
        SApiMesh tMeshTranslate;
        tMeshTranslate.tris =
        {
            {0.0f,0.0f, 0.0f,       0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},
            {0.0f,0.0f, 0.0f,       0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f}
        };
        //벡터와 스케일 변환 행렬을 곱하자 
        for (int ti = 0; ti < 2; ++ti)
        {
            MultiplyMatrixVectorApi(tMeshRotate.tris[ti].p[0], tMeshTranslate.tris[ti].p[0], tMatTranslate);
            MultiplyMatrixVectorApi(tMeshRotate.tris[ti].p[1], tMeshTranslate.tris[ti].p[1], tMatTranslate);
            MultiplyMatrixVectorApi(tMeshRotate.tris[ti].p[2], tMeshTranslate.tris[ti].p[2], tMatTranslate);
        }

        //정직하게
        /*float tNear = 0.7f;//0.1f;
        float tFar          = 1.0f;
        float tR            = 1.0f * 0.5f;
        float tL            = -1.0f * 1.0f * 0.5f;
        float tT            = 0.5f * 0.5f;
        float tB            = -1.0f * 0.5f * 0.5f;

        float tMatProj[4][4] = { 0 };

        tMatProj[0][0] = (2.0f * tNear) / (tR - tL);
        tMatProj[1][1] = (2.0f * tNear) / (tT - tB); // customized instead of this
        tMatProj[2][2] = -1.0f * (tFar + tNear) / (tFar - tNear);
        tMatProj[3][2] = -2.0f * tNear * (tFar / (tFar - tNear));
        //tMatProj[2][3] = -1.0f;
        tMatProj[2][3] = 1.0f; // z축 양의 방향을 모니터 안쪽방향으로 가정하였다
        tMatProj[3][3] = 0.0f;

        //tMatProj[2][0] = (tR + tL) / (tR - tL);
        //tMatProj[2][1] = (tT + tB) / (tT - tB);*/

        float tNear = 0.7f;//0.1f;
        float tFar = 1.0f;
        float tFov = 90.0f; // 시야각 degree
        float tAspectRatio = (float)ScreenHeight() / (float)ScreenWidth(); // Aspect Ratio 종횡비
        float tFovRad = 1.0f / tanf((tFov * 0.5f) * 3.14159f / 180.0f);
        //float tR = 1.0f * 0.5f;
        //float tL = -1.0f * 1.0f * 0.5f;
        //float tT = 0.5f * 0.5f;
        //float tB = -1.0f * 0.5f * 0.5f;

        float tMatProj[4][4] = { 0 };

        tMatProj[0][0] = tAspectRatio * tFovRad;
        tMatProj[1][1] = tFovRad;
        tMatProj[2][2] = -1.0f * (tFar + tNear) / (tFar - tNear);
        tMatProj[3][2] = -2.0f * tNear * (tFar / (tFar - tNear));
        //tMatProj[2][3] = -1.0f;
        tMatProj[2][3] = 1.0f;		//z축 양의 방향을 모니터 안쪽방향으로 가정하였다. 
        tMatProj[3][3] = 0.0f;

        //tMatProj[2][0] = 0; //(tR + tL) / (tR - tL);
        //tMatProj[2][1] = 0; //(tT + tB) / (tT - tB);

        /*tMatProj[0][0] = 1.0f;
        tMatProj[1][1] = 1.0f;
        tMatProj[2][2] = 1.0f;
        tMatProj[3][3] = 1.0f;*/

        //투영 변환 적용
        SApiMesh tMeshProj;
        tMeshProj.tris =
        {
            { 0.0f, 0.0f, 0.0f,			0.0f, 0.0f, 0.0f,		0.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 0.0f,			0.0f, 0.0f, 0.0f,		0.0f, 0.0f, 0.0f }
        };

        int ti = 0;
        for (auto t : tMeshTranslate.tris)
        {
            MultiplyMatrixVectorApi(t.p[0], tMeshProj.tris[ti].p[0], tMatProj);
            MultiplyMatrixVectorApi(t.p[1], tMeshProj.tris[ti].p[1], tMatProj);
            MultiplyMatrixVectorApi(t.p[2], tMeshProj.tris[ti].p[2], tMatProj);

            // 간단히 뷰포트 변환을 적용하였다.
            // 투영이 적용된 적용된 정점들에 대해 x축 양의 방향으로 1만큼 이동, y축 양의 방향으로 1만큼 이동
            tMeshProj.tris[ti].p[0].x += 1.0f;
            tMeshProj.tris[ti].p[0].y += 1.0f;

            tMeshProj.tris[ti].p[1].x += 1.0f;
            tMeshProj.tris[ti].p[1].y += 1.0f;

            tMeshProj.tris[ti].p[2].x += 1.0f;
            tMeshProj.tris[ti].p[2].y += 1.0f;

            // 화면 너비, 높이를 고려하여 비율을 늘려주었다
            tMeshProj.tris[ti].p[0].x *= 0.5f * (float)ScreenWidth();
            tMeshProj.tris[ti].p[0].y *= 0.5f * (float)ScreenHeight();

            tMeshProj.tris[ti].p[1].x *= 0.5f * (float)ScreenWidth();
            tMeshProj.tris[ti].p[1].y *= 0.5f * (float)ScreenHeight();

            tMeshProj.tris[ti].p[2].x *= 0.5f * (float)ScreenWidth();
            tMeshProj.tris[ti].p[2].y *= 0.5f * (float)ScreenHeight();

            ti++;
        }

        for (auto t : tMeshProj.tris)
        {
            DrawTriangle(t.p[0].x, t.p[0].y,
                         t.p[1].x, t.p[1].y,
                         t.p[2].x, t.p[2].y);
        }

        this->Present();
    }

    //행벡터에 행렬을 곱셈하여 행벡터를 구하는 형태로 되어 있다.
    //( 행렬의 곱셈의 정의와 동차좌표 연산을 고려하여 구현되었다. )
    void MultiplyMatrixVectorApi(SApiVector3& tIn, SApiVector3& tOut, float tM[][4])
    {
        tOut.x = tIn.x * tM[0][0] + tIn.y * tM[1][0] + tIn.z * tM[2][0] + 1.0f * tM[3][0];
        tOut.y = tIn.x * tM[0][1] + tIn.y * tM[1][1] + tIn.z * tM[2][1] + 1.0f * tM[3][1];
        tOut.z = tIn.x * tM[0][2] + tIn.y * tM[1][2] + tIn.z * tM[2][2] + 1.0f * tM[3][2];

        float tW = tIn.x * tM[0][3] + tIn.y * tM[1][3] + tIn.z * tM[2][3] + 1.0f * tM[3][3];

        if (tW != 0.0f)
        {
            tOut.x = tOut.x / tW;
            tOut.y = tOut.y / tW;
            tOut.z = tOut.z / tW;
        }
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
