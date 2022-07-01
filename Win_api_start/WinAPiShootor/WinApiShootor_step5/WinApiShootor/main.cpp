#include "framework.h"
#include "main.h"
#include "CAPI_Engine.h"
#include "CUnit.h"
#include "CTexture.h"
#include "CObjectAPI.h"
#include "APIMacro.h"
#include "CInputMgr.h"
#include "CActor.h"
#include "CBullet.h"
#include "CEnemy.h"

// API ref
#include <list>
#include <vector>
using namespace std;

#pragma comment(lib, "WinApiEngine.lib")

/*
    // winAPIShootor step5

    이 예시에서는 충돌 검사 알고리즘을 살펴보자
    두가지를 살펴보도록 한다

    원활한 테스트와 관찰을 위해 적 한마리만 남긴다

    1. 원vs원 충돌 알고리즘

        원을 이용한 충돌검사
        
        //ryu_collision_circle


    2. AABB 충돌 알고리즘 

        축정렬 경계상자(Axis Aligned Bounding Box)를 이용한 충돌검사

        //ryu_collision_aabb
*/

class CAPIEngine : public CAPI_Engine
{
public:
    CTexture* mpTexture = nullptr;
    // API bullets
    CTexture* mpTexBullet = nullptr;
    //
    CTexture* mpTexEnemy = nullptr;

    // 프리팹 : 원본객체
    CUnit* PFActor = nullptr;
    // API bullets
    CUnit* PFBullet = nullptr;
    // 
    CUnit* PFEnemy = nullptr;

    // 실제 게임월드에 배치될 주인공 객체
    CActor* mpActor = nullptr;

    // API bullets
    vector<CBullet*> mBullets;

    CEnemy* mpEnemy = nullptr;
    vector<CBullet*> mBulletEnemys;

    /*CEnemy* mpEnemyAimed = nullptr;
    vector<CBullet*> mBulletAimeds;
    
    CEnemy* mpEnemyCircled = nullptr;
    vector<CBullet*> mBulletC;*/
    
    list<CObjectAPI*> mObjectApi;

public:

    CAPIEngine()
    {
    }
    virtual ~CAPIEngine() // 가상소멸자
    {
    }

    // 복사생성과 복사대입을 금지하기 위해서 private로 접근제한하였다
private:
    CAPIEngine(const CAPIEngine& tEngine) {};
    CAPIEngine& operator=(const CAPIEngine& tEngine) {};

public:
    virtual void OnCreate() override
    {
        CAPI_Engine::OnCreate();
        
        CInputMgr::GetInst()->Create(mhWnd);
        CInputMgr::GetInst()->AddKey("OnMoveLeft", 'A');
        CInputMgr::GetInst()->AddKey("OnMoveRight", 'D');
        CInputMgr::GetInst()->AddKey("OnFire", VK_SPACE);
        CInputMgr::GetInst()->AddKey("OnTest", VK_LCONTROL, 'G');


        // todo
        WCHAR szTemp[256] = { 0 };
        wsprintf(szTemp, L"CAPIEngine::Create\n");
        OutputDebugString(szTemp);

        mpTexture = new CTexture();
        mpTexture->LoadTexture(this->hInst, this->mhDC, TEXT("resources/bongbong_0.bmp"));
        // 원본객체 : CActor 타입의 프리팹 생성
        PFActor = CreatePrefab<CActor>(mpTexture, 0.5f, 0.5f, SVector2D(400.0f, 500.0f));

        mpTexBullet = new CTexture();
        mpTexBullet->LoadTexture(this->hInst, this->mhDC, TEXT("resources/bongbullet.bmp"));
        // 원본객체 : CActor 타입의 프리팹 생성
        PFBullet = CreatePrefab<CBullet>(mpTexBullet, 0.5f, 0.5f, SVector2D(400.0f, 500.0f));

        mpTexEnemy = new CTexture();
        mpTexEnemy->LoadTexture(this->hInst, this->mhDC, TEXT("resources/bongenemy.bmp"));
        // 원본객체 : CEnemy 타입의 프리팹 생성
        PFEnemy = CreatePrefab<CEnemy>(mpTexEnemy, 0.5f, 0.5f, SVector2D(400.0f, 100.0f));


        // 주인공 게임 객체 하나를 복제로 생성
        mpActor = InstantObject<CActor>(PFActor);
        mpActor->AddRef();

        // API bullets
        CBullet* tpBullet = nullptr;
        for (int ti = 0; ti < 10; ++ti)
        {
            tpBullet = InstantObject<CBullet>(PFBullet);
            tpBullet->AddRef();

            // 탄환은 생성시 비활성으로
            tpBullet->SetIsActive(false);


            mBullets.push_back(tpBullet);
            tpBullet->AddRef();

            tpBullet->Release(); // 지역변수 tpBullet에 대한 Release
            tpBullet = nullptr;
        }

        mpEnemy = InstantObject<CEnemy>(PFEnemy);
        mpEnemy->AddRef();
        mpEnemy->SetVelocity(SVector2D(+1.0f, 0.0f) * 100.0f);        
        
        CBullet* tpBulletEnemy = nullptr;
        for (int ti = 0; ti < 10; ++ti)
        {
            tpBulletEnemy = InstantObject<CBullet>(PFBullet);
            tpBulletEnemy->AddRef();

            // 탄환은 생성시 비활성으로
            tpBulletEnemy->SetIsActive(false);


            mBulletEnemys.push_back(tpBulletEnemy);
            tpBulletEnemy->AddRef();

            tpBulletEnemy->Release(); // 지역변수 tpBulletEnemy에 대한 Release
            tpBulletEnemy = nullptr;
        }

        /*mpEnemyAimed = InstantObject<CEnemy>(PFEnemy);
        mpEnemyAimed->AddRef();
        //mpEnemyAimed->SetVelocity(SVector2D(+1.0f, 0.0f) * 50.0f);

        CBullet* tpBulletAimed = nullptr;
        for (int ti = 0; ti < 10; ++ti)
        {
            tpBulletAimed = InstantObject<CBullet>(PFBullet);
            tpBulletAimed->AddRef();

            // 탄환은 생성시 비활성으로
            tpBulletAimed->SetIsActive(false);

            mBulletAimeds.push_back(tpBulletAimed);
            tpBulletAimed->AddRef();

            tpBulletAimed->Release(); // 지역변수 tpBulletEnemy에 대한 Release
            tpBulletAimed = nullptr;
        }

        mpEnemyCircled = InstantObject<CEnemy>(PFEnemy);
        mpEnemyCircled->AddRef();
        mpEnemyCircled->SetVelocity(SVector2D(+1.0f, 0.0f) * 25.0f);

        CBullet* tpBulletC = nullptr;
        for (int ti = 0; ti < 8*10; ++ti)
        {
            tpBulletC = InstantObject<CBullet>(PFBullet);
            tpBulletC->AddRef();

            // 탄환은 생성시 비활성으로
            tpBulletC->SetIsActive(false);

            mBulletC.push_back(tpBulletC);
            tpBulletC->AddRef();

            tpBulletC->Release(); // 지역변수 tpBulletEnemy에 대한 Release
            tpBulletC = nullptr;
        }*/

    }

    virtual void OnDestroy() override
    {
        /*vector<CBullet*>::iterator tItorBulletC;
        for (tItorBulletC = mBulletC.begin(); tItorBulletC != mBulletC.end(); ++tItorBulletC)
        {
            DestroyObject(*tItorBulletC);
        }
        mBulletC.clear();

        DestroyObject(mpEnemyCircled);

        vector<CBullet*>::iterator tItorBulletAimed;
        for (tItorBulletAimed = mBulletAimeds.begin(); tItorBulletAimed != mBulletAimeds.end(); ++tItorBulletAimed)
        {
            DestroyObject(*tItorBulletAimed);
        }
        mBulletAimeds.clear();

        DestroyObject(mpEnemyAimed);*/

        // window API 에서 제공하는 타이머 해제함수
        //KillTimer(mhWnd, 0);

        vector<CBullet*>::iterator tItorBulletEnemy;
        for (tItorBulletEnemy = mBulletEnemys.begin(); tItorBulletEnemy != mBulletEnemys.end(); ++tItorBulletEnemy)
        {
            DestroyObject(*tItorBulletEnemy);
        }
        mBulletEnemys.clear();

        DestroyObject(mpEnemy);

        // API bullets
        vector<CBullet*>::iterator tItorBullet;
        for (tItorBullet = mBullets.begin(); tItorBullet != mBullets.end(); ++tItorBullet)
        {
                DestroyObject(*tItorBullet);
        }
        mBullets.clear();

        DestroyObject(mpActor);

        DestroyPrefab(PFEnemy);
        DestroyPrefab(PFBullet);
        DestroyPrefab(PFActor);
        
        if (nullptr != this->mpTexEnemy)
        {
            delete mpTexEnemy;
            mpTexEnemy = nullptr; 
        }

        if (nullptr != this->mpTexBullet)
        {
            delete mpTexBullet;
            mpTexBullet = nullptr;
        }

        if (nullptr != mpTexture)
        {
            delete mpTexture;
            mpTexture = nullptr;
        }

        CAPI_Engine::OnDestroy();
    }

    virtual void OnUpdate(float tDeltaTime) override
    {
        CAPI_Engine::OnUpdate(tDeltaTime);

        // collision

        // 원vs원 충돌 알고리즘 test
        // 적 vs 주인공 기체가 발사한 일반 탄환들 만 가정한다

        /*vector<CBullet*>::iterator tBItor;
        for (tBItor = mBullets.begin(); tBItor != mBullets.end(); tBItor++)
        {
            if ((*tBItor)->GetIsActive())
            {
                if (mpEnemy->GetIsActive())
                {
                    // 원을 이용한 충돌처리
                    
                    // 제곱근은 무한의 개념이 들어있어 연산이 많으므로 제거한다(양변을 거듭제곱)
                    float tAdd      = ((*tBItor)->GetRadius() + mpEnemy->GetRadius()) * ((*tBItor)->GetRadius() + mpEnemy->GetRadius());
                    float tDistance = ((*tBItor)->GetPosition().mX - mpEnemy->GetPosition().mX) * ((*tBItor)->GetPosition().mX - mpEnemy->GetPosition().mX)
                                    + ((*tBItor)->GetPosition().mY - mpEnemy->GetPosition().mY) * ((*tBItor)->GetPosition().mY - mpEnemy->GetPosition().mY);

                    // 길이의 개념이므로 0을 포함한 양수이다
                    // 그러므로 거듭제곱해도 그 대소관계가 유지된다
                    if (tDistance <= tAdd)
                    {
                        OutputDebugString(TEXT("Collision\n"));

                        break;
                    }
                }
            }
        }*/

        // AABB 충돌 알고리즘 test
        bool tIsCollision = false;
        vector<CBullet*>::iterator tBItor;
        for (tBItor = mBullets.begin(); tBItor != mBullets.end(); tBItor++)
        {
            if ((*tBItor)->GetIsActive())
            {
                if (mpEnemy->GetIsActive())
                {
                    tIsCollision = mpEnemy->Intersects(*(* tBItor));
                    if (tIsCollision)
                    {
                        OutputDebugString(TEXT("Collision\n"));
                        
                        mpEnemy->SetIsActive(false);
                        (*tBItor)->SetIsActive(false);

                        break;
                    }
                }
            }
        }


        // todo
        
        CInputMgr::GetInst()->Update();

        if (CInputMgr::GetInst()->KeyPress("OnMoveLeft"))
        {            
            mpActor->SetVelocity(SVector2D(-250.f, 0.0f));
            mpActor->Update(tDeltaTime);
        }

        if (CInputMgr::GetInst()->KeyPress("OnMoveRight"))
        {
            mpActor->SetVelocity(SVector2D(+250.f, 0.0f));
            mpActor->Update(tDeltaTime);
        }

        if (CInputMgr::GetInst()->KeyUp("OnFire"))
        {
            OutputDebugString(L"Skill_00\n");

            mpActor->DoFire(mBullets);
        }

        if (CInputMgr::GetInst()->KeyDown("OnTest"))
        {
            OutputDebugString(L"TEST.................\n");
        }

        // update
        vector<CBullet*>::iterator t;
        for (t = mBullets.begin(); t != mBullets.end(); ++t)
        {
            (*t)->Update(tDeltaTime);
        }

        // enemy do fire

        mpEnemy->Update(tDeltaTime);
        // 목표한 시간에 도달하면
        if (mpEnemy->mTimeTick >= 2.0f)
        {
            // todo
            mpEnemy->DoFire(mBulletEnemys);
            
            //mpEnemy->mTimeTick = 0.0f; // 오차가 있을 수 있다
            float tDiff = mpEnemy->mTimeTick - 2.0f;
            mpEnemy->mTimeTick = tDiff;
        }
        else
        {
            // delta time을 누적해간다
            mpEnemy->mTimeTick = mpEnemy->mTimeTick + tDeltaTime;
        }


        vector<CBullet*>::iterator tE;
        for (tE = mBulletEnemys.begin(); tE != mBulletEnemys.end(); ++tE)
        {
            (*tE)->Update(tDeltaTime);
        }

        /*mpEnemyAimed->Update(tDeltaTime);

        if (mpEnemyAimed->mTimeTick >= 4.0f)
        {
            // todo
            mpEnemyAimed->DoFireAimed(mBulletEnemys, mpActor);
                        
            float tDiff = mpEnemyAimed->mTimeTick - 4.0f;
            mpEnemyAimed->mTimeTick = tDiff;
        }
        else
        {
            mpEnemyAimed->mTimeTick = mpEnemyAimed->mTimeTick + tDeltaTime;
        }


        vector<CBullet*>::iterator tEC;
        for (tEC = mBulletC.begin(); tEC != mBulletC.end(); ++tEC)
        {
            (*tEC)->Update(tDeltaTime);
        }

        mpEnemyCircled->Update(tDeltaTime);

        if (mpEnemyCircled->mTimeTick >= 2.0f)
        {
            // todo
            mpEnemyCircled->DoFireCircled(mBulletC);

            float tDiff = mpEnemyCircled->mTimeTick - 2.0f;
            mpEnemyCircled->mTimeTick = tDiff;
        }
        else
        {
            mpEnemyCircled->mTimeTick = mpEnemyCircled->mTimeTick + tDeltaTime;
        }*/


        // render
        this->Clear(0.0f, 0.0f, 0.2f);

        mpActor->Render();

        vector<CBullet*>::iterator tItorBullet;
        for (tItorBullet = mBullets.begin(); tItorBullet != mBullets.end(); ++tItorBullet)
        {
            (*tItorBullet)->Render();
        }

        mpEnemy->Render();

        vector<CBullet*>::iterator tItorBulletE;
        for (tItorBulletE = mBulletEnemys.begin(); tItorBulletE != mBulletEnemys.end(); ++tItorBulletE)
        {
            (*tItorBulletE)->Render();
        }

        /*mpEnemyAimed->Render();

        vector<CBullet*>::iterator tItorEAimed;
        for (tItorEAimed = mBulletAimeds.begin(); tItorEAimed != mBulletAimeds.end(); ++tItorEAimed)
        {
            (*tItorEAimed)->Render();
        }

        mpEnemyCircled->Render();

        vector<CBullet*>::iterator tECItor;
        for (tECItor = mBulletC.begin(); tECItor != mBulletC.end(); ++tECItor)
        {
            (*tECItor)->Render();
        }*/

        this->Present();
        
    }
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

    //// 이런 경우를 허용하지 말자
    //CAPIEngine tB = tEngine; // 복사생성자
    //CAPIEngine tA;
    //tEngine = tA; // 복사대입연산자

    return (int)msg.wParam;
}

// CObgectTywcmailcom