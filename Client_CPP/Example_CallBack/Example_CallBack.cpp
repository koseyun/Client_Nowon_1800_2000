#include <iostream>
#include "SCV.h"
#include "CommandCenter.h"
#include <Windows.h>

int main() {

	CommandCenter* commandCenter = CommandCenter::GetInstace();

	// 기본으로 주어지는 SCV
	for (int i = 0; i < SCV_STANDARD_NUMBER; i++)
		commandCenter->SpawnSCV();

	float scv_timer = SCV_SPAWN_TIME;
	float delta_time = 16.6666667; // 60fps 기준 프레임당 걸리는 시간
	while (true)
	{
		if (scv_timer <= 0)
		{
			if (commandCenter->TrySpwanSCV())
			{
				scv_timer = SCV_SPAWN_TIME;
			}
		}

		commandCenter->UpdateAllSCVs();

		Sleep(delta_time);
		scv_timer -= delta_time;
	}



	return 0;
}