#include <stdio.h>

// 공용체 union
// union 에서 가장 사이즈가 큰 멤버의 데이터 크기만큼 공간 할당
// 나머지 멤버들은 해당 공간을 공유함.

//typedef union _JobInfo {
//	char schoolName[20];
//	char companyName[20];
//} JobInfo;
//
//typedef struct _Person {
//	char name[20];
//	JobInfo jonInfo;
//} Person;



typedef struct _Person {
	char name[20];
	union _JobInfo {
		char schoolName[20];
		char companyName[20];
	} jobInfo;
} Person;

int main() {

	Person a = {
		{"Luke"},
		{"KoreaSchool"}
	};
	Person b = {
		{"Dina"},
		{"StrongCompany"}
	};
	
	strcpy(a.name, "Luke");
	strcpy(a.jobInfo.schoolName, "KoreaSchool");

	strcpy(b.name, "Dina");
	strcpy(b.jobInfo.companyName, "StrongCompany");

	printf("Luke's schoolName : %s\n", a.jobInfo.schoolName);
	printf("Luke's companyName : %s\n", a.jobInfo.companyName);
	printf("Dina's schoolName : %s\n", b.jobInfo.schoolName);
	printf("Dina's companyName : %s\n", b.jobInfo.companyName);


}