#pragma once
#include "SVector2D.h"
#include "CRef.h"

class CObjectAPI: public CRef
{
public:
	CObjectAPI();
	virtual ~CObjectAPI();

public:
	// 위치 정보
	SVector2D mPosition;

	//// 참조 카운팅 변수
	//int mRef = 0;

	//void AddRef()
	//{
	//	// 참조카운트를 하나씩 증가한다
	//	++mRef;
	//}

	//int Release()
	//{
	//	// 참조를 하나씩 줄여준다
	//	--mRef;

	//	// 최종적으로 참조카운트가 0이 되면 메모리를 해제하고 참조카운트 0을 리턴한다
	//	if (0 == mRef)
	//	{
	//		delete this;
	//		return 0;
	//	}

	//	return mRef;
	//}

};

