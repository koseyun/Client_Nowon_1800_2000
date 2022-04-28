#pragma once
#include <string>
#include "Creature.h"
#include "DynaminArraryTemplate.h"
using namespace std;

class Human :
    public Creature
{
public:
    DynamicArrary<string> clothes;

public:
    void WearCloth(string cloth);
    void PrintAllClothes();
};

