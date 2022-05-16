#include <stdio.h>

// While : 특정 조건에 따라 내용을 반복 제어
// 형태 : while(조건) { 조건이 참일때 반복할 내용 }


// do while : 내용을 일단 한번 실행하고 특정 조건에 따라 내용을 반복제어
// 형대 : do { 조건이 참일때 반복할 내용 } while(조건)

int main(void) {

	// 조건이 항상 참인 반복문을 무한 루프라고 함
	while (0)
	{
		printf("ahahahahahah11111");
		continue; // 분기문, 가장 가까운 반복문을 찾아서 해당 반복문의 조건 비교줄로 돌아감
		printf("ahahahahahah22222");
	}
	printf("while statement is over\n");
	
	int count = 0;
	while (count < 5)
	{
		printf("while count : %d\n", count);
		count++;
	}
	printf("while statement is over\n");

	// do while
	do
	{
		printf("do while test");
	} while (0);



	return 0;
}