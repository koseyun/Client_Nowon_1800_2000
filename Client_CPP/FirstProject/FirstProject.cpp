// 표준입출력 스트림 헤더파일.
// stdio.h 는 더이상 수동으로 추가해줄 필요 없이 자동으로 링크됨.
// c++ 에서는 헤더파일 확장자 없어도 됨
#include <iostream>

// namespace
// C++ 에서는 변수, 함수, 사용자정의 자료형 (클래스포함) 등을 서로 구분하기 위해서
// 이름으로 사용되는 다양한 내부 식별자를 가지고 있음.
// 하지만 프로그램이 복잡해지고 여러가지 라이브러리가 포함될수록 이 식별자 간에 충돌할 가능성이 높아짐
// 이러한 이름 충돌을 방지하기 위해서 namespace 를 사용함.
// 일반적으로 헤더파일에 선언해놓고 씀.
// 특정 namespace 에 접근하기 위해서는 범위지정 연산자 :: 를 사용해야함.
// namespace 를 해당 소스파일에서 전역으로 쓰고싶다면
// using namespace "네임스페이스 이름" 형태로 써주면 된다.
using namespace	std;

int main() {

	//printf("%s", "Hello World!");
	std::cout << "Hello World!" << endl;

	// auto 키워드
	// C에서는 지역변수 선언할때 사용하나 생력 가능하므로 쓸모가 없음
	// C++ 에서는 해당 키워드 재정의함.
	// auto 를 자료형처럼 사용하면서 변수 선언과 동시에 초기화 하면
	// 초기화 값의 형태로 자동으로 자료형을 선언해줌.
	auto age = 1;
	char name[20];

	cout << "안녕 몇살이니?" << endl;
	// scanf("%s", &age);
	cin >> age;
	cout << "안녕, 난" << age << "살 이야" << endl;

	cout << "이름은 뭔데?" << endl;
	cin >> name;
	cout << "내이름은" << name << "이야" << endl;

	
	double feel = "happy", "good", "not bad";
	cout << "How are you?" << endl;
	cin >> feel;
	cout << "I'm " << feel << "Thank you. And you?" << endl;

	
	return 0;
}