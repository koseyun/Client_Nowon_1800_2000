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

// ������ ��ġ �ε���, UV �ε���, normal �ε����� �ѽ����� �ٷ�� ���� ����ü
struct TEST
{
    int mFace;
    int mUV;
    int mNormal;
};

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
    vector<XMFLOAT3> mVertices; // ���������� ������� ���� ��ġ �����͸� ��Ƶ� �迭
    vector<XMFLOAT2> mUVs;      // ���������� ������� UV �����͸� ��Ƶ� �迭
    vector<XMFLOAT3> mNormals;  // ���������� ������� ���� �����͸� ��Ƶ� �迭

    vector<int> mIndexVertices; // ���������� ������� ������ ��ġ �������� �ε����� ��Ƶ� �����迭
    vector<int> mIndexUVs;      // ���������� ������� ������ UV �������� �ε����� ��Ƶ� �����迭
    vector<int> mIndexNormals;  // ���������� ������� ������ ���� �������� �ε����� ��Ƶ� �����迭

    // �簡���� �߰��ܰ迡 �ʿ��� �ڷᱸ�����̴�
    vector<TEST> mAPI;      // ���Ͽ� ��ϵ� ���� ��ġindex, UVindex, normal index�� �ѽ����� �����صд�
    vector<XMFLOAT3> mTT;   // ���Ͽ� ��ϵ� ������ ��ġ �����͸� ��Ƶ� �����迭
    vector<XMFLOAT3> mNN;   // ���Ͽ� ��ϵ� ������ ���� �����͸� ��Ƶ� �����迭
    vector<XMFLOAT2> mAAAA; // ���Ͽ� ��ϵ� ������ UV �����͸� ��Ƶ� �����迭

    bool LoadFromObjectFile(string tFileName)
    {
        // ������ ����
        std::ifstream tFile(tFileName);
        if (!tFile.is_open())
        {
            return false;
        }

        int tIndexReal = 0;

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
                    //UVs.push_back(tUV);
                    mAAAA.push_back(tUV);
                }
                // ���� ������ ó��
                if ('n' == tLine[1])
                {
                    XMFLOAT3 tNormal;
                    tStr >> tJunk >> tJunk >> tNormal.x >> tNormal.y >> tNormal.z;
                    // ���Ϸκ��� ���� �����͸� �״�� ����
                    //mNormals.push_back(tNormal);
                    mNN.push_back(tNormal);
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
                    //mVertices.push_back(tPos);
                    mTT.push_back(tPos);
                }
            }
            // �� ������ ó�� 
            if ('f' == tLine[0])
            {
                TEST tTest[3];

                int tFace[3];
                int tUV[3];
                int tNormal[3];
                                
                tStr >> tJunk >>
                    tTest[0].mFace >> tJunk >> tTest[0].mUV >> tJunk >> tTest[0].mNormal >>
                    tTest[1].mFace >> tJunk >> tTest[1].mUV >> tJunk >> tTest[1].mNormal >>
                    tTest[2].mFace >> tJunk >> tTest[2].mUV >> tJunk >> tTest[2].mNormal;

                // �߰� �簡�� �ܰ�. �� �ܰ踦 ��� ��ġ�� �ε��� ������ ����� ����ȴ�
                //int tIndexReal = 0;
                bool tIsBe = false;
                // �����˻�
                for (int ti = 0; ti < mAPI.size(); ++ti)
                {
                    if (tTest[0].mFace == mAPI[ti].mFace &&
                        tTest[0].mUV == mAPI[ti].mUV &&
                        tTest[0].mNormal == mAPI[ti].mNormal)
                    {
                        mIndexVertices.push_back(ti);
                        mIndexUVs.push_back(ti);
                        mIndexNormals.push_back(ti);

                        tIsBe = true;
                        break;
                    }
                }
                // ó������ ���Ӱ� �߰��Ǵ� �ε��� ������
                if (!tIsBe)
                {
                    // �ѽ��� ���� �����͸� mAPI �ڷᱸ���� �߰�
                    mAPI.push_back(tTest[0]);

                    mIndexVertices.push_back(tIndexReal);
                    mIndexUVs.push_back(tIndexReal);
                    mIndexNormals.push_back(tIndexReal);

                    tIndexReal++;
                }

                tIsBe = false;
                // �����˻�
                for (int ti = 0; ti < mAPI.size(); ++ti)
                {
                    if (tTest[1].mFace == mAPI[ti].mFace &&
                        tTest[1].mUV == mAPI[ti].mUV &&
                        tTest[1].mNormal == mAPI[ti].mNormal)
                    {
                        mIndexVertices.push_back(ti);
                        mIndexUVs.push_back(ti);
                        mIndexNormals.push_back(ti);

                        tIsBe = true;
                        break;
                    }
                }
                // ó������ ���Ӱ� �߰��Ǵ� �ε��� ������
                if (!tIsBe)
                {
                    // �ѽ��� ���� �����͸� mAPI �ڷᱸ���� �߰�
                    mAPI.push_back(tTest[1]);

                    mIndexVertices.push_back(tIndexReal);
                    mIndexUVs.push_back(tIndexReal);
                    mIndexNormals.push_back(tIndexReal);

                    tIndexReal++;
                }

                tIsBe = false;
                // �����˻�
                for (int ti = 0; ti < mAPI.size(); ++ti)
                {
                    if (tTest[2].mFace == mAPI[ti].mFace &&
                        tTest[2].mUV == mAPI[ti].mUV &&
                        tTest[2].mNormal == mAPI[ti].mNormal)
                    {
                        mIndexVertices.push_back(ti);
                        mIndexUVs.push_back(ti);
                        mIndexNormals.push_back(ti);

                        tIsBe = true;
                        break;
                    }
                }
                // ó������ ���Ӱ� �߰��Ǵ� �ε��� ������
                if (!tIsBe)
                {
                    // �ѽ��� ���� �����͸� mAPI �ڷᱸ���� �߰�
                    mAPI.push_back(tTest[2]);

                    mIndexVertices.push_back(tIndexReal);
                    mIndexUVs.push_back(tIndexReal);
                    mIndexNormals.push_back(tIndexReal);

                    tIndexReal++;
                }

                /*
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
                mIndexNormals.push_back(tNormal[2] - 1);*/
            }
        }

        // ���� �������� ������ �����͵��� �����
        // �ε��� ������ŭ �ݺ��ϸ鼭 ����������(��ġ, UV, Normal)�� ���� �簡���Ѵ�
        for (int ti = 0; ti < mAPI.size(); ++ti)
        {
            int tIndexFace      = mAPI[ti].mFace - 1;
            int tIndexUV        = mAPI[ti].mUV - 1;
            int tIndexNormal    = mAPI[ti].mNormal - 1;

            mVertices.push_back(mTT[tIndexFace]);
            mUVs.push_back(mAAAA[tIndexUV]);
            mNormals.push_back(mNN[tIndexNormal]);
        }

        return true;
    }

    /*// Obj���Ϸκ��� �� ������ �ε��Ͽ� ���� 
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
    }*/
};
