#pragma once

#include <vector>
#include "SCV.h"

using namespace std;
class CommandCenter
{
public :
	int minerals;
	vector<SCV> SCVs;


	void UpdateAllSCVs();
	bool TrySpwanSCV();
	void SCVCallBack(int id);
	void Register(SCV& scv, REGISTER_CALLBACK cb);
};

