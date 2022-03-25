#pragma warning(disable : 4996)
#include <stdio.h>
#include "basicOperations.h"
//"sum" 입력시 "sum" 함수 호출
//"sub" 입력시 "sub" 함수 호출
//"div" 입력시 "div" 함수 호출
//"mul" 입력시 "mul" 함수 호출
//"mod" 입력시 "mod" 함수 호출
//
//모든 함수는 실행시마다
//1. 연산 결과 콘솔창에 출력
//2. 전역변수 OperationCount 하나씩 증가시키고 출력
//-------------------------------------------------
//+
//재귀함수를 사용해서 팩토리얼 함수 구현
//n!= 1 * 2 * 3 * ... *n
//n! = n * (n-1) * (n-2) * ... * 1
int OperationCount;
int main() {
	int op[4];
	int a, b;

	printf("5 factorial %d\n", factotial(5));
	
	while (1)
	{
		int isOperated = 1;
		printf("명령을 입력하세요 (sum, sub, mul, div, mod) : ");
		scanf("%s", op);
		printf("연산에 사용할 숫자를 두개 입력하세요");
		scanf("%d %d", &a, &b);

		if (!strcmp("sum", op)) printf("%d\n", sum(a, b));
		else if (!strcmp("sub", op)) printf("%d\n", sub(a, b));
		else if (!strcmp("mul", op)) printf("%d\n", mul(a, b));
		else if (!strcmp("div", op)) printf("%d\n", div(a, b));
		else if (!strcmp("mod", op)) printf("%d\n", mod(a, b));
		else {
			printf("입력이 이상합니다");
			isOperated = 0;
		}
		OperationCount += isOperated;
		printf("operation count : %d\n", OperationCount);
	}


}

