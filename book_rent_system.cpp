#include <iostream>
using namespace std;
#define NAME_SIZE 33
#define BOOK_MAX 10
//책정보를 담은 구조체
struct BookInfo{
	char name[NAME_SIZE] = {};
	int rent_price = 0;
	int book_num = 0;
	bool rent = false;
};
enum MENU {
	MENU_NONE,
	MENU_INSERT,
	MENU_RENT,
	MENU_RETURN,
	MENU_OUTPUT,
	MENU_EXIT
};


int main() {
	int iMenuNumber;
	int iBookCount = 1;
	char strSearchName[NAME_SIZE] = {};
	BookInfo tBookArr[BOOK_MAX] = {};

	cout << "도서 관리 프로그램입니다. -Made by KSJ\n\n";
	system("pause");
	//무한루프로 도서관리
	while (true) {
		system("cls");
		cout << "1. 도서 등록\n";
		cout << "2. 도서 대여\n";
		cout << "3. 도서 반납\n";
		cout << "4. 도서 목록\n";
		cout << "5. 종료\n";
		cout << "메뉴를 입력하세요 -> ";
		cin >> iMenuNumber;
		//입력오류처리
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
		}
		//예외처리 exit선택시
		if (iMenuNumber == MENU_EXIT) {
			break;
		}
		//case로 나머지 메뉴 다루기
		switch (iMenuNumber) {
		case MENU_INSERT:
			system("cls");
			cout << "==================도서 등록=================\n";
			cout << "도서명 : ";
			cin.ignore(1024, '\n');
			cin.getline(tBookArr[iBookCount].name, NAME_SIZE);
			cout << "대여 금액 : ";
			cin >> tBookArr[iBookCount].rent_price;
			tBookArr[iBookCount].book_num = iBookCount;
			iBookCount++;
			cout << "등록 완료!\n";
			break;
		case MENU_RENT:
			system("cls");
			cout << "==================도서 대여=================\n";
			cout << "도서명 : ";
			cin.ignore(1024, '\n');
			cin.getline(strSearchName, NAME_SIZE);
			for (int i = 1; i < iBookCount; i++) {
				if (strcmp(strSearchName, tBookArr[i].name) == 0) {
					if (tBookArr[i].rent) {
						cout << "이미 대여된 도서입니다.\n";
					}
					else {
						tBookArr[i].rent = true;
						cout << "대여 완료! \n";
					}
					break;
				}
			}
			break;
		case MENU_RETURN:
			system("cls");
			cout << "==================도서 반납=================\n";
			cout << "도서명 : ";
			cin.ignore(1024, '\n');
			cin.getline(strSearchName, NAME_SIZE);
			for (int i = 1; i < iBookCount; i++) {
				if (strcmp(strSearchName, tBookArr[i].name) == 0) {
					if (tBookArr[i].rent) {
						tBookArr[i].rent = false;
						cout << "반납완료\n";
					}
					else {
						cout << "대여된 도서가 아닙니다.\n";
					}
					break;
				}
			}
			break;
		case MENU_OUTPUT:
			system("cls");
			cout << "==================도서 현황=================\n";
			for (int i = 1; i < iBookCount; i++) {
				cout << i << "번\n";
				cout << "-----------------------\n";
				cout << "도서명 : " << tBookArr[i].name << "\n";
				cout << "대여 금액 : " << tBookArr[i].rent_price << '\n';
				cout << "대여 여부 : ";
				tBookArr[i].rent ? (cout << "O\n\n") : (cout << "X\n\n");
			}
			break;
		default:
			break;
		}
		system("pause");
	}
	return 0;
}