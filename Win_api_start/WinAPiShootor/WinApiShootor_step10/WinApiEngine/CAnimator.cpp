#include "CAnimator.h"
#include "CAniSeq.h"
#include "APIMacro.h"
#include "CAPI_Engine.h"
#include "CTexture.h"

CAnimator::CAnimator(): mId(""), mpEngine(nullptr), mpCurAniSeq(nullptr), mStrKeyCurAniSeq("")
{
	mAniSeqs.clear();
}
CAnimator::CAnimator(const CAnimator& t)
{
	//기본대입, shallow copy
	//*this = t;

	mId = t.mId;
	mpEngine = t.mpEngine;
	mpCurAniSeq = t.mpCurAniSeq;
	mStrKeyCurAniSeq = t.mStrKeyCurAniSeq;
	mpObject = t.mpObject;

	// 애니메이션 시퀀스는 게임오브젝트마다 있어야 하므로 다음과 같이
	// depp copy
	mAniSeqs.clear();
	unordered_map<string, CAniSeq*>::const_iterator tItor;
	for (tItor = t.mAniSeqs.begin(); tItor != t.mAniSeqs.end(); ++tItor)
	{
		CAniSeq* tpAniClip = new CAniSeq();

		*tpAniClip = *tItor->second;

		mAniSeqs.insert(make_pair(tpAniClip->mId, tpAniClip));
	}
}
CAnimator::~CAnimator()
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
	/*if (&t == this)
	{
		return;
	}*/

	//기본대입, shallow copy
	//*this = t;

	mId = t.mId;
	mpEngine = t.mpEngine;
	mpCurAniSeq = t.mpCurAniSeq;
	mStrKeyCurAniSeq = t.mStrKeyCurAniSeq;
	mpObject = t.mpObject;


	// 애니메이션 시퀀스는 게임오브젝트마다 있어야 하므로 다음과 같이
	// depp copy
	mAniSeqs.clear();
	unordered_map<string, CAniSeq*>::const_iterator tItor;
	for (tItor = t.mAniSeqs.begin(); tItor != t.mAniSeqs.end(); ++tItor)
	{
		CAniSeq* tpAniClip = new CAniSeq();

		*tpAniClip = *tItor->second;

		mAniSeqs.insert(make_pair(tpAniClip->mId, tpAniClip));
	}
}

void CAnimator::UpdateAnimation(float t)
{
	/*
	// test
	this->mStrKeyCurAniSeq = "ani_idle_actor";
	*/

	unordered_map<string, CAniSeq*>::iterator tItor = mAniSeqs.find(mStrKeyCurAniSeq);
	mpCurAniSeq = tItor->second;

	mpCurAniSeq->Update(t);
}

void CAnimator::Render(CAPI_Engine* tpEngine, float tX, float tY)
{
	int tIndex = mpCurAniSeq->mCurFrameIndex;
	CTexture* tpTex = mpCurAniSeq->mTexs[tIndex];
	if (tpTex)
	{
		tpEngine->DrawTexture(tX, tY, tpTex);
	}
}

bool CAnimator::AddAniSeq(const string& tName, float tTimeInterval, int tTotalFramesCount, LPCWSTR tpFileName)
{
	// 동적할당
	CAniSeq* tpClip = new CAniSeq();

	//api
	tpClip->mId = tName;

	// 데이터 설정
	tpClip->mTimeInterval = tTimeInterval;
	tpClip->mTotalFramesCount = tTotalFramesCount;

	// 프레임 개수만큼 만들어서 추가한다
	// 이름은 뒤에 번호를 붙여 만드는 것으로 규칙을 정하였다
	for (int ti = 0; ti < tTotalFramesCount; ++ti)
	{
		CTexture* tpTex = nullptr;
		tpTex = new CTexture();

		WCHAR szTemp[256] = { 0 };
		wsprintf(szTemp, L"%s_%d.bmp", tpFileName, ti);

		tpTex->LoadTexture(mpEngine->GetHInst(), mpEngine->GetHDC(), szTemp);
		tpClip->mTexs.push_back(tpTex);
	}

	// 해시테이블에 등록
	mAniSeqs.insert(make_pair(tName, tpClip));

	return true;
}
