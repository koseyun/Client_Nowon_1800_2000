#pragma warning(disable : 4996)

#include <stdio.h>

int GetFactorial(int n);

double sum(int a, int b), sub(int a, int b), div(int a, int b), mul(int a, int b);

int main() {
	// �Լ� �������� ����
	// ��ȯ�� (*�Լ������ͺ����̸�)(�Ķ����1�ڷ��� (�Ķ����1) ...)
	int(*pf)(int);
	pf = GetFactorial;

	printf("%d\n", GetFactorial(5));
	printf("%d\n", pf(5));
	pf(5);

	// ����
	double (*pOP)(double, double) = NULL;
	char op[20]; // ��ɾ� �Է��� ���� ���ڿ�
	printf("���� ��ɾ �Է��ϼ��� (sum, sub, div, mul):");
	scanf("%s", op);

	if (!strcmp(op, "sum")) pOP = sum;
	else if (!strcmp(op, "sub")) pOP = sub;
	else if (!strcmp(op, "div")) pOP = div;
	else if (!strcmp(op, "mul")) pOP = mul;

	if (pOP != NULL);
		printf("3 �� 7�� ���� ����� : %lf\n", pOP(3, 7));


	/*
	double sum(int a, int b);
	double sub(int a, int b);
	double div(int a, int b);
	double mul(int a, int b);


	pOP = sum;
	pOP = sub;
	pOP = div;
	pOP = mul;
	
	int a = 0;
	int b = 0;

	if (sum(a, b))
	{
		scanf("%s\n", pOP);
	}
	else if (sub(a, b))
	{
		scanf("%s\n", pOP);
	}
	else if (div(a, b))
	{
		scanf("%s\n", pOP);
	}
	else if (mul(a, b))
	{
		scanf("%s\n", pOP);
	}*/
}

int GetFactorial(int n) {
	int fact = 1;
	int i;
	for (int i = 1; i <= n; i++)
	{
		fact *= i;
		fact = fact * i;
	}
	return fact;
}

double sum(double a, double b)
{
	return a + b;
}

double sub(double a, double b)
{
	return a - b;
}

double mul(double a, double b)
{
	return a * b;
}

double div(double a, double b)
{
	return a / b;
}