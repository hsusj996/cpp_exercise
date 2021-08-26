#include <iostream>
//사용자 정의 헤더파일은 ""안에 적어준다.
#include "ListHeader.h" 
using namespace std;
/*
메인메뉴에 정렬기능 추가
학번, 평균 기준으로 오름차순 기능
*/


enum MainMenu {
	MM_NONE,
	MM_INSERT,
	MM_DELETE,
	MM_SEARCH,
	MM_OUTPUT,
	MM_SORT,
	MM_QUIT
};

#define NAME_SIZE 32

int MainMenu() {
	system("cls");

	cout << "1. 학생입력" << endl;
	cout << "2. 삭제" << endl;
	cout << "3. 탐색" << endl;
	cout << "4. 출력" << endl;
	cout << "5. 정렬" << endl;
	cout << "6. 끝내기" << endl;
	cout << "메뉴를 선택하세요 : ";
	int iInput = Inputint();

	if (iInput <= MM_NONE || iInput > MM_QUIT)
		return MM_NONE;

	return iInput;
}

int main() {
	LIST tList;

	InitList(&tList);

	while (true) {
		//메인메뉴 진입
		int iMenu = MainMenu();

		if (iMenu == MM_QUIT)
			break;

		switch (iMenu) {
		case MM_INSERT:
			Push_Back(&tList);
			break;
		case MM_DELETE:
			Delete(&tList);
			break;
		case MM_SEARCH:
			Search(&tList);
			break;
		case MM_OUTPUT:
			Output(&tList);
			break;
		case MM_SORT:
			Sort(&tList);
			break;
		}
	}

	Destroy(&tList);

	return 0;
}

//더블링크드리스트는 정보를 begin과 end사이 노드에 담고
// 모든 노드는 전노드와 후노드와 링크된다.
//따라서 보다 사용자가 원하는대로 정방향 혹은 역방향으로
//탐색이 가능하다.