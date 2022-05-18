#pragma once
#define SCV_COST 50
#define SCV_MININGTIME 2.0

typedef void(*REGISTER_CALLBACK)(int);

class SCV
{
public:
	enum STATE
	{
		IDLE,
		STRAT_MININING,
		ON_MINING,
		FINISH_MINING,
	};
	STATE state;
	double timeMark;
	int id;
	REGISTER_CALLBACK cb;

	SCV();
	void DoMine();
	void UpdataState();
	void NextState();
	void RegisterCallBack(REGISTER_CALLBACK callback);
	void SayImReady(int id);
};

