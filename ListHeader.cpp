#include "ListHeader.h"

void InitList(PLIST pList) {
	pList->iSize = 0;

	pList->pBegin = new NODE;
	pList->pEnd = new NODE;

	pList->pBegin->pNext = pList->pEnd;
	pList->pEnd->pPrev = pList->pBegin;

	pList->pEnd->pNext = NULL;
	pList->pBegin->pPrev = NULL;
}

void Destroy(PLIST pList)
{
	PNODE pNode = pList->pBegin;

	while (pNode != NULL) {
		PNODE pNext = pNode->pNext;
		delete pNode;
		pNode = pNext;
	}
	pList->iSize = 0;
	pList->pBegin = NULL;
	pList->pEnd = NULL;
}

void Push_Back(PLIST pList)
{
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

	pNode->tStudent = tStudent;

	//���ο� ���� End���� �� ����� ���̿�
	//�߰��Ǳ� ������ End����� �� ��� ������
	//�����´�.
	PNODE pPrev = pList->pEnd->pPrev;

	//������ ������带 ����
	//End�� Prev���̿� ����
	pPrev->pNext = pNode;
	pNode->pPrev = pPrev;
	pNode->pNext = pList->pEnd;
	pList->pEnd->pPrev = pNode;

	pList->iSize++;
}

void Push_Front(PLIST pList) {

}

void OutputStudent(const PSTUDENT pStudent) {
	cout << "�̸� : " << pStudent->strName << "\t�й� : " << pStudent->iNumber << endl;
	cout << "���� : " << pStudent->iKor << "\t���� : " << pStudent->iMath << endl;
	cout << "���� : " << pStudent->iEng << "\t���� : " << pStudent->iTotal << endl;
	cout << "��� : " << pStudent->fAvg << endl;
}

void Output(PLIST pList)
{
	int iMenu;
	while (true) {
		system("cls");
		cout << "1. ������ ���" << endl;
		cout << "2. ������ ���" << endl;
		cout << "�޴��� �����ϼ��� : ";
		iMenu = Inputint();

		if (iMenu > OT_NONE || iMenu <= OT_INVERSE)
			break;
	}

	PNODE pNode = NULL;

	switch (iMenu) {
	case OT_OUTPUT:
		//�߰��Ǵ� ���� begin�� next
		pNode = pList->pBegin->pNext;

		while (pNode != pList->pEnd) {
			OutputStudent(&pNode->tStudent);

			pNode = pNode->pNext;
		}
		break;
	case OT_INVERSE:
		//�������� end�� prev
		pNode = pList->pEnd->pPrev;
		while (pNode != pList->pBegin) {
			OutputStudent(&pNode->tStudent);

			pNode = pNode->pPrev;
		}
		break;
	}
	cout << "�л��� : " << pList->iSize << endl;
	system("pause");
}

void Search(PLIST pList)
{
	system("cls");
	cout << "Ž���� �̸��� �Է��ϼ��� :";
	char strName[NAME_SIZE] = {};
	InputString(strName, NAME_SIZE);

	PNODE pNode = pList->pBegin->pNext;

	while (pNode != pList->pEnd) {
		if (strcmp(pNode->tStudent.strName, strName) == 0) {
			OutputStudent(&pNode->tStudent);
			system("pause");
			return;
		}
		pNode = pNode->pNext;
	}
	cout << "�л��� ã�� �� �����ϴ�." << endl;
	system("pause");
}

void Delete(PLIST pList)
{
	system("cls");
	char strDeleteName[NAME_SIZE] = {};
	PNODE pNode = pList->pBegin->pNext;
	PNODE pPrev = NULL;

	cout << "������ �̸��� �Է��ϼ���. : ";
	InputString(strDeleteName, NAME_SIZE);

	while (pNode != pList->pEnd) {
		if (strcmp(pNode->tStudent.strName, strDeleteName) == 0) {
			pNode->pPrev->pNext = pNode->pNext;
			pNode->pNext->pPrev = pNode->pPrev;
			delete pNode;
			pList->iSize--;
			cout << strDeleteName << " �л��� �����Ͽ����ϴ�." << endl;
			system("pause");
			return;
		}
		pNode = pNode->pNext;
	}
	cout << "������ �л��� �����ϴ�." << endl;
	system("pause");
}

void SortedByNum(PLIST pList) {
	STUDENT tTempStudent;
	PNODE pNode_1 = pList->pBegin->pNext;

	while (pNode_1 != pList->pEnd->pPrev) {
		PNODE pNode_2 = pNode_1->pNext;
		while (pNode_2 != pList->pEnd) {
			if (pNode_1->tStudent.iNumber > pNode_2->tStudent.iNumber) {
				tTempStudent = pNode_1->tStudent;
				pNode_1->tStudent = pNode_2->tStudent;
				pNode_2->tStudent = tTempStudent;
			}
			pNode_2 = pNode_2->pNext;
		}
		pNode_1 = pNode_1->pNext;
	}
	cout << "�й������� ���ĿϷ�!!" << endl;
	system("pause");
}

void SortedByAvg(PLIST pList) {
	STUDENT tTempStudent;
	PNODE pNode_1 = pList->pBegin->pNext;

	while (pNode_1 != pList->pEnd) {
		PNODE pNode_2 = pNode_1->pNext;
		while (pNode_2 != pList->pEnd) {
			if (pNode_1->tStudent.fAvg > pNode_2->tStudent.fAvg) {
				tTempStudent = pNode_1->tStudent;
				pNode_1->tStudent = pNode_2->tStudent;
				pNode_2->tStudent = tTempStudent;
			}
			pNode_2 = pNode_2->pNext;
		}
		pNode_1 = pNode_1->pNext;
	}
	cout << "���������� ���ĿϷ�!!" << endl;
	system("pause");
}

void Sort(PLIST pList)
{
	int iMenu;
	while (true) {
		system("cls");
		cout << "1. �й���" << endl;
		cout << "2. ������" << endl;
		cout << "�޴��� �����ϼ���. : ";
		iMenu = Inputint();

		if (iMenu > ST_NONE || iMenu <= ST_AVG)
			break;
	}
	
	switch (iMenu) {
	case ST_NUM:
		SortedByNum(pList);
		break;
	case ST_AVG:
		SortedByAvg(pList);
		break;
	}
}


