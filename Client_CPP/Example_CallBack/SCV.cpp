#include "SCV.h"
#include <iostream>
#include <chrono>



SCV::SCV()
	:state(STATE::IDLE)
	, timeMark(0.0)
{

}

void SCV::DoMine()
{
	state = STATE::STRAT_MININING;
}

void SCV::UpdataState()
{
	switch (state)
	{
	case SCV::IDLE:
		// 할게 없음
		break;
	case SCV::STRAT_MININING:
		timeMark = clock();
		NextState();
		break;
	case SCV::ON_MINING:
		// 채굴 완료 되었는지 체크
		if (clock() - timeMark > SCV_MININGTIME) {
			NextState();
		}
		break;
	case SCV::FINISH_MINING:
		// todo -> 커맨드센터 총 미네랄 량 증가
		DoMine();
		break;
	default:
		break;
	}
}

void SCV::NextState()
{
	state = (STATE)(state + 1);
}

void SCV::RegisterCallBack(REGISTER_CALLBACK callback)
{
	this->cb = callback;
}

void SCV::SayImReady(int id)
{
	std::cout << "SCV" << id << "준비완료" << std::endl;
}
