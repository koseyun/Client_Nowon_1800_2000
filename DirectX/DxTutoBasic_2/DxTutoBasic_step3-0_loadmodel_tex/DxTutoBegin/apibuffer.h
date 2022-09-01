#pragma once

#include "framework.h"

struct SimpleVertex
{
    XMFLOAT3 Pos;       // 정점의 위치 정보 x,y,z

    //XMFLOAT4 Color;         // 정점의 색상 정보 r,g,b,a
    XMFLOAT3 Normal;        // 법선벡터 정보 x,y,z
    XMFLOAT2 Tex;           // 텍스쳐 좌표 정보, UV
};

struct CBTransform
{
    XMMATRIX mWorld;            // 월드 변환행렬           4* 4*4 = 64byte
    XMMATRIX mView;             // 뷰 변환행렬             4* 4*4 = 64byte
    XMMATRIX mProjection;       // 투영 변환행렬           4* 4*4 = 64byte

    // 빛에 기반한 음영 계산을 위해 빛방향 벡터, 빛의 색상에 대한 정보를 XMFLOAT4로 선언하였다
    XMFLOAT4 LightDir;          // 빛방향벡터                 4* 4 = 16byte
    XMFLOAT4 LightColor;        // 빛 색상                    4* 4 = 16byte
};
