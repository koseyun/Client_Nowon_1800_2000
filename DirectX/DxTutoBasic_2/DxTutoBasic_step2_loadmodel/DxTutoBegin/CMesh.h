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
    vector<XMFLOAT3> mVertices; // 파일에 기록된 정점의 위치 데이터를 담아둘 가변배열
    vector<XMFLOAT2> mUVs; // 파일에 기록된 정점의 UV 데이터를 담아둘 가변배열
    vector<XMFLOAT3> mNormals; // 파일에 기록된 정점의 법선 데이터를 담아둘 가변배열

    vector<int> mIndexVertices; // 파일에 기록된 정점의 위치 데이터의 인덱스를 담아둘 가변배열
    vector<int> mIndexUVs;  // 파일에 기록된 정점의 UV 데이터의 인덱스를 담아둘 가변배열
    vector<int> mIndexNormals;  // 파일에 기록된 정점의 법선 데이터의 '인덱스를 담아둘 가변배열

    // Obj파일로부터 모델 데이터 로드하여 적재 
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
    }
};
