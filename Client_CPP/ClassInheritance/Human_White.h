#pragma once
#include "Human.h"
class Human_White :
    public Human
{
public:
    void GoTravel();

    // override
    // 부모의 멤버함수를 재정의 할 수 있는 기능
    void Breath();
    void Grow();
};

