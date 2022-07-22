#pragma once

#include <vector>
#include <string>
using namespace std;

class CTexture;


//�ִϸ��̼� �÷��� �ɼ� 
enum ANI_PO
{
	LOOP = 0,		//�ݺ��ؼ� �÷��� 
	ONCE,			//�ѹ��� �÷���
};

//��������Ʈ �ɼ�
enum ANI_SO
{
	FRAME_FILE = 0,		//��������Ʈ �������� ���� ������ ����
	SHEET_FILE,			//��������Ʈ �����ӵ��� �ϳ��� ��������Ʈ ��Ʈ ���Ͽ� ���� 
};

class CAniSeq
{
public:
	CAniSeq(): 
		mId(""), mAniTime(0.0f), mTimeInterval(0.1f), mCurFrameIndex(0), mTotalFramesCount(0)
	{
		mTexs.clear();
	};
	CAniSeq(const CAniSeq& t)
	{
		*this = t;

		//�ؽ��Ĵ� �����ڿ��̴�.
		/*vector<CTexture*>::iterator tItor;
		for (tItor = mTexs.begin(); tItor != mTexs.end(); ++tItor)
		{
			
		}*/
	};
	~CAniSeq()
	{
	};


	void Update(float fElapsedTime);

	void SetSpriteFrameWH(int tRow = 1, int tCol = 1);
	


public:

	string mId = "";
	vector<CTexture*> mTexs;
	float mTimeInterval = 0.1f;
	int mTotalFramesCount = 0;

	int mCurFrameIndex = 0;
	float mAniTime = 0.0f;


	ANI_PO mPlayOption = ANI_PO::LOOP;

	//ryu_ani_spritesheet_i
	ANI_SO mSpriteOption = ANI_SO::FRAME_FILE;




	//ryu_ani_spritesheet_i
	int mSpriteWidth = 0;
	int mSpriteHeight = 0;

	int mRow = 0;	//��
	int mCol = 0;	//��
	int mFrameCOL = 0;		//��������Ʈ �������� �ʺ�
};

