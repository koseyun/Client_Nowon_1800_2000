#pragma once
#include <windows.h>
#include <unordered_map>
using namespace std;

class CAniSeq;
class CAPI_Engine;
class CObjectApPI;

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

	bool Create(CAPI_Engine* tpEngine)
	{
		mpEngine = tpEngine;

		return true;
	}
	void Destroy()
	{

	}

	// 현재 애니메이션 진행을 위한 데이터 갱신
	void UpdateAnimation(float t);
	// 현재 애니메이션의 결과 포즈를 렌더링
	void Render(CAPI_Engine* tpEngine, float tX, float tY);

	// 애니메이션 시퀀스를 등록하는 함수
	bool AddAniSeq(const string& tName, float tTimeInterval, int tTotalFramesCount, LPCWSTR tpFileName);
	
	void SetOwnerObject(CObjectAPI* tpObject)
	{
		mpObject = tpObject;
	}
	CObjectAPI* GetOwnerObject() const
	{
		return mpObject;
	}

public:
	// 여러 애니메이션 시퀀스의 집합, 키는 문자열타입, 값은 애니메이션 시퀀스의 주소값
	// 빠르게 임의의 애니메이션 시퀀스에 접근하기 위한 자료구조로 해시테이블을 선택했다
	unordered_map<string, CAniSeq*> mAniSeqs;

	string mId = "";					// 이 애니메이터의 식별자 키

	CAPI_Engine* mpEngine = nullptr;	// 엔진의 주소값(참조)
	
	CAniSeq* mpCurAniSeq = nullptr;		// 현재 애니메이션 시퀀스의 주소값(참조)
	string mStrKeyCurAniSeq;			// 현재 애니메이션 시퀀스의 식별자 키

	CObjectAPI* mpObject = nullptr;
};

