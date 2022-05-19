#pragma once
#define SCV_COST 50
#define SCV_SPAWN_TIME 4000
#define SCV_MINING_TIME 2000
#define SCV_MINING_AMOUNT 8


typedef void(*REGISTER_CALLBACK)(int);

class SCV
{
public:
	// FSM (Finite State Machine , 유한 상태 머신)
	enum STATE
	{
		IDLE,
		STRAT_MININING,
		ON_MINING,
		FINISH_MINING,
	};
	STATE state;
	double timeMark; // 채굴 시작시 시간 체크용
	int id; // 고유 번호
	REGISTER_CALLBACK cb; // 채굴 명령 받았을 때 호출할 콜백

	SCV();
	void DoMine(); // 채굴 시작
	void UpdataState(); // FSM 동작
	void NextState(); // FSM 그다음 스텝으로
	void RegisterCallBack(REGISTER_CALLBACK callback);
};

