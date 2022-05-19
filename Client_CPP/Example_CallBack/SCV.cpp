#include "SCV.h"
#include <iostream>
#include <chrono>
#include "CommandCenter.h"

/// <summary>
/// 소환시 CommandCenter 에 자기자신 등록 및 고유 ID 부여받음
/// </summary>
SCV::SCV()
	:state(STATE::IDLE)
	, timeMark(0.0)
{
	CommandCenter* commandCenter = CommandCenter::GetInstace();
	id = commandCenter->GetUnitSpawnCount();
	commandCenter->Register(*this);
}

/// <summary>
/// 채굴 시작하겠다는 콜백 호출 및
/// FSM 상태 채굴 시작으로 변경
/// </summary>
void SCV::DoMine()
{
	cb(id);
	state = STATE::STRAT_MININING;
}

/// <summary>
/// FSM
/// </summary>
void SCV::UpdataState()
{
	switch (state)
	{
		// 아무것도 안함
		//----------------------------------------------------------------------
		case SCV::IDLE:
			// 할게 없음
			break;

		// 채굴 시작
		//----------------------------------------------------------------------
		case SCV::STRAT_MININING:
			timeMark = clock();
			NextState();
			break;

		// 채굴 중...
		//----------------------------------------------------------------------
		case SCV::ON_MINING:
			// 채굴 완료 되었는지 체크
			if (clock() - timeMark > SCV_MINING_TIME) {
				NextState();
			}
			break;

		// 채굴 완료
		//----------------------------------------------------------------------
		case SCV::FINISH_MINING:
			CommandCenter::GetInstace()->IncreaseMinerals(SCV_MINING_AMOUNT);
			state = STATE::IDLE;
			break;
		default:
			break;
		}
}

/// <summary>
/// FSM 다음 상태로
/// </summary>
void SCV::NextState()
{
	state = (STATE)(state + 1);
}

/// <summary>
/// 콜백 등록
/// </summary>
void SCV::RegisterCallBack(REGISTER_CALLBACK callback)
{
	this->cb = callback;
}