// 1. 포인터 주소란?
// 주소를 값으로 가지는 변수이다
// 
// 2. 다음 코드에서 tpPtr의 타입은 무엇인가?
// auto tpPtr = new int();
// 타입예약어 / 변수의 선언

// 3. 다음 코드를 살펴보고 물음에 답하라
/*int main() {
  
int* tpA = new int();

//return 0;
delete tpA;
}*/
// 1)이 프로그램의 문제점은 무엇인가? 
// 메모리 누수가 일어난다
// 2)이 프로그램은 변수가 얼마의 메모리를 사용하고 있는가? (32비트 컴퓨터로 가정하자)
// 4byte + 4byte = 8byte
// 3)변수는 어떤 종류의 메모리에 있는가?
// 코드 - 데이터 - 힙 - 스택 -

// 5. 다음은 팩토리얼의 정의이다 재귀호출을 이용한 함수를 정의하라
// 

/*int DoFactorial(int tN)
{
	//base case
	if (0 == tN)
	{
		return 1;
	}
	//recursive case
	else
	{
		return tN * DoFactorial(tN - 1);
	}
}*/

//int tA = 3;
//int tB = 2;


//swap routine

//int tTemp = 0;
//int tTemp = tA;
//int tA = tB;
//int tB = tTemp;

/*void DoSwap(int& tA, int& tB)
{
	int tTemp = 0;
	int tTemp = tA;
	int tA = tB;
	int tB = tTemp;
}*/

// 7. 클래스의 private, protected, public에 대해 설명하라
// 접근제한자
// public
// 어디서나 접근가능하다
// private
// 해당 클래스 내에서만 접근가능하다
// protected
// 상속 계통 구조 안에서만 접근가능하다

// 8. 다음 이진트리를 중위순회 해보라(사진참고)
// 배열 : 동일한 타입의 원소들의 (물리적으로) 연속적인 메모리 블럭이다
// 링크드리스트 : 노드가 데이터와 링크를 가지고 각각의 링크에 의해 한줄로(선형으로) 연결된 자료구조
// 트리 : 1:N의 비선형 자료구조, 계층형 자료구조
// 
// 이진탐색트리 :
// 1) 이진트리여야 한다
// 2) 중복된 값이 없어야 한다
// 3) 왼쪽 서브트리의 값은 루트보다 작고, 오른쪽 서브트리의 값은 루트보다 크다
// 4) 서브트리도 이진탐색트리여야 한다

// 9. 선택정렬의 정렬 메커니즘을 다음 항목들로 설명해라
// 
// 가) 핵심키워드
// 기준위치, 선택(selection)
// 
// 나) 동작기전 : 오름차순 정렬 가정
//	  기준위치에 있는 원소와 그 이후의 원소들의 값을 비교하여 최솟값을 찾는다. 이것을 선택이라고 한다
//	  기준위치에 있는 원소와 선택된 원소의 값을 교환한다
//	  기준위치를 하나 증가시킨다
//	  위의 과정을 계속 반복한다
//	  정렬된 값들은 앞에서부터 채워진다
// 
// 다) 시간복잡도 : O(n^2)
// 
// 라) 공간복잡도 : n

// 3개월

// 빅오표기법: 알고리즘의 성능측정의 도구, 최악의 경우의 수행속도를 표기하는 방법이다
