// winAPITraning00.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

/*

    winAPIShootor step 13 ani sprite sheet



    i)잠깐 컬러키 설정을 하자

        컬러키는 일단 하얀색(255,255,255)로 하자
            전통적으로 많이 쓰이는 컬러키는 자홍색이다(255,0,255)


    //ryu_colorkey



    ii)스프라이트 시트를 고려한 기능도 추가하자

        explosionFull.bmp 리소스를 가정하여 작성한다
        2048*1024의 크기를 가진다
        4행 8열 의 스프라이트 프레임들 이 하나의 이미지 파일로 구성되어 있다.( 4*8 = 32 장의 프레임 )
        <-- 이러한 것을 스프라이트 시트 sprite sheet, 또는 atlas 라고 한다.

        스프라이트 시트를 구성하는 방법은 크게 두가지인데 
        여기서는 각각의 스프라이트 프레임 의 크기를 통일한 버전으로 가정한다


    


    //ryu_ani_spritesheet_i



*/

#include "framework.h"
#include "main.h"


#include "CAPIEngine.h"
#include "CUnit.h"
#include "CTexture.h"
#include "CObjectRyu.h"
#include "CInputMgr.h"
#include "ryumacro.h"
#include "CActor.h"
#include "CBullet.h"
#include "playmacro.h"
#include "CEnemy.h"
#include "CCollider.h"
#include "CCollisionMgr.h"

#include "CAnimator.h"
#include "CAniSeq.h"

#include <list>
using namespace std;

#pragma comment(lib, "winAPIEngine.lib")




class CRyuEngine : public CAPIEngine
{
private:
    CUnit* PFActor = nullptr;
    CUnit* PFBullet = nullptr;
    //프리팹
    CUnit* PFEnemy = nullptr;

    CTexture* mpTexture = nullptr;
    CTexture* mpTexBullet = nullptr;
    //필요한 이미지 자원
    CTexture* mpTexEnemy = nullptr;


    
    list<CObjectRyu*> mObjects;


    CActor* mpActor = nullptr;
    vector<CBullet*> mBullets;

    //적 기체 게임오브젝트
    CEnemy* mpEnemy = nullptr;
    vector<CBullet*> mBulletsEnemy;



    CEnemy* mpEnemy_0 = nullptr;
    vector<CBullet*> mBulletsEnemy_0;

    //ryu_circled
    CEnemy* mpEnemy_C = nullptr;
    vector<CBullet*> mBulletsEnemy_C;


    
public:
    CRyuEngine() {};
    virtual ~CRyuEngine() {};


    virtual void OnCreate() override
    {
        CAPIEngine::OnCreate();

        //키입력 등록
        //키 등록은 이렇게 한다
        CInputMgr::GetInstance()->AddKey("DoMoveLeft", 'A');
        CInputMgr::GetInstance()->AddKey("DoMoveRight", 'D');
        CInputMgr::GetInstance()->AddKey("DoFire", VK_SPACE);

        CInputMgr::GetInstance()->AddKey("DoTest", VK_LCONTROL, 'G');
        CInputMgr::GetInstance()->AddKey("DoTest_0", VK_LCONTROL, 'H');
        //CInputMgr::GetInstance()->AddKey("DoTest", VK_LCONTROL, 'G', 'H');

        //CCollisionMgr::GetInstance();


        
        mpTexture = new CTexture();
        mpTexture->LoadTexture(hInst, mhDC, TEXT("resources/bongbong_0.bmp"));

        mpTexBullet = new CTexture();
        mpTexBullet->LoadTexture(hInst, mhDC, TEXT("resources/bongbullet.bmp"));

            
        mpTexEnemy = new CTexture();
        //mpTexEnemy->LoadTexture(hInst, mhDC, TEXT("resources/bongenemy.bmp"));
        mpTexEnemy->LoadTexture(hInst, mhDC, TEXT("resources/paladin_idle_0.bmp"));






        PFActor = CreatePrefab<CActor>(mpTexture, 0.5f, 0.5f, SVector2D(400.0f, 500.0f));
           
        CAnimator* tpAnimActor = PFActor->CreateAnimation("AnimActor", this);
            tpAnimActor->SetOwnerObject(PFActor);
            tpAnimActor->AddAniSeq(L"resources/bongbong", "ani_idle_actor", 1.0f, 2);
            tpAnimActor->AddAniSeq(L"resources/bongbong_super","ani_super_actor", 1.0f, 2);
            PFActor->SetDefaultAniSeq("ani_idle_actor");

            

        PFBullet = CreatePrefab<CBullet>(mpTexBullet, 0.5f, 0.5f, SVector2D(400.0f, 500.0f));

            //test
            //ryu_ani_spritesheet_i
            CAnimator* tpAnimBullet = PFBullet->CreateAnimation("AnimBullet", this);
            tpAnimBullet->SetOwnerObject(PFBullet);
            tpAnimBullet->AddAniSeq(L"resources/explosionFull", "ani_idle_bullet", 0.01f, 4*8,ANI_PO::LOOP, ANI_SO::SHEET_FILE, 4,8);
            PFBullet->SetDefaultAniSeq("ani_idle_bullet");

        PFEnemy = CreatePrefab<CEnemy>(mpTexEnemy, 0.5f, 0.5f, SVector2D(400.0f, 100.0f));

            CAnimator* tpAnimEnemy = PFEnemy->CreateAnimation("AnimEnemy", this);
            tpAnimEnemy->SetOwnerObject(PFEnemy);
            tpAnimEnemy->AddAniSeq(L"resources/paladin_idle", "ani_idle_enemy", 0.2f, 7);
            //tpAnimEnemy->AddAniSeq(L"resources/paladin_attack", "ani_attack_enemy", 1.0f, 7,  ANI_PO::ONCE);
            tpAnimEnemy->AddAniSeq(L"resources/paladin_attack", "ani_attack_enemy", 0.08f, 7, ANI_PO::ONCE);
            PFEnemy->SetDefaultAniSeq("ani_idle_enemy");






        mpActor = InstantObject<CActor>(PFActor);
        mpActor->AddRef();
        //mpActor->PlayAni("ani_idle_actor");



        mObjects.push_back(mpActor);
        mpActor->AddRef();




        CBullet* tpBullet = nullptr;
        for (int ti = 0; ti < ACTOR_BULLET_MAX_COUNT; ++ti)
        {
            tpBullet = InstantObject<CBullet>(PFBullet);
            tpBullet->AddRef();


            //여기서는 인스턴스에 개별적으로 모두 태그를 붙임
            //프리팹에 붙여넣고 인스턴싱하면 모두 붙게 할 수도 있다.
            tpBullet->SetTag("tagActorBullet");



            //탄환은 일단 비활성화시키겠다.
            tpBullet->SetIsActive(false);

            mBullets.push_back(tpBullet);
            tpBullet->AddRef();

            mObjects.push_back(tpBullet);
            tpBullet->AddRef();

            tpBullet->Release();    //지역변수 tpBullet에 대한 Release
            tpBullet = nullptr;


            

        }


        mpEnemy = InstantObject<CEnemy>(PFEnemy);
        mpEnemy->AddRef();

        mpEnemy->SetVelocity(SVector2D(+1.0f, 0.0f) * 100.0f);
        //mpEnemy->PlayAni("ani_idle_enemy");






        CBullet* tpBulletEnemy = nullptr;
        for (int ti = 0; ti < ACTOR_BULLET_MAX_COUNT; ++ti)
        {
            tpBulletEnemy = InstantObject<CBullet>(PFBullet);
            tpBulletEnemy->AddRef();




            //탄환은 일단 비활성화시키겠다.
            tpBulletEnemy->SetIsActive(false);

            mBulletsEnemy.push_back(tpBulletEnemy);
            tpBulletEnemy->AddRef();

            mObjects.push_back(tpBulletEnemy);
            tpBulletEnemy->AddRef();

            tpBulletEnemy->Release();    //지역변수 tpBullet에 대한 Release
            tpBulletEnemy = nullptr;
        }


        //mpEnemy_0 = InstantObject<CEnemy>(PFEnemy);
        //mpEnemy_0->AddRef();
        //mpEnemy_0->SetPosition(SVector2D(200.0f, 100.0f));
        //mpEnemy_0->SetVelocity(SVector2D(+1.0f, 0.0f) * 100.0f);



        //CBullet* tpBulletEnemy_0 = nullptr;
        //for (int ti = 0; ti < ACTOR_BULLET_MAX_COUNT; ++ti)
        //{
        //    tpBulletEnemy_0 = InstantObject<CBullet>(PFBullet);
        //    tpBulletEnemy_0->AddRef();

        //    //탄환은 일단 비활성화시키겠다.
        //    tpBulletEnemy_0->SetIsActive(false);

        //    mBulletsEnemy_0.push_back(tpBulletEnemy_0);
        //    tpBulletEnemy_0->AddRef();

        //    mObjects.push_back(tpBulletEnemy_0);
        //    tpBulletEnemy_0->AddRef();

        //    tpBulletEnemy_0->Release();    //지역변수 tpBullet에 대한 Release
        //    tpBulletEnemy_0 = nullptr;
        //}




        ////ryu_circled
        //mpEnemy_C = InstantObject<CEnemy>(PFEnemy);
        //mpEnemy_C->AddRef();
        //mpEnemy_C->SetPosition(SVector2D(200.0f, 100.0f));
        //mpEnemy_C->SetVelocity(SVector2D(+1.0f, 0.0f) * 10.0f);



        //CBullet* tpBulletEnemy_C = nullptr;
        //for (int ti = 0; ti < 8*ACTOR_BULLET_MAX_COUNT; ++ti)
        //{
        //    tpBulletEnemy_C = InstantObject<CBullet>(PFBullet);
        //    tpBulletEnemy_C->AddRef();

        //    //탄환은 일단 비활성화시키겠다.
        //    tpBulletEnemy_C->SetIsActive(false);

        //    mBulletsEnemy_C.push_back(tpBulletEnemy_C);
        //    tpBulletEnemy_C->AddRef();

        //    mObjects.push_back(tpBulletEnemy_C);
        //    tpBulletEnemy_C->AddRef();

        //    tpBulletEnemy_C->Release();    //지역변수 tpBullet에 대한 Release
        //    tpBulletEnemy_C = nullptr;
        //}

    }
    virtual void OnDestroy() override
    {
        ////ryu_circled
        //vector<CBullet*>::iterator tItorBulletEnemy_C;
        //for (tItorBulletEnemy_C = mBulletsEnemy_C.begin(); tItorBulletEnemy_C != mBulletsEnemy_C.end(); ++tItorBulletEnemy_C)
        //{
        //    DestroyObject<CBullet>((*tItorBulletEnemy_C));
        //}
        //mBulletsEnemy_C.clear();

        //DestroyObject<CEnemy>(mpEnemy_C);






        //vector<CBullet*>::iterator tItorBulletEnemy_0;
        //for (tItorBulletEnemy_0 = mBulletsEnemy_0.begin(); tItorBulletEnemy_0 != mBulletsEnemy_0.end(); ++tItorBulletEnemy_0)
        //{
        //    DestroyObject<CBullet>((*tItorBulletEnemy_0));
        //}
        //mBulletsEnemy_0.clear();

        //DestroyObject<CEnemy>(mpEnemy_0);





        //KillTimer(mhWnd, 0);

        vector<CBullet*>::iterator tItorBulletEnemy;
        for (tItorBulletEnemy = mBulletsEnemy.begin(); tItorBulletEnemy != mBulletsEnemy.end(); ++tItorBulletEnemy)
        {
            DestroyObject((*tItorBulletEnemy));
        }
        mBulletsEnemy.clear();

        DestroyObject<CEnemy>(mpEnemy);








        vector<CBullet*>::iterator tItorBullet;
        for (tItorBullet = mBullets.begin(); tItorBullet != mBullets.end(); ++tItorBullet)
        {
            DestroyObject((*tItorBullet));
        }
        mBullets.clear();




        list<CObjectRyu*>::iterator tItor;
        for (tItor = mObjects.begin(); tItor != mObjects.end(); ++tItor)
        {
            if (nullptr != (*tItor))
            {
                (*tItor)->Release();

                (*tItor) = nullptr;
            }
        }
        mObjects.clear();



        DestroyObject<CActor>(mpActor);






        
        SAFE_DELETE(mpTexBullet);

        SAFE_DELETE(mpTexBullet);
        SAFE_DELETE(mpTexture);
        

        DestroyPrefab(PFEnemy);

        DestroyPrefab(PFBullet);
        DestroyPrefab(PFActor);



        //CCollisionMgr::GetInstance()->ReleaseInstance();



        CAPIEngine::OnDestroy();
    }
    virtual void OnUpdate(float tDeltaTime) override
    {
        CAPIEngine::OnUpdate(tDeltaTime);


        //input
        CInputMgr::GetInstance()->Update();

        if (CInputMgr::GetInstance()->KeyPress("DoMoveLeft"))
        {
            mpActor->SetVelocity(SVector2D(-1.0f * 200.0f, 0.0f));
            mpActor->Update(tDeltaTime);
        }

        if (CInputMgr::GetInstance()->KeyPress("DoMoveRight"))
        {
            mpActor->SetVelocity(SVector2D(+1.0f * 200.0f, 0.0f));
            mpActor->Update(tDeltaTime);
        }


        if (CInputMgr::GetInstance()->KeyUp("DoFire"))
        {
            mpActor->DoFire(mBullets);
        }


        //애니메이션 변경 테스트: 쌩 
        if (CInputMgr::GetInstance()->KeyUp("DoTest"))
        {
            mpActor->PlayAni("ani_super_actor");
        }

        if (CInputMgr::GetInstance()->KeyUp("DoTest_0"))
        {
            mpActor->PlayAni("ani_idle_actor");

        }


        //update
        vector<CBullet*>::iterator tItor;
        for (tItor = mBullets.begin(); tItor != mBullets.end(); ++tItor)
        {
            (*tItor)->Update(tDeltaTime);
        }



        vector<CBullet*>::iterator t;
        for (t = mBulletsEnemy.begin(); t != mBulletsEnemy.end(); ++t)
        {
            (*t)->Update(tDeltaTime);
        }

        mpEnemy->Update(tDeltaTime);


        //UpdateTimer
        // 프레임 시간간격을 누적하여 타이머를 구현한다.
        //일정시간 간격으로 적이 탄환을 발사한다.
        //if (mpEnemy->mTimeTick >= 0.5f)
        if (mpEnemy->mTimeTick >= 5.0f)
        {
            mpEnemy->DoFire(mBulletsEnemy);
            mpEnemy->PlayAni("ani_attack_enemy");





            mpEnemy->mTimeTick = 0.0f;
        }
        else
        {
            mpEnemy->mTimeTick = mpEnemy->mTimeTick + tDeltaTime;
        }





        //vector<CBullet*>::iterator te;
        //for (te = mBulletsEnemy_0.begin(); te != mBulletsEnemy_0.end(); ++te)
        //{
        //    (*te)->Update(tDeltaTime);
        //}

        //mpEnemy_0->Update(tDeltaTime);

        //if (mpEnemy_0->mTimeTick >= 1.0f)
        //{
        //    //mpEnemy_0->DoFire(mBulletsEnemy_0);
        //    mpEnemy_0->DoFireAimed(mBulletsEnemy_0, mpActor);

        //    mpEnemy_0->mTimeTick = 0.0f;
        //}
        //else
        //{
        //    mpEnemy_0->mTimeTick = mpEnemy_0->mTimeTick + tDeltaTime;
        //}





        ////ryu_circled
        //vector<CBullet*>::iterator tc;
        //for (tc = mBulletsEnemy_C.begin(); tc != mBulletsEnemy_C.end(); ++tc)
        //{
        //    (*tc)->Update(tDeltaTime);
        //}

        //mpEnemy_C->Update(tDeltaTime);

        //if (mpEnemy_C->mTimeTick >= 5.0f)
        //{
        //    mpEnemy_C->DoFireCircled(mBulletsEnemy_C);

        //    mpEnemy_C->mTimeTick = 0.0f;
        //}
        //else
        //{
        //    mpEnemy_C->mTimeTick = mpEnemy_C->mTimeTick + tDeltaTime;
        //}









        //Render
        this->Clear(0.1f, 0.1f, 0.3f);
        
        mpActor->Render();

        //vector<CBullet*>::iterator tItor;
        for (tItor = mBullets.begin(); tItor != mBullets.end(); ++tItor)
        {
            (*tItor)->Render();
        }

        
        
        mpEnemy->Render();


        vector<CBullet*>::iterator tItorEnemy;
        for (tItorEnemy = mBulletsEnemy.begin(); tItorEnemy != mBulletsEnemy.end(); ++tItorEnemy)
        {
            (*tItorEnemy)->Render();
        }




        //mpEnemy_0->Render();

        //vector<CBullet*>::iterator tItorEnemy_0;
        //for (tItorEnemy_0 = mBulletsEnemy_0.begin(); tItorEnemy_0 != mBulletsEnemy_0.end(); ++tItorEnemy_0)
        //{
        //    (*tItorEnemy_0)->Render();
        //}




        ////ryu_circled
        //mpEnemy_C->Render();

        //vector<CBullet*>::iterator tItorEnemy_C;
        //for (tItorEnemy_C = mBulletsEnemy_C.begin(); tItorEnemy_C != mBulletsEnemy_C.end(); ++tItorEnemy_C)
        //{
        //    (*tItorEnemy_C)->Render();
        //}


        this->Present();
    }

private:
    CRyuEngine(const CRyuEngine&) {};

    CRyuEngine& operator=(const CRyuEngine&) {};


};


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    CRyuEngine tEngine;
    tEngine.Create(hInstance, nCmdShow);


    MSG msg = { 0 };

    msg = tEngine.Run();

    return (int) msg.wParam;
}

