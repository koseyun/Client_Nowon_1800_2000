// GG_Matrix.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
using namespace std;

// 2행2열 행렬 구조체 정의
struct SMatrix2x2
{
    float m[2][2];
};

// 2행1열 열벡터 구조체 정의
struct SVector
{
    float v[2][1];
};

// 단위행렬로 설정하는 함수
void Identity(SMatrix2x2& mat)
{
    mat.m[0][0] = 1.0f; mat.m[0][0] = 0.0f;
    mat.m[1][0] = 0.0f; mat.m[1][1] = 1.0f;
}

void MatrixMultiply2x2(SMatrix2x2& matResult, SMatrix2x2& matA, SMatrix2x2& matB)
{
    for (int r = 0; r < 2; ++r)
    {
        for (int c = 0; c < 2; ++c)
        {
            matResult.m[r][c] = matA.m[r][0] * matB.m[0][c] +
                matA.m[r][1] * matB.m[1][c];
        }
    }
}

// 행렬식 값 구하기
float Determinent(SMatrix2x2& matA)
{
    // 행렬식 값을 구한다 ad - bc
    float tDeterminent = matA.m[0][0] * matA.m[1][1] - matA.m[0][1] * matA.m[1][0];

    return tDeterminent;
}

// 역행렬 구하기
void Inverse(SMatrix2x2& matResult, SMatrix2x2& matA)
{
    // 행렬식 값을 구한다
    float tDeterminent = matA.m[0][0] * matA.m[1][1] - matA.m[0][1] * matA.m[1][0];

    cout << "tDeterminent" << tDeterminent << endl;

    //if (tDeterminent - 0.0f < FLT_EPSILON)
    //if (tDeterminent == 0.0f)
    if (std::fabsf(tDeterminent) < FLT_EPSILON)
    {
        cout << "inverse is not." << endl;
        return;
    }

    // inverse determinent
    float idet = 1.0f / tDeterminent;

    // 전치하고 여인수행렬을 구하는 형태로 만듦
    matResult.m[0][0] = matA.m[1][1] * idet;
    matResult.m[0][1] = -1.0f * matA.m[0][1] * idet;
    matResult.m[1][0] = -1.0f * matA.m[1][0] * idet;
    matResult.m[1][1] = matA.m[0][0] * idet;
}

void Display(SMatrix2x2 matA)
{
    for (int r = 0; r < 2; ++r)
    {
        for (int c = 0; c < 2; ++c)
        {
            cout << matA.m[r][c] << "\t";
        }
        cout << endl;
    }
}

void MatrixMultiplyVector(SVector& tResult, SMatrix2x2& matA, SVector& tVector)
{
    tResult.v[0][0] = matA.m[0][0] * tVector.v[0][0] + matA.m[0][1] * tVector.v[1][0];
    tResult.v[1][0] = matA.m[1][0] * tVector.v[0][0] + matA.m[1][1] * tVector.v[1][0];
}

void DisplayVector(SVector& tVector)
{
    for (int r= 0; r < 2; ++r)
    {
        for (int c = 0; c < 1; ++c)
        {
            cout << tVector.v[r][c] << endl;
        }
    }
}

int main()
{
    // step0
    SMatrix2x2 tMatA =
    {
        1.0f, 2.0f,
        3.0f, 4.0f
    };

    float tDet = Determinent(tMatA);
    cout << "tDet: " << tDet << endl;

    SMatrix2x2 tMatB =
    {
        1.0f, 2.0f,
        -1.0f, 3.0f
    };

    SMatrix2x2 tMatResult =
    {
        0.0f, 0.0f,
        0.0f, 0.0f
    };

    Inverse(tMatResult, tMatB);

    Display(tMatResult);

    SMatrix2x2 tMatResult_0 =
    {
        0.0f, 0.0f,
        0.0f, 0.0f
    };

    cout << endl;

    MatrixMultiply2x2(tMatResult_0, tMatResult, tMatB);

    Display(tMatResult_0);

    // step1
    // 계토산

    SMatrix2x2 tRabbitCh =
    {
        1.0f, 1.0f,
        4.0f, 2.0f
    };

    SVector tApiVector =
    {
        15.0f,
        40.0f
    };

    // 결과벡터
    SVector tResultVector =
    {
        0.0f,
        0.0f
    };

    SMatrix2x2 tInverse =
    {
        0.0f, 0.0f,
        0.0f, 0.0f
    };

    // 역행렬을 구함
    Inverse(tInverse, tRabbitCh);
    // 행렬과 열벡터의 곱셈의 결과는 열벡터이다
    MatrixMultiplyVector(tResultVector, tInverse, tApiVector);

    DisplayVector(tResultVector);

    return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
