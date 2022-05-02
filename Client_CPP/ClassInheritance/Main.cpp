#include <iostream>
#include <Windows.h>

#include "Creature.h"
#include "Dog.h"
#include "Human.h"
#include "Human_Yellow.h"
#include "Human_Black.h"
#include "Human_White.h"

using namespace std;
int main() {
	/*
	Creature* creature1 = new Creature();
	Dog* dog1 = new Dog();
	Human* human1 = new Human();
	human1->WearCloth("밀짚모자");
	human1->WearCloth("빨간재킷");
	human1->WearCloth("청반바지");
	human1->WearCloth("조리");

	human1->PrintAllClothes();

	Human_Yellow* human_yellow1 = new Human_Yellow();
	Human_Black* human_black1 = new Human_Black();
	Human_White* human_white1 = new Human_White();

	human_yellow1->GoToAcademy();
	human_black1->GoToGym();
	human_white1->GoTravel();*/

	// 부모-자식 간의 특징
	// 부모클래스 타입으로 자식객체를 인스턴스화 할 수 있다.
	// 요렇게 했을때는 부모클래스 타입에 있는 멤버들만 접근이 가능하다.
	Human* human_yellow2 = new Human_Yellow();

	Human* humans[99];
	
	for (int i = 0; i < 99; i += 3)
	{
		humans[i] = new Human_Yellow();
		humans[i + 1] = new Human_Black();
		humans[i + 2] = new Human_White();
	}

	// 순수 가상함수가 포함된 클래스는 인스턴스화가 불가능함.
	ITwoLeggedWalker* twoLeggedWalkers[99];
	for (int i = 0; i < 99; i += 3)
	{
		twoLeggedWalkers[i] = humans[i];
	}

	for (int i = 0; i < 99; i++)
	{
		twoLeggedWalkers[i]->TwoLeggedWalk();
	}
	
	int elapsedTime = 0;
	//while (true)
	//{
	//	for (int i = 0; i < 99; i++) {
	//		humans[i]->Breath();
	//		cout << i << " 의 나이 : " << humans[i]->age
	//			<< ", 키 :"   << humans[i]->height
	//			<< ", 질량 :" << humans[i]->mass << endl;
	//	}


	//	/*human_yellow1->Breath();
	//	cout << " 황인 나이 : " << human_yellow1->age
	//		<< ", 황인 키 :"    << human_yellow1->height
	//		<< ", 황인 질량 :"  << human_yellow1->mass << endl;

	//	human_black1->Breath();
	//	cout << " 흑인 나이 : " << human_black1->age
	//		<< ", 흑인 키 :"    << human_black1->height
	//		<< ", 흑인 질량 :"  << human_black1->mass << endl;

	//	human_white1->Breath();
	//	cout << " 백인 나이 : " << human_white1->age
	//		<< ", 백인 키 :"    << human_white1->height
	//		<< ", 백인 질량 :"  << human_white1->mass << endl;*/

	//	//// 크리처 숨쉬기
	//	//creature1->Breath();

	//	//cout << "크리처 나이 :" << creature1->age
	//	//	 << ", 크리처 높이 :" << creature1->height
	//	//	 << ", 크리처 질량 :" << creature1->mass << endl;

	//	//Sleep(1000);

	//	//// 개 숨쉬기
	//	//dog1->Breath();

	//	//cout << "개 나이 :" << dog1->age
	//	//	<< ", 개 높이 :" << dog1->height
	//	//	<< ", 개 질량 :" << dog1->mass << endl;

	//	//// 사람 숨쉬기
	//	//human1->Breath();

	//	//cout << "사람 나이 :" << human1->age
	//	//	<< ", 사람 높이 :" << human1->height
	//	//	<< ", 사람 질량 :" << human1->mass << endl;


	//	//// 3초에 한번씩 물기
	//	//if (elapsedTime > 2) {
	//	//	dog1->Bite(creature1);
	//	//	elapsedTime = 0;
	//	//}
	//	//else
	//	//	elapsedTime++;

	//	//Sleep(1000);
	//}

	/*delete creature1;
	delete dog1;
	delete human1;
	delete human_yellow1;
	delete human_black1;
	delete human_white1;*/
	
	// 가상클래스 비교

	// 되는 이유 : 가상클래스를 상속받고 부모의 멤버순수가상함수를 재정의 한 클래스를 인스턴스화 했음
	Human_Yellow* yelloMan = new Human_Yellow();
	yelloMan->Breath();

	// 안되는 이유 : 가상클래스를 상속받은 클래스를 인스턴스화 하려 했지만, 멤버순수가상함수를 재정의(override) 하지 않았음
	//Human* human = new Human();

	// 안되는 이유 : 가상클래스를 직접 인스턴스화 하려고 했음
	//Creature* creature = new Creature();

	return 0;
}