#include "Debuffer.h"
#include <iostream>

void Debuffer::DecreaseHP(Warrior& target)
{
	std::cout << "플레이어의 체력을" << _damage << "만큼 깎을거야" << std::endl;
	target.SetHP(target.GetHP() - _damage);
}

void Debuffer::DecreaseHP()
{
	//Warrior& warrior = *(Warrior::GetInstance());
	//warrior.SetHP(warrior.GetHP() - DAMAGE);
	DecreaseHP(*(Warrior::GetInstance()));
}
