/*
    이번 예시에서는 shading(음영)을 만들겠다

        <-- 일반적으로 용어를 말해보자
        shading : 3D 그래픽스에서 최종색상결정(물체의 색상 + 텍스쳐 + 조명)을 이야기한다
        material : How to Shading, 셰이딩을 하는 데이터와 방법론을 함께 아우르는 개념이다

        램버트 조명 모델
        빛벡터 dot 법선벡터 --> 광량을 구함. 이것을 색상음영값으로 사용
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

    ApiPixel color; // 회색조 음영 표현 데이터
};

// 메시
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

        // Render
        this->Clear(0.1f, 0.1f, 0.3f);
                
        SApiMesh tMesh;
        tMesh.tris =
        {
            // CCW로 나열하였지만 윈도우 좌표계를 사용하고 있으므로 데카르트 좌표계에서는 CW
            // CW : 해당 삼각형의 정점은 시계방향을 가정하고 데이터를 설정하였다 (y축이 뒤집어 있는 점을 주의하자)
            // south
            {0.0f, 0.0f, 0.0f,			0.0f, 1.0f, 0.0f,		1.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 0.0f,			1.0f, 1.0f, 0.0f,		1.0f, 0.0f, 0.0f},

            // east
            {1.0f, 0.0f, 0.0f,			1.0f, 1.0f, 0.0f,		1.0f, 1.0f, 1.0f},
            {1.0f, 0.0f, 0.0f,			1.0f, 1.0f, 1.0f,		1.0f, 0.0f, 1.0f},
            
            // north
            {1.0f, 0.0f, 1.0f,			1.0f, 1.0f, 1.0f,		0.0f, 1.0f, 1.0f},
            {1.0f, 0.0f, 1.0f,			0.0f, 1.0f, 1.0f,		0.0f, 0.0f, 1.0f},

            // west
            {0.0f, 0.0f, 1.0f,			0.0f, 1.0f, 1.0f,		0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 1.0f,			0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 0.0f},

            // top
            {0.0f, 1.0f, 0.0f,			0.0f, 1.0f, 1.0f,		1.0f, 1.0f, 1.0f},
            {1.0f, 1.0f, 0.0f,			1.0f, 1.0f, 1.0f,		1.0f, 1.0f, 0.0f},

            // bottom
            {0.0f, 0.0f, 1.0f,			0.0f, 0.0f, 0.0f,		1.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 1.0f,			1.0f, 0.0f, 0.0f,		1.0f, 0.0f, 1.0f}
        };
        
        // 스케일 변환 행렬 
        float tScaleScalar = 1.0f;
        float tMatScale[4][4] = { 0 };

        tMatScale[0][0] = 1.0f * tScaleScalar;
        tMatScale[1][1] = 1.0f * tScaleScalar;
        tMatScale[2][2] = 1.0f * tScaleScalar;
        tMatScale[3][3] = 1.0f;

        // 스케일 변환 적용
        SApiMesh tMeshScale;
        tMeshScale.tris =
        {
            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},
            
            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},

            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},

            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},

            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},

            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f}
        };
        // 벡터와 스케일 변환 행렬을 곱하자
        for (int ti = 0; ti < 12; ++ti)
        {
            MultiplyMatrixVectorApi(tMesh.tris[ti].p[0], tMeshScale.tris[ti].p[0], tMatScale);
            MultiplyMatrixVectorApi(tMesh.tris[ti].p[1], tMeshScale.tris[ti].p[1], tMatScale);
            MultiplyMatrixVectorApi(tMesh.tris[ti].p[2], tMeshScale.tris[ti].p[2], tMatScale);
        }

        float tMatRotate[4][4] = { 0 };
        
        /*tMatRotate[0][0] = 1.0f;
        tMatRotate[1][1] = 1.0f;
        tMatRotate[2][2] = 1.0f;
        tMatRotate[3][3] = 1.0f;*/

        static float mTheta = 0.0f;
        mTheta += 1.0f * tDeltaTime;

        // x축 회전축을 가정하고 회전
        /*tMatRotate[0][0] = 1.0f;
        tMatRotate[1][1] = cosf(mTheta);
        tMatRotate[1][2] = sinf(mTheta);
        tMatRotate[2][1] = -1.0f * sinf(mTheta);
        tMatRotate[2][2] = cosf(mTheta);
        tMatRotate[3][3] = 1.0f;*/

        // y축 회전축을 가정하고 회전
        tMatRotate[0][0] = cosf(mTheta);
        tMatRotate[0][2] = -1.0f * sinf(mTheta);
        tMatRotate[1][1] = 1.0f;
        tMatRotate[2][0] = sinf(mTheta);
        tMatRotate[2][2] = cosf(mTheta);
        tMatRotate[3][3] = 1.0f;


        //회전 변환 적용
        SApiMesh tMeshRotate;
        tMeshRotate.tris =
        {
            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},

            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},

            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},

            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},

            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},

            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f}
        };
        //벡터와 회전 변환 행렬을 곱하자 
        for (int ti = 0; ti < 12; ++ti)
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
        tMatTranslate[3][2] = 2.5f; // z축 전방으로 6만큼 이동

        // 이동 변환 적용
        SApiMesh tMeshTranslate;
        tMeshTranslate.tris =
        {
            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},

            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},

            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},

            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},

            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},

            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f}
        };
        //벡터와 스케일 변환 행렬을 곱하자 
        for (int ti = 0; ti < 12; ++ti)
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
            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},

            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},

            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},

            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},

            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},

            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f}
        };

        int ti = 0;
        for (auto t : tMeshTranslate.tris)
        {
            SApiVector3 tNomal; // 삼각형 면의 법선 벡터(면에 수직인 단위벡터)
            SApiVector3 tLine_A; // A벡터
            SApiVector3 tLine_B; // B벡터

            tLine_A.x = t.p[1].x - t.p[0].x;
            tLine_A.y = t.p[1].y - t.p[0].y;
            tLine_A.z = t.p[1].z - t.p[0].z;

            tLine_B.x = t.p[2].x - t.p[0].x;
            tLine_B.y = t.p[2].y - t.p[0].y;
            tLine_B.z = t.p[2].z - t.p[0].z;

            // 외적의 오른손 법칙을 감안하여 외적순서를 정했다
            // B Cross A
            tNomal.x = tLine_B.y * tLine_A.z - tLine_B.z * tLine_A.y;
            tNomal.y = tLine_B.z * tLine_A.x - tLine_B.x * tLine_A.z;
            tNomal.z = tLine_B.x * tLine_A.y - tLine_B.y * tLine_A.x;

            // 정규화 normalized
            float tLength = std::sqrtf(tNomal.x * tNomal.x + tNomal.y * tNomal.y + tNomal.z * tNomal.z);
            // 자기자신을 내적한 것은 노름의 제곱과 같다

            tNomal.x = tNomal.x / tLength;
            tNomal.y = tNomal.y / tLength;
            tNomal.z = tNomal.z / tLength;


            SApiVector3 tPosMid; // 삼각형의 중심점
            tPosMid.x = t.p[0].x + t.p[1].x + t.p[2].x;
            tPosMid.y = t.p[0].y + t.p[1].y + t.p[2].y;
            tPosMid.z = t.p[0].z + t.p[1].z + t.p[2].z;

            SApiVector3 mPosMainCamera = { 0.0f, 0.0f, 0.0f }; // 카메라의 위치
            SApiVector3 tVecView; // 시선벡터
            tVecView.x = tPosMid.x - mPosMainCamera.x;
            tVecView.y = tPosMid.y - mPosMainCamera.y;
            tVecView.z = tPosMid.z - mPosMainCamera.z;

            // 시선벡터 정규화
            tLength = std::sqrtf(tVecView.x * tVecView.x + tVecView.y * tVecView.y + tVecView.z * tVecView.z);
            // 자기자신을 내적한 것은 노름의 제곱과 같다

            tVecView.x = tVecView.x / tLength;
            tVecView.y = tVecView.y / tLength;
            tVecView.z = tVecView.z / tLength;

            float tResultDot = tNomal.x * tVecView.x + tNomal.y * tVecView.y + tNomal.z * tVecView.z;

            
            // 빛이란 개념을 추가한다. 이 빛음 방향 개념을 나타내고 있다
            // (빛의 위치는 (0, 0, 0)이고 크기는 1, 방향은 (0, 0, 1)이다)
            SApiVector3 tVecLight = { 0.0f, 0.0f, 1.0f };

            // 램버트 조명모델을 이용하여 음영을 구하자
            
            // 먼저 두 벡터의 내적을 이용하여 광량(빛의 양)을 구한다
            float tDotLightIntensity = tNomal.x * tVecLight.x + tNomal.y * tVecLight.y + tNomal.z * tVecLight.z;
            t.color = GetColor(tDotLightIntensity); // 면의 색상(음영)값으로 설정

            // 전면이라고 판단된 삼각형만 렌더링한다
            if (tResultDot >= 0.0f)
            {
                // 삼각형의 위치값 변환
                MultiplyMatrixVectorApi(t.p[0], tMeshProj.tris[ti].p[0], tMatProj);
                MultiplyMatrixVectorApi(t.p[1], tMeshProj.tris[ti].p[1], tMatProj);
                MultiplyMatrixVectorApi(t.p[2], tMeshProj.tris[ti].p[2], tMatProj);

                // 색상(음영)값도 전달한다
                tMeshProj.tris[ti].color = t.color;

                // 간단히 뷰포트 변환을 적용하였다
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
                              
                FillTriangle(tMeshProj.tris[ti].p[0].x, tMeshProj.tris[ti].p[0].y,
                             tMeshProj.tris[ti].p[1].x, tMeshProj.tris[ti].p[1].y,
                             tMeshProj.tris[ti].p[2].x, tMeshProj.tris[ti].p[2].y,
                             tMeshProj.tris[ti].color);

                /*DrawTriangle(tMeshProj.tris[ti].p[0].x, tMeshProj.tris[ti].p[0].y,
                             tMeshProj.tris[ti].p[1].x, tMeshProj.tris[ti].p[1].y,
                             tMeshProj.tris[ti].p[2].x, tMeshProj.tris[ti].p[2].y,
                             0.0f, 0.0f, 0.0f);*/
            }

            ti++;
        }

        /*for (auto t : tMeshProj.tris)
        {
            DrawTriangle(t.p[0].x, t.p[0].y,
                         t.p[1].x, t.p[1].y,
                         t.p[2].x, t.p[2].y);
        }*/

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

    // 광량 -> 색상값(음영)
    ApiPixel GetColor(float tLightIntenseity)
    {
        ApiPixel tResult;

        tResult.r = tLightIntenseity * 255.0f;
        tResult.g = tLightIntenseity * 255.0f;
        tResult.b = tLightIntenseity * 255.0f;

        return tResult;
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
