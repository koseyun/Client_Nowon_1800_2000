#include <stdio.h>
// ����ü
// ���� �������� ����� ���� �� �ִ� ����� ���� �ڷ���

// ����:
//struct ����ü�ڷ����̸� {
//
//	// ��� ����
//};

// ����ü�� �� ����

/*int a = 1, b = 5;
int* ap = &a;
int* bp = &b;

ap = bp;
*ap = 3;
*bp = 8;*/

struct Coord {
	int x;
	int y;
};

struct Student {
	
	char name[20]; // 20byte
	double average; // 8byte
	int Korean, english, math; // 12byte
};

int main() {

	struct Coord coord1;

	// . ������ (���������)
	coord1.x = 4;
	coord1.y = 8;

	struct Coord coord2;
	coord2 = coord1;

	coord2.x = 1;
	coord2.y = 2;
	printf("��ǥ1 : (%d, %d)\n", coord1.x, coord1.y);
	printf("��ǥ2 : (%d, %d)\n", coord2.x, coord2.y);


	// ����ü�� �޸� �Ҵ�
	printf("Coord Size : %d\n", sizeof(struct Coord));

	printf("Student Size : %d\n", sizeof(struct Student));

	struct Student studentA;
	struct Student* student_P;



}