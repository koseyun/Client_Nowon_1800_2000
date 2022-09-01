#pragma once
#include "framework.h"

class CDX_Engine;

class CMesh
{
public:
    CMesh();
    ~CMesh();

    // delete���� �̿��� ���
    CMesh(const CMesh& t) = delete;

// �������� ���
//private:
    //CMesh(const CMesh& t) {};

    // �ܺο��� ȣ��� �Լ�
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

    // ���ο��� ȣ���� �Լ�, 
    // ������ ���������ο��� ���̴����� �ٷ�� buffer��� ������ �������� �̸�������
private:
    void CreateBuffers(ID3D11Device* tpDevice);
    void ShutdownBuffers();
    void RenderBuffers(ID3D11DeviceContext* tpDeviceContext);

public:
    ID3D11Buffer* mpVertexBuffer = nullptr; // �������� �ִ� ������ ������. �� ���ÿ����� �ﰢ�� �����͸� ���� ���̴�

    // VertexBuffer�� ������ �����Ͽ� �׸����� ����
    ID3D11Buffer* mpIndexBuffer = nullptr;

    int mCountVertex = 0;   // ���� �������� ����
    int mCountIndex = 0;    // �ε��� �������� ����

    CDX_Engine* mpEngine = nullptr;
};

