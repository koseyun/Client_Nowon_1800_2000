#pragma once
#include "SVector2D.h"
#include "CRef.h"

class CObjectAPI: public CRef
{
public:
	CObjectAPI();
	virtual ~CObjectAPI();

protected:
	// 위치 정보
	SVector2D mPosition;

};

/*
	OOP 프로그래밍의 4가지 특징

	추상화 abstraction : 코드의 추상화 + 데이터의 추상화 --> 데이터의 추상화
	은닉화 encapsulation : Data Hiding
	상속성 inheritance :  공통된 특성을 부모클래스에 두고 이를 이어받아 자식클래스를 작성하는것, 호율적인 재사용
	다형성 polymorphysm : 같은 메시지에 다른 반응
		override + virtual + 부모클래스 타입의 포인터
*/

