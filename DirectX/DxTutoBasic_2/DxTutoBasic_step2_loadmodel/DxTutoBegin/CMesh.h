#pragma once
#include "framework.h"

//���� ��Ʈ��, ���ڿ� ��Ʈ���� ����� �̿�����
#include <fstream>
#include <strstream>
//�����迭 
#include <vector>

using namespace std;

class CDX_Engine;
class CTextureApi;

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
    void Create(ID3D11Device* tpDevice, LPCWSTR tpFileName);
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

    ID3D11ShaderResourceView* GetTexture();

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

    CTextureApi* mpTexture = nullptr;

    CDX_Engine* mpEngine = nullptr;

private:
    vector<XMFLOAT3> mVertices; // ���Ͽ� ��ϵ� ������ ��ġ �����͸� ��Ƶ� �����迭
    vector<XMFLOAT2> mUVs; // ���Ͽ� ��ϵ� ������ UV �����͸� ��Ƶ� �����迭
    vector<XMFLOAT3> mNormals; // ���Ͽ� ��ϵ� ������ ���� �����͸� ��Ƶ� �����迭

    vector<int> mIndexVertices; // ���Ͽ� ��ϵ� ������ ��ġ �������� �ε����� ��Ƶ� �����迭
    vector<int> mIndexUVs;  // ���Ͽ� ��ϵ� ������ UV �������� �ε����� ��Ƶ� �����迭
    vector<int> mIndexNormals;  // ���Ͽ� ��ϵ� ������ ���� �������� '�ε����� ��Ƶ� �����迭

    // Obj���Ϸκ��� �� ������ �ε��Ͽ� ���� 
    bool LoadFromObjectFile(string tFileName)
    {
        // ������ ����
        std::ifstream tFile(tFileName);
        if (!tFile.is_open())
        {
            return false;
        }
        // ���ϳ����� ���鼭 ������ �ε��Ͽ� ����
        while (!tFile.eof())
        {
            char tLine[256] = { 0 };    // c style ���ڿ�
            tFile.getline(tLine, 256);  // ���Ͽ��� ���� �о���� 

            strstream tStr;
            tStr << tLine; // strstreamŸ���� �����Ϳ� ��Ƶд�

            // ���ʿ��� ���ڸ� ó���� ����
            char tJunk;

            if ('v' == tLine[0])
            {
                // �ؽ��� ��ǥ ó��
                if ('t' == tLine[1])
                {
                    XMFLOAT2 tUV;
                    tStr >> tJunk >> tJunk >> tUV.x >> tUV.y;
                    // ���Ϸκ��� ���� �����͸� �״�� ����
                    mUVs.push_back(tUV);
                }
                // ���� ������ ó��
                if ('n' == tLine[1])
                {
                    XMFLOAT3 tNormal;
                    tStr >> tJunk >> tJunk >> tNormal.x >> tNormal.y >> tNormal.z;
                    // ���Ϸκ��� ���� �����͸� �״�� ����
                    mNormals.push_back(tNormal);
                }
            }
            // ��ġ ������ ó�� 
            if ('v' == tLine[0])
            {
                if ('t' != tLine[1] && 'n' != tLine[1])
                {
                    XMFLOAT3 tPos;
                    tStr >> tJunk >> tPos.x >> tPos.y >> tPos.z;
                    //���Ϸκ��� ���� �����͸� �״�� ����
                    mVertices.push_back(tPos);
                }
            }
            // �� ������ ó�� 
            if ('f' == tLine[0])
            {
                int tFace[3];
                int tUV[3];
                int tNormal[3];

                tStr >> tJunk >>
                    tFace[0] >> tJunk >> tUV[0] >> tJunk >> tNormal[0] >>
                    tFace[1] >> tJunk >> tUV[1] >> tJunk >> tNormal[1] >>
                    tFace[2] >> tJunk >> tUV[2] >> tJunk >> tNormal[2];

                // ������ ��ġ �������� �ε��� ���� ����
                mIndexVertices.push_back(tFace[0] - 1);
                mIndexVertices.push_back(tFace[1] - 1);
                mIndexVertices.push_back(tFace[2] - 1);

                // ������ UV �������� �ε��� ���� ����
                mIndexUVs.push_back(tUV[0] - 1);
                mIndexUVs.push_back(tUV[1] - 1);
                mIndexUVs.push_back(tUV[2] - 1);

                // ������ ���� �������� �ε��� ���� ����
                mIndexNormals.push_back(tNormal[0] - 1);
                mIndexNormals.push_back(tNormal[1] - 1);
                mIndexNormals.push_back(tNormal[2] - 1);
            }
        }
        return true;
    }
};
