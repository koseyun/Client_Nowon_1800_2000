#include <stdio.h>

void swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
}

int main(void) {

	// �����͸� ����ϴ� ����
	// swap ����
	int _a = 1, _b = 2;
	swap(&_a, &_b);
	printf("a = %d, b = %d \n", _a, _b); // ������ a = 2, b = 1;

}