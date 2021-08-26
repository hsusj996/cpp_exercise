#include <iostream>
#include <time.h>
using namespace std;

enum AI_MODE
{
	AM_EASY = 1,
	AM_HARD
};

enum LINE_NUMBER
{
	LN_H1,
	LN_H2,
	LN_H3,
	LN_H4,
	LN_H5,
	LN_V1,
	LN_V2,
	LN_V3,
	LN_V4,
	LN_V5,
	LN_LT,
	LN_RT
};
int main()
{
	int iNumber[25];
	int iAINumber[25];
	int iAIMode;
	int bingo = 0, AIbingo = 0;
	//�������̺�
	srand((unsigned int)time(NULL));
	//1 ~ 25 ���� �Ҵ�
	for (int i = 0; i < 25; i++) {
		iNumber[i] = i + 1;
		iAINumber[i] = i + 1;
	}
	//��� �����ϰ� �����ش�.
	for (int i = 0; i < 100; i++) {
		int idx1 = rand() % 25;
		int idx2 = rand() % 25;
		int temp;

		temp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = temp;

		idx1 = rand() % 25;
		idx2 = rand() % 25;
		temp = iAINumber[idx1];
		iAINumber[idx1] = iAINumber[idx2];
		iAINumber[idx2] = temp;
	}
	//AI ��� ����
	while (true) {
		system("cls");
		cout << "1. Easy" << endl;
		cout << "2. Hard" << endl;
		cout << "AI ��带 �����ϼ���. : ";
		cin >> iAIMode;

		if (iAIMode >= AM_EASY && iAIMode <= AM_HARD) {
			break;
		}
	}
	//Easy ����� ��� ���õ��� ���� �����߿��� �������� ���� �̴´�
	int iNoneSelect[25] = {};
	int iNoneSelectCount = 0;
	//���ӽ���
	while (1) {
		system("cls");
		//�������̺� ���
		cout << "==========player===========\n";
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (iNumber[i * 5 + j] == INT_MAX) {
					cout << "*" << "\t";
				}
				else {
					cout << iNumber[i * 5 + j] << "\t";
				}
			}
			cout << "\n";
		}
		cout << "bingo : " << bingo << "\n\n";

		//AI �������̺� ���
		cout << "==============AI=============\n";
		switch (iAIMode) {
		case AM_EASY:
			cout << "EASY\n";
			break;
		case AM_HARD:
			cout << "HARD\n";
			break;
		}
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (iAINumber[i * 5 + j] == INT_MAX) {
					cout << "*" << "\t";
				}
				else {
					cout << iAINumber[i * 5 + j] << "\t";
				}
			}
			cout << "\n";
		}
		cout << "bingo : " << AIbingo << "\n";

		//bingo >= 5��� �¸�, ���� ����
		if (bingo >= 5) {
			cout << "\n player �¸�!! \n";
			break;
		}
		if (AIbingo >= 5) {
			cout << "\n AI �¸�!! \n";
			break;
		}
		//���ϴ� ���� �Է�
		cout << "���ڸ� �Է��ϼ��� (0 : ����) : ";
		bingo = 0;
		AIbingo = 0;
		int n;
		cin >> n;
		bool bnum = true; //�ߺ��Է��� ����(true : �ߺ��� ����)
		//����ó��
		if (n == 0) {
			break;
		}
		else if (n < 1 || n>25) {
			continue;
		}
		//���ڰ� �ԷµǸ� �ش���ڸ� *�� ġȯ�Ѵ�.
		for (int i = 0; i < 25; i++) {
			if (iNumber[i] == n) {
				iNumber[i] = INT_MAX;
				bnum = false;
				break;
			}
		}
		//AI���� �ش���ڸ� *�� ġȯ�Ѵ�.
		for (int i = 0; i < 25; i++) {
			if (iAINumber[i] == n) {
				iAINumber[i] = INT_MAX;
				break;
			}
		}
		switch (iAIMode) {
		case AM_EASY:
			//Easy ����� ��� ���õ��� ���� �����߿��� �������� ���� �̴´�
			iNoneSelectCount = 0;
			for (int i = 0; i < 25; i++) {
				if (iAINumber[i] != INT_MAX) {
					iNoneSelect[iNoneSelectCount] = iAINumber[i];
					iNoneSelectCount++;
				}
			}
			n = iNoneSelect[rand() % iNoneSelectCount];
			break;
		case AM_HARD:
			//�ϵ���� ���� ������ ������ �ϼ� ���ɼ��� ���� ���� ����
			//ã�Ƽ� �� �ٿ� �ִ� ������ �ϳ��� *�� ������ش�.
			int iLine;
			int iStarCount = 0;
			int iSaveCount = 0;

			//���� ������ üũ
			for (int i = 0; i < 5; i++) {
				iStarCount = 0;
				for (int j = 0; j < 5; j++) {
					if (iAINumber[i * 5 + j] == INT_MAX)
						iStarCount++;
				}
				//���� 5�� �̸��̾�� ���� ���� �ƴϰ� ������ ���帹��
				//������ ������ Ŀ�� ���� ���� ���� �����̹Ƿ� ������
				//��ü���ְ� ����� �� ���� ��ü�Ѵ�.
				if (iStarCount < 5 && iSaveCount < iStarCount)
				{
					iLine = i;
					iSaveCount = iStarCount;
				}
			}

			//���� ������ üũ
			for (int i = 0; i < 5; i++) {
				iStarCount = 0;
				for (int j = 0; j < 5; j++) {
					if (iAINumber[j * 5 + i] == INT_MAX)
						iStarCount++;
				}
				if (iStarCount < 5 && iSaveCount < iStarCount)
				{
					iLine = i + 5;
					iSaveCount = iStarCount;
				}
			}

			//���� -> ������ �밢�� üũ
			iStarCount = 0;
			for (int i = 0; i < 25; i += 6) {
				if (iAINumber[i] == INT_MAX)
					iStarCount++;
			}
			if (iStarCount < 5 && iSaveCount < iStarCount)
			{
				iLine = LN_LT;
				iSaveCount = iStarCount;
			}
			//������ -> ���� �밢�� üũ
			iStarCount = 0;
			for (int i = 4; i < 20; i += 4) {
				if (iAINumber[i] == INT_MAX)
					iStarCount++;
			}
			if (iStarCount < 5 && iSaveCount < iStarCount)
			{
				iLine = LN_RT;
				iSaveCount = iStarCount;
			}
			//��� ������ ���������� iLine�� ���ɼ��� ���� ���� �� ��ȣ��
			// ����Ǿ���.
			// �� �ٿ� �ִ� *�� �ƴ� ������ �ϳ��� �����ϰ� �Ѵ�.
			//�������� ���
			if (iLine <= LN_H5) {
				//�������� ��� iLine�� 0~4 ������ ���̴�.
				for (int i = 0; i < 5; i++) {
					if (iAINumber[iLine * 5 + i] != INT_MAX) {
						n = iAINumber[iLine * 5 + i];
						break;
					}
				}
			}
			else if (iLine <= LN_V5) {
				//�������� ��� iLine�� 5~9������ ���̴�.
				for (int i = 0; i < 5; i++) {
					if (iAINumber[i * 5 + (iLine - 5)] != INT_MAX)
					{
						n = iAINumber[i * 5 + (iLine - 5)];
						break;
					}
				}
			}
			else if (iLine == LN_LT) {
				for (int i = 0; i < 25; i += 6) {
					if (iAINumber[i] != INT_MAX) {
						n = iAINumber[i];
						break;
					}
				}
			}
			else if (iLine == LN_RT) {
				for (int i = 4; i <= 20; i += 4) {
					if (iAINumber[i] != INT_MAX) {
						n = iAINumber[i];
						break;
					}
				}
			}
			break;
		}
		//���ڰ� �ԷµǸ� �ش���ڸ� *�� ġȯ�Ѵ�.
		for (int i = 0; i < 25; i++) {
			if (iNumber[i] == n) {
				iNumber[i] = INT_MAX;
				bnum = false;
				break;
			}
		}
		//AI���� �ش���ڸ� *�� ġȯ�Ѵ�.
		for (int i = 0; i < 25; i++) {
			if (iAINumber[i] == n) {
				iAINumber[i] = INT_MAX;
				break;
			}
		}
		//�ߺ��� ��� bnum = true �ٽ� �Է¹޴´�.
		if (bnum) {
			continue;
		}
		//�������� ����ϱ�
		int star1;
		int star2;
		int AIstar1;
		int AIstar2;
		//���� ���� ���� ���� ���� *�� 5����� ����++
		//�� �κ��� �밢����� �ٷ��� ����
		for (int i = 0; i < 5; i++) {
			star1 = 0;
			star2 = 0;
			for (int j = 0; j < 5; j++) {
				if (iNumber[i * 5 + j] == INT_MAX) {
					star1++;
				}
				if (iNumber[j * 5 + i] == INT_MAX) {
					star2++;
				}
			}
			if (star1 == 5) {
				bingo++;
			}
			if (star2 == 5) {
				bingo++;
			}
		}
		//AI ��,�� ����
		for (int i = 0; i < 5; i++) {
			AIstar1 = 0;
			AIstar2 = 0;
			for (int j = 0; j < 5; j++) {
				if (iAINumber[i * 5 + j] == INT_MAX) {
					AIstar1++;
				}
				if (iAINumber[j * 5 + i] == INT_MAX) {
					AIstar2++;
				}
			}
			if (AIstar1 == 5) {
				AIbingo++;
			}
			if (AIstar2 == 5) {
				AIbingo++;
			}
		}
		//�밢����

		//������밢
		star1 = 0;
		for (int i = 0; i < 25; i += 6) {
			if (iNumber[i] == INT_MAX) {
				star1++;
			}
		}
		if (star1 == 5) {
			bingo++;
		}
		AIstar1 = 0;
		for (int i = 0; i < 25; i += 6) {
			if (iAINumber[i] == INT_MAX) {
				AIstar1++;
			}
		}
		if (AIstar1 == 5) {
			AIbingo++;
		}
		//�����밢
		star1 = 0;
		for (int i = 4; i <= 20; i += 4) {
			if (iNumber[i] == INT_MAX) {
				star1++;
			}
		}
		if (star1 == 5) {
			bingo++;
		}
		AIstar1 = 0;
		for (int i = 4; i <= 20; i += 4) {
			if (iAINumber[i] == INT_MAX) {
				AIstar1++;
			}
		}
		if (AIstar1 == 5) {
			AIbingo++;
		}
	}
	cout << "\n������ �����մϴ�.";
}