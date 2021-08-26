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

	pNode->tStudent = tStudent;

	//새로운 노드는 End노드와 전 노드의 사이에
	//추가되기 때문에 End노드의 전 노드 정보를
	//가져온다.
	PNODE pPrev = pList->pEnd->pPrev;

	//새노드와 기존노드를 연결
	//End와 Prev사이에 연결
	pPrev->pNext = pNode;
	pNode->pPrev = pPrev;
	pNode->pNext = pList->pEnd;
	pList->pEnd->pPrev = pNode;

	pList->iSize++;
}

void Push_Front(PLIST pList) {

}

void OutputStudent(const PSTUDENT pStudent) {
	cout << "이름 : " << pStudent->strName << "\t학번 : " << pStudent->iNumber << endl;
	cout << "국어 : " << pStudent->iKor << "\t수학 : " << pStudent->iMath << endl;
	cout << "영어 : " << pStudent->iEng << "\t총점 : " << pStudent->iTotal << endl;
	cout << "평균 : " << pStudent->fAvg << endl;
}

void Output(PLIST pList)
{
	int iMenu;
	while (true) {
		system("cls");
		cout << "1. 정방향 출력" << endl;
		cout << "2. 역방향 출력" << endl;
		cout << "메뉴를 선택하세요 : ";
		iMenu = Inputint();

		if (iMenu > OT_NONE || iMenu <= OT_INVERSE)
			break;
	}

	PNODE pNode = NULL;

	switch (iMenu) {
	case OT_OUTPUT:
		//추가되는 노드는 begin의 next
		pNode = pList->pBegin->pNext;

		while (pNode != pList->pEnd) {
			OutputStudent(&pNode->tStudent);

			pNode = pNode->pNext;
		}
		break;
	case OT_INVERSE:
		//역방향은 end의 prev
		pNode = pList->pEnd->pPrev;
		while (pNode != pList->pBegin) {
			OutputStudent(&pNode->tStudent);

			pNode = pNode->pPrev;
		}
		break;
	}
	cout << "학생수 : " << pList->iSize << endl;
	system("pause");
}

void Search(PLIST pList)
{
	system("cls");
	cout << "탐색할 이름을 입력하세요 :";
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
	cout << "학생을 찾을 수 없습니다." << endl;
	system("pause");
}

void Delete(PLIST pList)
{
	system("cls");
	char strDeleteName[NAME_SIZE] = {};
	PNODE pNode = pList->pBegin->pNext;
	PNODE pPrev = NULL;

	cout << "삭제할 이름을 입력하세요. : ";
	InputString(strDeleteName, NAME_SIZE);

	while (pNode != pList->pEnd) {
		if (strcmp(pNode->tStudent.strName, strDeleteName) == 0) {
			pNode->pPrev->pNext = pNode->pNext;
			pNode->pNext->pPrev = pNode->pPrev;
			delete pNode;
			pList->iSize--;
			cout << strDeleteName << " 학생을 삭제하였습니다." << endl;
			system("pause");
			return;
		}
		pNode = pNode->pNext;
	}
	cout << "삭제할 학생이 없습니다." << endl;
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
	cout << "학번순으로 정렬완료!!" << endl;
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
	cout << "성적순으로 정렬완료!!" << endl;
	system("pause");
}

void Sort(PLIST pList)
{
	int iMenu;
	while (true) {
		system("cls");
		cout << "1. 학번순" << endl;
		cout << "2. 성적순" << endl;
		cout << "메뉴를 선택하세요. : ";
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


