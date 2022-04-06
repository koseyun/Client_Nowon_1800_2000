#include <stdio.h>
#include "OperationFunctions.h"
#include "SubFunction.h"

// static (정적) 키워드
// 메모리 동적 할당을 불가능하게 하는 키워드
// 인스턴스화가 불가능하게 하는 키워드

// 정적 전역 변수
// 다른 소스파일에서 참조할 수 없는 전역변수
//static int opCount;
int opCount;

int main() {
	printf("%d\n", sum_int(1, 2));
	printf("%d\n", sum_int(1, 2));
	printf("%d\n", sum_int(1, 2));
	printf("%d\n", sum_int(1, 2));
	printf("%d", opCount);
	return 0;
}