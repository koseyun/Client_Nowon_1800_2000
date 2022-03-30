#include <stdio.h>

void swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
}

int main(void) {

	// 포인터를 사용하는 이유
	// swap 예시
	int _a = 1, _b = 2;
	swap(&_a, &_b);
	printf("a = %d, b = %d \n", _a, _b); // 예상결과 a = 2, b = 1;

}