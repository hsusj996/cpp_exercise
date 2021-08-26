#include <iostream>
using namespace std;

enum MainMenu {
	MM_NONE,
	MM_INSERT,
	MM_DELETE,
	MM_SEARCH,
	MM_OUTPUT,
	MM_QUIT
};

#define NAME_SIZE 32
#define STUDENT_MAX 10

typedef struct _tagStudent {
	char strName[NAME_SIZE];
	int iNumber;
	int iKor;
	int iEng;
	int iMath;
	int iTotal;
	float fAvg;
}STUDENT, *PSTUDENT;

// 리스트 노드
typedef struct _tagNode {
	STUDENT tStudent;
	_tagNode* pNext;
}NODE, *PNODE;

// 리스트 구조체
typedef struct _tagList {
	PNODE pBegin;
	PNODE pEnd;
	int iSize;
}LIST, *PLIST;

//링크드리스트 시작 
void InitList(PLIST pList) {
	pList->pBegin = NULL;
	pList->pEnd = NULL;
	pList->iSize = 0;
}

int Inputint() {
	int iInput;
	cin >> iInput;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(1024, '\n');
		return INT_MAX;
	}
	return iInput;
}

void InputString(char* pString, int iSize) {
	cin.clear();
	cin.ignore(1024, '\n');
	cin.getline(pString, iSize - 1);
}

int MainMenu() {
	system("cls");

	cout << "1. 학생입력" << endl;
	cout << "2. 삭제" << endl;
	cout << "3. 탐색" << endl;
	cout << "4. 출력" << endl;
	cout << "5. 끝내기" << endl;
	cout << "메뉴를 선택하세요 : ";
	int iInput = Inputint();

	if (iInput <= MM_NONE || iInput > MM_QUIT)
		return MM_NONE;

	return iInput;
}

void Menu_Insert(PLIST pList) {
	system("cls");
	STUDENT tStudent = {};

	cout << "이름 : ";
	InputString(tStudent.strName, NAME_SIZE);
	cout << "학번 : ";
	tStudent.iNumber = Inputint();
	cout << "국어 : ";
	tStudent.iKor = Inputint();
	cout << "영어 : ";
	tStudent.iEng = Inputint();
	cout << "수학 : ";
	tStudent.iMath = Inputint();

	tStudent.iTotal = (tStudent.iKor + tStudent.iMath + tStudent.iEng);
	tStudent.fAvg = tStudent.iTotal / 3.0;

	PNODE pNode = new NODE;

	pNode->pNext = NULL;
	pNode->tStudent = tStudent;

	if (pList->pBegin == NULL) {
		pList->pBegin = pNode;
	}
	else {
		pList->pEnd->pNext = pNode;
	}
	pList->pEnd = pNode;

	++pList->iSize;
}

void ClearList(PLIST pList) {
	PNODE pNode = pList->pBegin;

	while (pNode != NULL) {
		PNODE pNext = pNode->pNext;
		delete pNode;
		pNode = pNext;
	}
	pList->pBegin = NULL;
	pList->pEnd = NULL;
	pList->iSize = 0;
}

void OutputStudent(const PSTUDENT pStudent) {
	cout << "이름 : " << pStudent->strName << "\t학번 : " << pStudent->iNumber << endl;
	cout << "국어 : " << pStudent->iKor << "\t수학 : " << pStudent->iMath << endl;
	cout << "영어 : " << pStudent->iEng << "\t총점 : " << pStudent->iTotal << endl;
	cout << "평균 : " << pStudent->fAvg << endl;
}

void Menu_Output(PLIST pList) {
	system("cls");

	PNODE pNode = pList->pBegin;

	while (pNode != NULL) {
		OutputStudent(&pNode->tStudent);
		pNode = pNode->pNext;
	}
	cout << "학생수 : " << pList->iSize << endl;

	system("pause");
}

void Menu_Delete(PLIST pList) {
	system("cls");
	char strDeleteName[NAME_SIZE] = {};
	PNODE pNode = pList->pBegin;
	PNODE pPrev = NULL;

	cout << "삭제할 이름을 입력하세요. : ";
	InputString(strDeleteName, NAME_SIZE);

	while (pNode != NULL) {
		if (strcmp(pNode->tStudent.strName, strDeleteName) == 0) {
			if (pNode == pList->pBegin) {
				pList->pBegin = pNode->pNext;
				delete pNode;
				break;
			}
			else if (pNode == pList->pEnd) {
				pList->pEnd = pPrev;
				delete pNode;
				break;
			}
			else {
				pPrev->pNext = pNode->pNext;
				delete pNode;
				break;
			}
		}
		pPrev = pNode;
		pNode = pNode->pNext;
	}
	if (pNode == NULL) {
		cout << "삭제할 이름이 없습니다." << endl;
	}
	else {
		pList->iSize--;
	}
	system("pause");
}

void Menu_Search(PLIST pList) {
	system("cls");
	char strSearchName[NAME_SIZE] = {};
	PNODE pNode = pList->pBegin;

	cout << "이름을 입력하세요. : ";
	InputString(strSearchName, NAME_SIZE);

	while (pNode != NULL) {
		if (strcmp(pNode->tStudent.strName, strSearchName) == 0) {
			OutputStudent(&pNode->tStudent);
			break;
		}
		pNode = pNode->pNext;
	}
	if (pNode == NULL) {
		cout << "찾는 학생이 없습니다." << endl;
	}
	system("pause");
}

int main() {
	cout << "학생정보 관리 프로그램입니다. 1.0 k.s.j" << endl;
	system("pause");

	LIST tStudentList;

	//리스트 초기설정
	InitList(&tStudentList);

	while (true) {
		//메인메뉴 진입
		int iMenu = MainMenu();
		
		if (iMenu == MM_QUIT)
			break;

		switch (iMenu) {
		case MM_INSERT:
			Menu_Insert(&tStudentList);
			break;
		case MM_DELETE:
			Menu_Delete(&tStudentList);
			break;
		case MM_SEARCH:
			Menu_Search(&tStudentList);
			break;
		case MM_OUTPUT:
			Menu_Output(&tStudentList);
			break;
		}
	}

	return 0;
}