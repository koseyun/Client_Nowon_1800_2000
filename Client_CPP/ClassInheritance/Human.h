#pragma once
#include <string>
#include "Creature.h"
#include "DynaminArraryTemplate.h"
#include "ITwoLeggedWalker.h"
#include "IFourLeggedWalker.h"

using namespace std;

class Human :
    public Creature, public ITwoLeggedWalker, public IFourLeggedWalker
{
public:
    DynamicArrary<string> clothes;

public:
    void WearCloth(string cloth);
    void PrintAllClothes();
    void TwoLeggedWalk();
    void FourLeggedWalk();
};

