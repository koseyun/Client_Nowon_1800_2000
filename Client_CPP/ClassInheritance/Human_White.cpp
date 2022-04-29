#include <iostream>
#include "Human_White.h"

void Human_White::GoTravel()
{
	std::cout << "백인은 여행을 떠납니다" << std::endl;
}

void Human_White::Breath()
{
	age++;
	Grow();
}

void Human_White::Grow()
{
	mass += 2;
	height += 2;
}
