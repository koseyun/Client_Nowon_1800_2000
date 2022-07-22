#pragma once
#include <windows.h>
#include "CAniSeq.h"
#include <unordered_map>
using namespace std;

class CAniSeq;
class CAPI_Engine;
class CObjectAPI;

class CAnimator
{
public:
	CAnimator();
	CAnimator(const CAnimator& t);
	~CAnimator();

	void operator=(const CAnimator& t);

	void SetId(string tId)
	{
		mId = tId;
	}

	bool Create(CAPI_Engine* tpEngine);
	void Destroy();
	
	void UpdateAnimation(float t);
	void Render(CAPI_Engine* tpEngine, float tX, float tY);

	// api_ani_spritesheet_i
	bool AddAniSeq(LPCWSTR tpFileName, const string& tName,
		float tTimeInterval, int tTotalFramesCount, ANI_PO tPlayOption = ANI_PO::LOOP, ANI_SO tSpriteOption = ANI_SO::FRAME_FILE, int tRow = 1, int tCol = 1);

	void SetCurAniClip(const string& tStrCurAniClip);
	void ChangeAniClip(const string& tStrClip);

	void SetDefaultAniSeq(const string& tStrDefaultAniSeq);
	void PlayAni(const string& tStrAniSeq);

	void LateUpdate();

	void SetOwnerObject(CObjectAPI* tpObject)
	{
		mpObject = tpObject;
	}
	CObjectAPI* GetOwnerObject() const
	{
		return mpObject;
	}

//protected:	
public:
	//여러 애니메이션클립의 집합
	unordered_map<string, CAniSeq*> mAniSeqs;

	string mId = "";
	CAPI_Engine* mpEngine = nullptr;

	CAniSeq* mpCurAniSeq = nullptr;
	string mStrKeyCurAniSeq;

	// api_ani_spritesheet_i
	CObjectAPI* mpObject = nullptr;
	//CUnit* mpObject = nullptr;

	string mStrKeyPrevAniSeq = "";
};
