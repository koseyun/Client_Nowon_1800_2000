#pragma warning (disable : 4996)
#include <stdio.h>

// FSM ( Finite State Machine )
// 유한 상태 머신
enum JumpState {
	Idle,
	PrepareToJump,
	InFlight,
	Falling,
	OnGround,
};

// enum : 열거형, 사용자정의 자료형을 정의하기위한 키워드
enum PlayerState {
	Idle,
	Walk,
	Run,
	Attack,
	Jump,
	Hurt,
};

// playerState
// 설명
// 플레이어 상태
// 0 = 아무것도 하지않는 상태
// 1 = 걷기
// 2 = 달리기
// 3 = 공격하기
// 4 = 점프하기
// 5 = 피격당하기

int main() {

	enum PlayerState playerState;
	playerState = Idle;

	while (1)
	{
		scanf("%d", &playerState);
		switch (playerState)
		{
		case Idle:
			printf("아무것도 하지않는 상태");
			break;
		case Walk:
			printf("걷기");
			break;
		case Run:
			printf("달리기");
			break;
		case Attack:
			printf("공격하기");
			break;
		case Jump:
			printf("점프하기");
			break;
		case Hurt:
			printf("피격당하기");
			break;
		default:
			printf("무슨 동작인지 모르겠어요 ㅠㅠ");
			break;
		}
	}



}