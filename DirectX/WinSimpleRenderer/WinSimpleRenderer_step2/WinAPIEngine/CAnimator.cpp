#include "CAnimator.h"
//#include "CAniSeq.h"
#include "APIMacro.h"
#include "CAPI_Engine.h"
#include "CTexture.h"
#include "CResourcesMgr.h"

CAnimator::CAnimator()
{
	mAniSeqs.clear();
}
CAnimator::CAnimator(const CAnimator& t)
{
	mId = t.mId;
	mpEngine = t.mpEngine;
	mStrKeyCurAniSeq = t.mStrKeyCurAniSeq;

	mAniSeqs.clear();
	unordered_map<string, CAniSeq*>::const_iterator tItor;
	for (tItor = t.mAniSeqs.begin(); tItor != t.mAniSeqs.end(); ++tItor)
	{
		CAniSeq* tpAniClip = new CAniSeq();

		*tpAniClip = *tItor->second;
		//tpAniClip->mId = tItor->first;

		mAniSeqs.insert(make_pair(tpAniClip->mId, tpAniClip));
	}

	mStrKeyPrevAniSeq = t.mStrKeyPrevAniSeq;
}
CAnimator::~CAnimator()
{
	
}

bool CAnimator::Create(CAPI_Engine* tpEngine)
{
	mpEngine = tpEngine;

	return true;
}
void CAnimator::Destroy()
{	
	unordered_map<string, CAniSeq*>::iterator tItor;
	for (tItor = mAniSeqs.begin(); tItor != mAniSeqs.end(); ++tItor)
	{
		SAFE_DELETE(tItor->second);
	}

	mAniSeqs.clear();
}

void CAnimator::operator=(const CAnimator& t)
{
	//*this = t;

	mId					= t.mId;
	mpEngine			= t.mpEngine;
	mStrKeyCurAniSeq	= t.mStrKeyCurAniSeq;

	mStrKeyPrevAniSeq = t.mStrKeyPrevAniSeq;

	mAniSeqs.clear();
	unordered_map<string, CAniSeq*>::const_iterator tItor;
	for (tItor = t.mAniSeqs.begin(); tItor != t.mAniSeqs.end(); ++tItor)
	{
		CAniSeq* tpAniClip = new CAniSeq();

		*tpAniClip = *tItor->second;
		//tpAniClip->mId = tItor->first;


		mAniSeqs.insert(make_pair(tpAniClip->mId, tpAniClip));
	}
}

void CAnimator::UpdateAnimation(float t)
{
	unordered_map<string, CAniSeq*>::iterator tItor = mAniSeqs.find(mStrKeyCurAniSeq);
	mpCurAniSeq = tItor->second;

	if (mpCurAniSeq)
	{
		mpCurAniSeq->Update(t);
	}
	else
	{
		OutputDebugString(L"mpCurAniSeq is nullptr.");
	}
}
void CAnimator::LateUpdate()
{
	switch (mpCurAniSeq->mPlayOption)
	{
	case ANI_PO::LOOP:
	{

	}
	break;
	case ANI_PO::ONCE:
	{
		if (mpCurAniSeq->mCurFrameIndex == mpCurAniSeq->mTotalFramesCount - 1)
		{
			if (mpCurAniSeq->mAniTime >= mpCurAniSeq->mTimeInterval)
			{
				mStrKeyCurAniSeq = mStrKeyPrevAniSeq;


				mpCurAniSeq->mCurFrameIndex = 0;
				mpCurAniSeq->mAniTime = 0.0f;
			}

		}
	}
	break;

	}
}

void CAnimator::Render(CAPI_Engine* tpEngine, float tX, float tY)
{
	if (!mpCurAniSeq)
	{
		return;
	}

	if (ANI_SO::FRAME_FILE == mpCurAniSeq->mSpriteOption)
	{
		int tIndex = mpCurAniSeq->mCurFrameIndex;
		CTexture* tpTex = mpCurAniSeq->mTexs[tIndex];
		if (tpTex)
		{
			tpEngine->DrawTexture(tX, tY, tpTex);
		}

		LateUpdate();
	}
	else if (ANI_SO::SHEET_FILE == mpCurAniSeq->mSpriteOption)
	{
		int tIndex = mpCurAniSeq->mCurFrameIndex;
		CTexture* tpTex = mpCurAniSeq->mTexs[0];
		if (tpTex)
		{
			//tpEngine->DrawTexture(tX, tY, tpTex);

			tpEngine->DrawTexturePartial(tX, tY, tpTex, mpCurAniSeq->mRow, mpCurAniSeq->mCol, tIndex);
		}

		LateUpdate();
	}

	/*int tIndex = mpCurAniSeq->mCurFrameIndex;
	CTexture* tpTex = mpCurAniSeq->mTexs[tIndex];
	if (tpTex)
	{
		tpEngine->DrawTexture(tX, tY, tpTex);
	}

	LateUpdate();*/
}

// api_ani_spritesheet_1
// tpFileName : ù��° �����ӿ� �ش��ϴ� ��������Ʈ �̹��� ���� �̸�
// tName : Ŭ���� �̸�
// tTimerInterval : �ִϸ��̼� ������ ������ �ð�����
// tTotalFramesCount : �� ������ ����
// tPlayOption : �������� �ѹ��� �÷�������
bool CAnimator::AddAniSeq(const string& tStrKey,
	float tTimeInterval, int tTotalFramesCount, ANI_PO tPlayOption, ANI_SO tSpriteOption, int tRow, int tCol)
{
	CAniSeq* tpSeq			= new CAniSeq();

	tpSeq->mId				= tStrKey;

	tpSeq->mTimeInterval		= tTimeInterval;
	tpSeq->mTotalFramesCount	= tTotalFramesCount;

	tpSeq->mPlayOption = tPlayOption;
	tpSeq->mSpriteOption = tSpriteOption;

	tpSeq->mRow = tRow;
	tpSeq->mCol = tCol;
	
	if (ANI_SO::FRAME_FILE == tSpriteOption)
	{
		//������ ������ŭ ���� �߰��Ѵ�
		//�̸��� �ڿ� ��ȣ�� �ٿ� ����� ������ ��Ģ�� ���Ͽ���.
		for (int ti = 0; ti < tTotalFramesCount; ++ti)
		{
			/*CTexture* tpTex = nullptr;
			tpTex = new CTexture();
			WCHAR szTemp[256] = { 0 };
			wsprintf(szTemp, L"%s_%d.bmp", tpFileName, ti);
			tpTex->LoadTexture(mpEngine->GetHInst(), mpEngine->GetHDC(), szTemp);*/

			char szTemp[256] = { 0 };
			sprintf_s(szTemp, "%s_%d", tStrKey.c_str(), ti);

			string tString = szTemp;

			tpSeq->mTexs.push_back(FIND_TEX(tString));
		}
		tpSeq->SetSpriteFrameWH();
	}
	else if (ANI_SO::SHEET_FILE == tSpriteOption)
	{
		//������ ������ŭ �ִϸ��̼� �������� ����� �߰��Ѵ�
		//�ٸ� �̹��� �����ʹ� '�ϳ�'�̴�

		//��� �� ������ ����Ͽ� 
		//������ ��������Ʈ �������� �ʺ�� ���̸� �����Ѵ�

		/*CTexture* tpTex = nullptr;
		tpTex = new CTexture();
		WCHAR szTemp[256] = { 0 };
		wsprintf(szTemp, L"%s.bmp", tpFileName);
		tpTex->LoadTexture(mpEngine->GetHInst(), mpEngine->GetHDC(), szTemp);*/

		tpSeq->mTexs.push_back(FIND_TEX(tStrKey));

		tpSeq->SetSpriteFrameWH(tRow, tCol);
	}

	mAniSeqs.insert(make_pair(tStrKey, tpSeq));

	return true;
}

void CAnimator::SetCurAniClip(const string& tStrCurAniClip)
{
	ChangeAniClip(tStrCurAniClip);
}

void CAnimator::ChangeAniClip(const string& tStrClip)
{
	if (mStrKeyCurAniSeq == tStrClip)
	{
		return;
	}

	mStrKeyCurAniSeq = tStrClip;

	if (mpCurAniSeq)
	{
		mpCurAniSeq->mTimeInterval = 0.0f;
		mpCurAniSeq->mTotalFramesCount = 0;
	}

	/*mpCurAniClip = FindAniClip(tStrClip);

	if( mpCurAniClip)*/
}

void CAnimator::SetDefaultAniSeq(const string& tStrDefaultAniSeq)
{
	mStrKeyPrevAniSeq = tStrDefaultAniSeq;
	mStrKeyCurAniSeq = tStrDefaultAniSeq;

	if (nullptr != mpCurAniSeq)
	{
		mpCurAniSeq->mCurFrameIndex = 0;
		mpCurAniSeq->mAniTime = 0.0f;
	}
}
void CAnimator::PlayAni(const string& tStrAniSeq)
{
	//���� �÷��� ���� �ִϸ��̼� ������ Ű�� �����ص�
	mStrKeyPrevAniSeq = mStrKeyCurAniSeq;

	//���� �÷����� �ִϸ��̼� ������ ������ ����
	mStrKeyCurAniSeq = tStrAniSeq;

	if (nullptr != mpCurAniSeq)
	{
		mpCurAniSeq->mCurFrameIndex = 0;
		mpCurAniSeq->mAniTime = 0.0f;
	}
}
