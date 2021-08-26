#include <iostream>
using namespace std;
#define NAME_SIZE 33
#define BOOK_MAX 10
//å������ ���� ����ü
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

	cout << "���� ���� ���α׷��Դϴ�. -Made by KSJ\n\n";
	system("pause");
	//���ѷ����� ��������
	while (true) {
		system("cls");
		cout << "1. ���� ���\n";
		cout << "2. ���� �뿩\n";
		cout << "3. ���� �ݳ�\n";
		cout << "4. ���� ���\n";
		cout << "5. ����\n";
		cout << "�޴��� �Է��ϼ��� -> ";
		cin >> iMenuNumber;
		//�Է¿���ó��
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
		}
		//����ó�� exit���ý�
		if (iMenuNumber == MENU_EXIT) {
			break;
		}
		//case�� ������ �޴� �ٷ��
		switch (iMenuNumber) {
		case MENU_INSERT:
			system("cls");
			cout << "==================���� ���=================\n";
			cout << "������ : ";
			cin.ignore(1024, '\n');
			cin.getline(tBookArr[iBookCount].name, NAME_SIZE);
			cout << "�뿩 �ݾ� : ";
			cin >> tBookArr[iBookCount].rent_price;
			tBookArr[iBookCount].book_num = iBookCount;
			iBookCount++;
			cout << "��� �Ϸ�!\n";
			break;
		case MENU_RENT:
			system("cls");
			cout << "==================���� �뿩=================\n";
			cout << "������ : ";
			cin.ignore(1024, '\n');
			cin.getline(strSearchName, NAME_SIZE);
			for (int i = 1; i < iBookCount; i++) {
				if (strcmp(strSearchName, tBookArr[i].name) == 0) {
					if (tBookArr[i].rent) {
						cout << "�̹� �뿩�� �����Դϴ�.\n";
					}
					else {
						tBookArr[i].rent = true;
						cout << "�뿩 �Ϸ�! \n";
					}
					break;
				}
			}
			break;
		case MENU_RETURN:
			system("cls");
			cout << "==================���� �ݳ�=================\n";
			cout << "������ : ";
			cin.ignore(1024, '\n');
			cin.getline(strSearchName, NAME_SIZE);
			for (int i = 1; i < iBookCount; i++) {
				if (strcmp(strSearchName, tBookArr[i].name) == 0) {
					if (tBookArr[i].rent) {
						tBookArr[i].rent = false;
						cout << "�ݳ��Ϸ�\n";
					}
					else {
						cout << "�뿩�� ������ �ƴմϴ�.\n";
					}
					break;
				}
			}
			break;
		case MENU_OUTPUT:
			system("cls");
			cout << "==================���� ��Ȳ=================\n";
			for (int i = 1; i < iBookCount; i++) {
				cout << i << "��\n";
				cout << "-----------------------\n";
				cout << "������ : " << tBookArr[i].name << "\n";
				cout << "�뿩 �ݾ� : " << tBookArr[i].rent_price << '\n';
				cout << "�뿩 ���� : ";
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