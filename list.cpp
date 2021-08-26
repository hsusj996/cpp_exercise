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

// ����Ʈ ���
typedef struct _tagNode {
	STUDENT tStudent;
	_tagNode* pNext;
}NODE, *PNODE;

// ����Ʈ ����ü
typedef struct _tagList {
	PNODE pBegin;
	PNODE pEnd;
	int iSize;
}LIST, *PLIST;

//��ũ�帮��Ʈ ���� 
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

	cout << "1. �л��Է�" << endl;
	cout << "2. ����" << endl;
	cout << "3. Ž��" << endl;
	cout << "4. ���" << endl;
	cout << "5. ������" << endl;
	cout << "�޴��� �����ϼ��� : ";
	int iInput = Inputint();

	if (iInput <= MM_NONE || iInput > MM_QUIT)
		return MM_NONE;

	return iInput;
}

void Menu_Insert(PLIST pList) {
	system("cls");
	STUDENT tStudent = {};

	cout << "�̸� : ";
	InputString(tStudent.strName, NAME_SIZE);
	cout << "�й� : ";
	tStudent.iNumber = Inputint();
	cout << "���� : ";
	tStudent.iKor = Inputint();
	cout << "���� : ";
	tStudent.iEng = Inputint();
	cout << "���� : ";
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
	cout << "�̸� : " << pStudent->strName << "\t�й� : " << pStudent->iNumber << endl;
	cout << "���� : " << pStudent->iKor << "\t���� : " << pStudent->iMath << endl;
	cout << "���� : " << pStudent->iEng << "\t���� : " << pStudent->iTotal << endl;
	cout << "��� : " << pStudent->fAvg << endl;
}

void Menu_Output(PLIST pList) {
	system("cls");

	PNODE pNode = pList->pBegin;

	while (pNode != NULL) {
		OutputStudent(&pNode->tStudent);
		pNode = pNode->pNext;
	}
	cout << "�л��� : " << pList->iSize << endl;

	system("pause");
}

void Menu_Delete(PLIST pList) {
	system("cls");
	char strDeleteName[NAME_SIZE] = {};
	PNODE pNode = pList->pBegin;
	PNODE pPrev = NULL;

	cout << "������ �̸��� �Է��ϼ���. : ";
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
		cout << "������ �̸��� �����ϴ�." << endl;
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

	cout << "�̸��� �Է��ϼ���. : ";
	InputString(strSearchName, NAME_SIZE);

	while (pNode != NULL) {
		if (strcmp(pNode->tStudent.strName, strSearchName) == 0) {
			OutputStudent(&pNode->tStudent);
			break;
		}
		pNode = pNode->pNext;
	}
	if (pNode == NULL) {
		cout << "ã�� �л��� �����ϴ�." << endl;
	}
	system("pause");
}

int main() {
	cout << "�л����� ���� ���α׷��Դϴ�. 1.0 k.s.j" << endl;
	system("pause");

	LIST tStudentList;

	//����Ʈ �ʱ⼳��
	InitList(&tStudentList);

	while (true) {
		//���θ޴� ����
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