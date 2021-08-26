#include <iostream>
#include <time.h>
#include <conio.h> //�ܼ�â���� ����� ��ɵ��� ����
using namespace std;

int main()
{
	srand((unsigned int)time(0));
	
	int iNumber[25] = {};

	for (int i = 0; i < 24; i++) {
		iNumber[i] = i + 1;
	}

	iNumber[24] = INT_MAX;

	int iTemp, idx1, idx2;

	for (int i = 0; i < 100; i++) {
		idx1 = rand() % 24;
		idx2 = rand() % 24;

		iTemp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = iTemp;
	}
	int Star_Index = 24;
	while (true) {
		system("cls");
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (iNumber[i * 5 + j ] == INT_MAX) {
					cout << "*" << "\t";
				}
				else {
					cout << iNumber[i * 5 + j] << "\t";
				}
			}
			cout << '\n';
		}
		cout << "w : �� s : �Ʒ� a : ���� d : ������ q : ���� :";
		char cInput = _getch(); //_getch�� ����1���� �Է��ϴ� ���� �ٷ� ��ȯ
		
		if (cInput == 'q' || cInput == 'Q') {
			break;
		}

		switch (cInput) {
		case 'w':
		case 'W':
			if (Star_Index < 5) {
				break;
			}
			iNumber[Star_Index] = iNumber[Star_Index - 5];
			iNumber[Star_Index - 5] = INT_MAX;
			Star_Index -= 5;
			break;
		case 'a':
		case 'A':
			if (Star_Index % 5 == 0) {
				break;
			}
			iNumber[Star_Index] = iNumber[Star_Index - 1];
			iNumber[Star_Index - 1] = INT_MAX;
			Star_Index -= 1;
			break;
		case 's':
		case 'S':
			if (Star_Index > 19) {
				break;
			}
			iNumber[Star_Index] = iNumber[Star_Index + 5];
			iNumber[Star_Index + 5] = INT_MAX;
			Star_Index += 5;
			break;
		case 'd':
		case 'D':
			if (Star_Index % 5 == 4) {
				break;
			}
			iNumber[Star_Index] = iNumber[Star_Index + 1];
			iNumber[Star_Index + 1] = INT_MAX;
			Star_Index += 1;
			break;
		}
		bool bwin = true;
		for (int i = 0; i < 24; i++) {
			if (iNumber[i] != i+1)
			{
				bwin = false;
				break;
			}
		}
		if (bwin == true) {
			cout << "���ڸ� ��� ������ϴ�." << "\n";
			break;
		}
	}
	cout << '\n' << "������ �����մϴ�." << '\n';

}