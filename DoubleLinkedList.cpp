#include <iostream>
//����� ���� ��������� ""�ȿ� �����ش�.
#include "ListHeader.h" 
using namespace std;
/*
���θ޴��� ���ı�� �߰�
�й�, ��� �������� �������� ���
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

	cout << "1. �л��Է�" << endl;
	cout << "2. ����" << endl;
	cout << "3. Ž��" << endl;
	cout << "4. ���" << endl;
	cout << "5. ����" << endl;
	cout << "6. ������" << endl;
	cout << "�޴��� �����ϼ��� : ";
	int iInput = Inputint();

	if (iInput <= MM_NONE || iInput > MM_QUIT)
		return MM_NONE;

	return iInput;
}

int main() {
	LIST tList;

	InitList(&tList);

	while (true) {
		//���θ޴� ����
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

//����ũ�帮��Ʈ�� ������ begin�� end���� ��忡 ���
// ��� ���� ������ �ĳ��� ��ũ�ȴ�.
//���� ���� ����ڰ� ���ϴ´�� ������ Ȥ�� ����������
//Ž���� �����ϴ�.