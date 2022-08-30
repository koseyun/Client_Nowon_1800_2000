#pragma once

#include "framework.h"

struct SimpleVertex
{
    XMFLOAT3 Pos;       // ������ ��ġ ���� x,y,z

    //XMFLOAT4 Color;         // ������ ���� ���� r,g,b,a
    XMFLOAT3 Normal;        // �������� ���� x,y,z
    XMFLOAT2 Tex;           // �ؽ��� ��ǥ ����, UV
};

struct CBTransform
{
    XMMATRIX mWorld;            // ���� ��ȯ���           4* 4*4 = 64byte
    XMMATRIX mView;             // �� ��ȯ���             4* 4*4 = 64byte
    XMMATRIX mProjection;       // ���� ��ȯ���           4* 4*4 = 64byte

    // ���� ����� ���� ����� ���� ������ ����, ���� ���� ���� ������ XMFLOAT4�� �����Ͽ���
    XMFLOAT4 LightDir;          // �����⺤��                 4* 4 = 16byte
    XMFLOAT4 LightColor;        // �� ����                    4* 4 = 16byte
};
