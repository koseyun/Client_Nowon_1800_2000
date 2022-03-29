#include <stdio.h>

void RefreshMaxAndMin(int* arr, int size, int** maxPtr, int** minPtr) {
	int* max, * min;
	max = min = arr;

	for (int i = 0; i < size; i++)
	{
		if (*max < arr[i])
			max = &arr[i];

		if (*min > arr[i])
			min = &arr[i];
	}

	*maxPtr = max;
	*minPtr = min;
}

int main(void) {
	
	int a = 3;
	int* p = &a;
	int** pp = &p;

	printf("%p\n", p);
	printf("%p\n", &p);
	printf("%p\n", pp);

	printf("%d\n", *p);
	printf("%d\n", **pp);

	printf("%p\n", &pp);

	int* maxPtr;
	int* minPtr;
	int arr[5] = {3,2,4,2,6};
	// 함수에서 실행할 내용 :
	// maxPtr 은 arr의 가장 큰값을 가리키고,
	// minPtr 은 arr의 가장 작은 값을 가리키도록
	int size = sizeof(arr) / sizeof(int);
	RefreshMaxAndMin(arr, size, &maxPtr, &minPtr);

	printf("최댓값 : %d , 최솟값 : %d\n", *maxPtr, *minPtr);


	return 0;
}