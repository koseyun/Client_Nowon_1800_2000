#include <iostream>
#include <stdlib.h>
struct MyStruct
{
	int a;
};
int main() {

	// c ���� �����Ҵ�
	struct MyStruct*a = (struct MyStruct*)malloc(sizeof(struct MyStruct));

	// c++ ���� �����Ҵ�
	// new Ű���带 ���
	// Ÿ��* �������̸� = new Ÿ��;
	MyStruct* mySturct = new MyStruct;
	delete mySturct;

	int* pi = new int;
	*pi = 100;
	std::cout << *pi << std::endl;
	delete pi;


	return 0;
}