#include <iostream>
using namespace std;
#define NAME_SIZE 32
#define STUDENT_MAX 3
typedef struct _tagStudent
{
	char strName[NAME_SIZE];
	int iNumber;
	int iKor;
	int iEng;
	int iMath;
	int iTotal;
	int iAvg;
}STUDENT, *PSTUDENT;

int main() {
	//STUDENT tStudent[STUDENT_MAX] = {};

	//for (int i = 0; i < STUDENT_MAX; i++) {
	//	cout << "�̸� : ";
	//	cin >>tStudent[i].strName;

	//	tStudent[i].iNumber = i + 1;

	//	cout << "���� : ";
	//	cin >> tStudent[i].iKor;
	//	cout << "���� : ";
	//	cin >> tStudent[i].iMath;
	//	cout << "���� : ";
	//	cin >> tStudent[i].iEng;
	//	tStudent[i].iTotal = tStudent[i].iKor + tStudent[i].iMath
	//		+ tStudent[i].iEng;
	//	tStudent[i].iAvg = tStudent[i].iTotal / 3.f;
	//}

	//int iStudentCount = STUDENT_MAX;

	//FILE* pFile = NULL;

	//fopen_s(&pFile, "Student.std", "wb");

	//if (pFile) {
	//	fwrite(&iStudentCount, 4, 1, pFile);

	//	for (int i = 0; i < iStudentCount; i++) {
	//		fwrite(&tStudent[i], sizeof(STUDENT), 1, pFile);
	//	}

	//	fclose(pFile);
	//}

	STUDENT tStudent[STUDENT_MAX] = {};
	int iStudentCount = 0;
	FILE* pFile = NULL;

	fopen_s(&pFile, "Student.std", "rb");

	if (pFile) {
		fread(&iStudentCount, 4, 1, pFile);

		for (int i = 0; i < iStudentCount; i++) {
			fread(&tStudent[i], sizeof(STUDENT), 1, pFile);
		}

		fclose(pFile);
	}
	for (int i = 0; i < iStudentCount; i++) {
		cout << "�̸� : " << tStudent[i].strName << endl;
		cout << "���� : " << tStudent[i].iKor << endl;
		cout << "���� : " << tStudent[i].iMath << endl;
		cout << "���� : " << tStudent[i].iEng << endl;
		cout << "���� : " << tStudent[i].iTotal << endl;
		cout << "��� : " << tStudent[i].iAvg << endl;
	}


	return 0;
}