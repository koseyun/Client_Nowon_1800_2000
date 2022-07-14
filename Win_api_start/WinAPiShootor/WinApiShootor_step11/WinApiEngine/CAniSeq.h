#pragma once
#include <vector>
#include <string>
using namespace std;

class CTexture;

// �ִϸ��̼� �÷��� �ɼ�
enum ANI_PO
{
    LOOP = 0,   // �ݺ��ؼ� �÷���
    ONCE,       // �ѹ��� �÷���
};

class CAniSeq
{
public:
    CAniSeq() : mId(""), mAniTime(0.0f), mTimeInterval(0.1f), mCurFrameIndex(0), mTotalFramesCount(0)
    {
        mTexs.clear();
    };
    CAniSeq(const CAniSeq& t)
    {
        *this = t;

        // �ؽ��Ĵ� �����ڿ��̹Ƿ� deep copy �� �ʿ䰡 ����
        /*
            vector<CTexture*>::iterator tItor;
            for(tItor = mTexs.begin(); tItor != mTexs.end(); ++tItor)
            {

            }
        */
    };
    ~CAniSeq()
    {
        mTexs.clear();
    };

    void Update(float tDeltaTime);

public:
    string mId = "";            // �ִϸ��̼� �������� �ĺ��� Ű

    vector<CTexture*> mTexs;    // �ִϸ��̼� �������� ������ �������� �����ϴ� �̹��� ����

    float mTimeInterval = 0.1f; // �ִϸ��̼� �������� �����Ӱ� �ð�
    int mTotalFramesCount = 0;  // �ִϸ��̼� �������� �� ������ ����

    int mCurFrameIndex = 0;     // ���� �߿� ���� ������ ��ȣ

    float mAniTime = 0.0f;      // �ִϸ��̼� ���� ƽ�ð�

    ANI_PO mPlayOption = ANI_PO::LOOP; // �⺻���� �ݺ��ؼ� �÷���
};

