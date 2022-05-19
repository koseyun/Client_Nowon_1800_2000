#pragma once

#include <vector>
#include "SCV.h"

#define SCV_STANDARD_NUMBER 2

using namespace std;
class CommandCenter
{
#pragma region 싱글톤
private:
	static CommandCenter* _instance;

public:
	static CommandCenter* GetInstace();
#pragma endregion

private:

	int _minerals; // 현재 자원
	int _unitSpawnCount; // 소환한 유닛 수

public:
	
	vector<SCV> SCVs; // 소환한 SCV들

	static void SCVCallBack(int id); // SCV에게 명령 내릴때 호출할 콜백

	void UpdateAllSCVs(); // 모든 SCV 상태 갱신
	bool TrySpwanSCV(); // SCV 생성 시도 (미네랄 필요함)
	void SpawnSCV(); // SCV 생성
	void Register(SCV& scv); // SCV 등록
	int GetUnitSpawnCount(); // 소환한 유닛 갯수
	void IncreaseMinerals(int amount); // 자원 증가
};

