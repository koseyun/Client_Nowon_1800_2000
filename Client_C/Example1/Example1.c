#pragma warning(disable : 4996)
#include <stdio.h>
#include "basicOperations.h"
//"sum" �Է½� "sum" �Լ� ȣ��
//"sub" �Է½� "sub" �Լ� ȣ��
//"div" �Է½� "div" �Լ� ȣ��
//"mul" �Է½� "mul" �Լ� ȣ��
//"mod" �Է½� "mod" �Լ� ȣ��
//
//��� �Լ��� ����ø���
//1. ���� ��� �ܼ�â�� ���
//2. �������� OperationCount �ϳ��� ������Ű�� ���
//-------------------------------------------------
//+
//����Լ��� ����ؼ� ���丮�� �Լ� ����
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
		printf("����� �Է��ϼ��� (sum, sub, mul, div, mod) : ");
		scanf("%s", op);
		printf("���꿡 ����� ���ڸ� �ΰ� �Է��ϼ���");
		scanf("%d %d", &a, &b);

		if (!strcmp("sum", op)) printf("%d\n", sum(a, b));
		else if (!strcmp("sub", op)) printf("%d\n", sub(a, b));
		else if (!strcmp("mul", op)) printf("%d\n", mul(a, b));
		else if (!strcmp("div", op)) printf("%d\n", div(a, b));
		else if (!strcmp("mod", op)) printf("%d\n", mod(a, b));
		else {
			printf("�Է��� �̻��մϴ�");
			isOperated = 0;
		}
		OperationCount += isOperated;
		printf("operation count : %d\n", OperationCount);
	}


}

