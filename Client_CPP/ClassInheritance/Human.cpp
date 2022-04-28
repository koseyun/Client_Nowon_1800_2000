#include <iostream>
#include "Human.h"

void Human::WearCloth(string cloth)
{
	clothes.Add(cloth);
}

void Human::PrintAllClothes()
{
	std::cout << "내가 입고 있는 옷들이야 :";
	for (int i = 0; i < clothes.Length(); i++)
	{
		std::cout << clothes[i] << ", ";
	}
	std::cout << std::endl;
}
