#pragma once
#include "framework.h"

//파일 스트림, 문자열 스트림의 기능을 이용하자
#include <fstream>
#include <strstream>
//가변배열 
#include <vector>

using namespace std;

class CDX_Engine;
class CTextureApi;

// 정점의 위치 인덱스, UV 인덱스, normal 인덱스를 한쌍으로 다루기 위한 구조체
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

    // delete예약어를 이용한 방법
    CMesh(const CMesh& t) = delete;

// 전통적인 방법
//private:
    //CMesh(const CMesh& t) {};

    // 외부에서 호출될 함수
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

    // 내부에서 호출할 함수, 
    // 랜더링 파이프라인에서 셰이더에서 다루는 buffer라는 개념을 바탕으로 이름지었다
private:
    void CreateBuffers(ID3D11Device* tpDevice);
    void ShutdownBuffers();
    void RenderBuffers(ID3D11DeviceContext* tpDeviceContext);

public:
    ID3D11Buffer* mpVertexBuffer = nullptr; // 비디오램에 있는 임의의 데이터. 이 예시에서는 삼각형 데이터를 담을 것이다

    // VertexBuffer의 내용을 참고하여 그리기할 정보
    ID3D11Buffer* mpIndexBuffer = nullptr;

    int mCountVertex = 0;   // 정점 데이터의 개수
    int mCountIndex = 0;    // 인덱스 데이터의 개수

    CTextureApi* mpTexture = nullptr;

    CDX_Engine* mpEngine = nullptr;

private:
    vector<XMFLOAT3> mVertices; // 최종적으로 만들어질 정점 위치 데이터를 담아둘 배열
    vector<XMFLOAT2> mUVs;      // 최종적으로 만들어질 UV 데이터를 담아둘 배열
    vector<XMFLOAT3> mNormals;  // 최종적으로 만들어질 법선 데이터를 담아둘 배열

    vector<int> mIndexVertices; // 최종적으로 만들어질 정점의 위치 데이터의 인덱스를 담아둘 가변배열
    vector<int> mIndexUVs;      // 최종적으로 만들어질 정점의 UV 데이터의 인덱스를 담아둘 가변배열
    vector<int> mIndexNormals;  // 최종적으로 만들어질 정점의 법선 데이터의 인덱스를 담아둘 가변배열

    // 재가공의 중간단계에 필요한 자료구조들이다
    vector<TEST> mAPI;      // 파일에 기록된 정점 위치index, UVindex, normal index를 한쌍으로 적재해둔다
    vector<XMFLOAT3> mTT;   // 파일에 기록된 정점의 위치 데이터를 담아둘 가변배열
    vector<XMFLOAT3> mNN;   // 파일에 기록된 정점의 법선 데이터를 담아둘 가변배열
    vector<XMFLOAT2> mAAAA; // 파일에 기록된 정점의 UV 데이터를 담아둘 가변배열

    bool LoadFromObjectFile(string tFileName)
    {
        // 파일을 연다
        std::ifstream tFile(tFileName);
        if (!tFile.is_open())
        {
            return false;
        }

        int tIndexReal = 0;

        // 파일끝까지 돌면서 데이터 로드하여 적재
        while (!tFile.eof())
        {
            char tLine[256] = { 0 };    // c style 문자열
            tFile.getline(tLine, 256);  // 파일에서 한줄 읽어들임 

            strstream tStr;
            tStr << tLine; // strstream타입의 데이터에 담아둔다

            // 불필요한 문자를 처리할 변수
            char tJunk;

            if ('v' == tLine[0])
            {
                // 텍스쳐 좌표 처리
                if ('t' == tLine[1])
                {
                    XMFLOAT2 tUV;
                    tStr >> tJunk >> tJunk >> tUV.x >> tUV.y;
                    // 파일로부터 얻어온 데이터를 그대로 적재
                    //UVs.push_back(tUV);
                    mAAAA.push_back(tUV);
                }
                // 법선 데이터 처리
                if ('n' == tLine[1])
                {
                    XMFLOAT3 tNormal;
                    tStr >> tJunk >> tJunk >> tNormal.x >> tNormal.y >> tNormal.z;
                    // 파일로부터 얻어온 데이터를 그대로 적재
                    //mNormals.push_back(tNormal);
                    mNN.push_back(tNormal);
                }
            }
            // 위치 데이터 처리 
            if ('v' == tLine[0])
            {
                if ('t' != tLine[1] && 'n' != tLine[1])
                {
                    XMFLOAT3 tPos;
                    tStr >> tJunk >> tPos.x >> tPos.y >> tPos.z;
                    //파일로부터 얻어온 데이터를 그대로 적재
                    //mVertices.push_back(tPos);
                    mTT.push_back(tPos);
                }
            }
            // 면 데이터 처리 
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

                // 중간 재가공 단계. 이 단계를 모두 거치면 인덱스 정보가 제대로 구축된다
                //int tIndexReal = 0;
                bool tIsBe = false;
                // 순차검색
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
                // 처음으로 새롭게 추가되는 인덱스 데이터
                if (!tIsBe)
                {
                    // 한쌍인 정점 데이터를 mAPI 자료구조에 추가
                    mAPI.push_back(tTest[0]);

                    mIndexVertices.push_back(tIndexReal);
                    mIndexUVs.push_back(tIndexReal);
                    mIndexNormals.push_back(tIndexReal);

                    tIndexReal++;
                }

                tIsBe = false;
                // 순차검색
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
                // 처음으로 새롭게 추가되는 인덱스 데이터
                if (!tIsBe)
                {
                    // 한쌍인 정점 데이터를 mAPI 자료구조에 추가
                    mAPI.push_back(tTest[1]);

                    mIndexVertices.push_back(tIndexReal);
                    mIndexUVs.push_back(tIndexReal);
                    mIndexNormals.push_back(tIndexReal);

                    tIndexReal++;
                }

                tIsBe = false;
                // 순차검색
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
                // 처음으로 새롭게 추가되는 인덱스 데이터
                if (!tIsBe)
                {
                    // 한쌍인 정점 데이터를 mAPI 자료구조에 추가
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

                // 정점의 위치 데이터의 인덱스 정보 취합
                mIndexVertices.push_back(tFace[0] - 1);
                mIndexVertices.push_back(tFace[1] - 1);
                mIndexVertices.push_back(tFace[2] - 1);

                // 정점의 UV 데이터의 인덱스 정보 취합
                mIndexUVs.push_back(tUV[0] - 1);
                mIndexUVs.push_back(tUV[1] - 1);
                mIndexUVs.push_back(tUV[2] - 1);

                // 정점의 법선 데이터의 인덱스 정보 취합
                mIndexNormals.push_back(tNormal[0] - 1);
                mIndexNormals.push_back(tNormal[1] - 1);
                mIndexNormals.push_back(tNormal[2] - 1);*/
            }
        }

        // 실제 랜더링에 참조할 데이터들을 만든다
        // 인덱스 개수만큼 반복하면서 정점데이터(위치, UV, Normal)를 최종 재가공한다
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

    /*// Obj파일로부터 모델 데이터 로드하여 적재 
    bool LoadFromObjectFile(string tFileName)
    {
        // 파일을 연다
        std::ifstream tFile(tFileName);
        if (!tFile.is_open())
        {
            return false;
        }
        // 파일끝까지 돌면서 데이터 로드하여 적재
        while (!tFile.eof())
        {
            char tLine[256] = { 0 };    // c style 문자열
            tFile.getline(tLine, 256);  // 파일에서 한줄 읽어들임 

            strstream tStr;
            tStr << tLine; // strstream타입의 데이터에 담아둔다

            // 불필요한 문자를 처리할 변수
            char tJunk;

            if ('v' == tLine[0])
            {
                // 텍스쳐 좌표 처리
                if ('t' == tLine[1])
                {
                    XMFLOAT2 tUV;
                    tStr >> tJunk >> tJunk >> tUV.x >> tUV.y;
                    // 파일로부터 얻어온 데이터를 그대로 적재
                    mUVs.push_back(tUV);
                }
                // 법선 데이터 처리
                if ('n' == tLine[1])
                {
                    XMFLOAT3 tNormal;
                    tStr >> tJunk >> tJunk >> tNormal.x >> tNormal.y >> tNormal.z;
                    // 파일로부터 얻어온 데이터를 그대로 적재
                    mNormals.push_back(tNormal);
                }
            }
            // 위치 데이터 처리 
            if ('v' == tLine[0])
            {
                if ('t' != tLine[1] && 'n' != tLine[1])
                {
                    XMFLOAT3 tPos;
                    tStr >> tJunk >> tPos.x >> tPos.y >> tPos.z;
                    //파일로부터 얻어온 데이터를 그대로 적재
                    mVertices.push_back(tPos);
                }
            }
            // 면 데이터 처리 
            if ('f' == tLine[0])
            {
                int tFace[3];
                int tUV[3];
                int tNormal[3];

                tStr >> tJunk >>
                    tFace[0] >> tJunk >> tUV[0] >> tJunk >> tNormal[0] >>
                    tFace[1] >> tJunk >> tUV[1] >> tJunk >> tNormal[1] >>
                    tFace[2] >> tJunk >> tUV[2] >> tJunk >> tNormal[2];


                // 정점의 위치 데이터의 인덱스 정보 취합
                mIndexVertices.push_back(tFace[0] - 1);
                mIndexVertices.push_back(tFace[1] - 1);
                mIndexVertices.push_back(tFace[2] - 1);

                // 정점의 UV 데이터의 인덱스 정보 취합
                mIndexUVs.push_back(tUV[0] - 1);
                mIndexUVs.push_back(tUV[1] - 1);
                mIndexUVs.push_back(tUV[2] - 1);

                // 정점의 법선 데이터의 인덱스 정보 취합
                mIndexNormals.push_back(tNormal[0] - 1);
                mIndexNormals.push_back(tNormal[1] - 1);
                mIndexNormals.push_back(tNormal[2] - 1);
            }
        }
        return true;
    }*/
};
