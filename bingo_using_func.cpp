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

void SetNumber(int* pArray) {
	for (int i = 0; i < 25; i++) {
		pArray[i] = i + 1;
	}
}

void Shuffle(int* pArray) {
	for (int i = 0; i < 100; i++) {
		int idx1 = rand() % 25;
		int idx2 = rand() % 25;
		int temp;

		temp = pArray[idx1];
		pArray[idx1] = pArray[idx2];
		pArray[idx2] = temp;
	}
}

AI_MODE SelectAIMode() {
	int iAIMode;
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
	return (AI_MODE)iAIMode;
}

void OutputNumber(int* pArray, int bingo) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (pArray[i * 5 + j] == INT_MAX) {
				cout << "*" << "\t";
			}
			else {
				cout << pArray[i * 5 + j] << "\t";
			}
		}
		cout << "\n";
	}
	cout << "bingo : " << bingo << "\n\n";
}

bool ChangeNumber(int* pArray, int iInput) {
	for (int i = 0; i < 25; i++) {
		if (pArray[i] == iInput) {
			pArray[i] = INT_MAX;
			return false;
		}
	}
	return true;
}

int SelectAINumber(int* pArray, AI_MODE eAIMode) {
	//Easy ����� ��� ���õ��� ���� �����߿��� �������� ���� �̴´�
	int iNoneSelect[25] = {};
	int iNoneSelectCount = 0;

	switch (eAIMode) {
	case AM_EASY:
		//Easy ����� ��� ���õ��� ���� �����߿��� �������� ���� �̴´�
		iNoneSelectCount = 0;
		for (int i = 0; i < 25; i++) {
			if (pArray[i] != INT_MAX) {
				iNoneSelect[iNoneSelectCount] = pArray[i];
				iNoneSelectCount++;
			}
		}
		return iNoneSelect[rand() % iNoneSelectCount];
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
				if (pArray[i * 5 + j] == INT_MAX)
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
				if (pArray[j * 5 + i] == INT_MAX)
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
			if (pArray[i] == INT_MAX)
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
			if (pArray[i] == INT_MAX)
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
				if (pArray[iLine * 5 + i] != INT_MAX) {
					return pArray[iLine * 5 + i];
					break;
				}
			}
		}
		else if (iLine <= LN_V5) {
			//�������� ��� iLine�� 5~9������ ���̴�.
			for (int i = 0; i < 5; i++) {
				if (pArray[i * 5 + (iLine - 5)] != INT_MAX)
				{
					return pArray[i * 5 + (iLine - 5)];
					break;
				}
			}
		}
		else if (iLine == LN_LT) {
			for (int i = 0; i < 25; i += 6) {
				if (pArray[i] != INT_MAX) {
					return pArray[i];
					break;
				}
			}
		}
		else if (iLine == LN_RT) {
			for (int i = 4; i <= 20; i += 4) {
				if (pArray[i] != INT_MAX) {
					return pArray[i];
					break;
				}
			}
		}
		break;
	}
	return -1;
}

int BingoCountingH(int* pArray) {
	int iStar1 = 0, iBingo = 0;
	for (int i = 0; i < 5; i++) {
		iStar1 = 0;
		for (int j = 0; j < 5; j++) {
			if (pArray[j * 5 + i] == INT_MAX) {
				iStar1++;
			}
		}
		if (iStar1 == 5) {
			iBingo++;
		}
	}
	return iBingo;
}
int BingoCountingV(int* pArray) {
	int iStar1 = 0, iBingo = 0;
	for (int i = 0; i < 5; i++) {
		iStar1 = 0;
		for (int j = 0; j < 5; j++) {
			if (pArray[i * 5 + j] == INT_MAX) {
				iStar1++;
			}
		}
		if (iStar1 == 5) {
			iBingo++;
		}
	}
	return iBingo;
}
int BingoCountingLTD(int* pArray) {
	int iStar1 = 0, iBingo = 0;
	for (int i = 4; i <= 20; i += 4) {
		if (pArray[i] == INT_MAX) {
			iStar1++;
		}
	}
	if (iStar1 == 5) {
		iBingo++;
	}
	return iBingo;
}
int BingoCountingRTD(int* pArray) {
	int iStar1 = 0, iBingo = 0;
	for (int i = 0; i < 25; i += 6) {
		if (pArray[i] == INT_MAX) {
			iStar1++;
		}
	}
	if (iStar1 == 5) {
		iBingo++;
	}
	return iBingo;
}
int BingoCounting(int* pArray) {
	int iBingo = 0;
	
	iBingo += BingoCountingV(pArray);
	iBingo += BingoCountingH(pArray);
	iBingo += BingoCountingLTD(pArray);
	iBingo += BingoCountingRTD(pArray);

	return iBingo;
}

int main()
{
	int iNumber[25];
	int iAINumber[25];
	int iAIMode;
	int ibingo = 0, iAIbingo = 0;
	//�������̺�
	srand((unsigned int)time(NULL));
	//1 ~ 25 ���� �Ҵ�
	SetNumber(iNumber);
	SetNumber(iAINumber);

	//��� �����ϰ� �����ش�.
	Shuffle(iNumber);
	Shuffle(iAINumber);

	//AI ��� ����
	AI_MODE eAIMode = SelectAIMode();

	//���ӽ���
	while (1) {
		system("cls");
		//�������̺� ���
		cout << "==========player===========\n";
		OutputNumber(iNumber, ibingo);

		//AI �������̺� ���
		cout << "==============AI=============\n";
		switch (eAIMode) {
		case AM_EASY:
			cout << "EASY\n";
			break;
		case AM_HARD:
			cout << "HARD\n";
			break;
		}
		OutputNumber(iAINumber, iAIbingo);

		//bingo >= 5��� �¸�, ���� ����
		if (ibingo >= 5) {
			cout << "\n player �¸�!! \n";
			break;
		}
		if (iAIbingo >= 5) {
			cout << "\n AI �¸�!! \n";
			break;
		}

		//���ϴ� ���� �Է�
		cout << "���ڸ� �Է��ϼ��� (0 : ����) : ";
		ibingo = 0;
		iAIbingo = 0;
		int iInput;
		cin >> iInput;
		bool bnum = ChangeNumber(iNumber, iInput); //�ߺ��Է��� ����(true : �ߺ��� ����)
		//����ó��
		if (iInput == 0) {
			break;
		}
		else if (iInput < 1 || iInput>25) {
			continue;
		}

		//bnum�� true�� ���� �� �ݺ������� �Է°� ���� ���ڰ� ���� ���(�ߺ��� ���)�̴�.
		//���� �Է��� �ٽ� �޴´�.
		if (bnum)
			continue;

		//AI���� �ش���ڸ� *�� ġȯ�Ѵ�.
		ChangeNumber(iAINumber, iInput);

		iInput = SelectAINumber(iAINumber, eAIMode);

		//���ڰ� �ԷµǸ� �ش���ڸ� *�� ġȯ�Ѵ�.
		ChangeNumber(iNumber, iInput);

		//AI���� �ش���ڸ� *�� ġȯ�Ѵ�.
		ChangeNumber(iAINumber, iInput);

		ibingo = BingoCounting(iNumber);
		iAIbingo = BingoCounting(iAINumber);
	}
	cout << "\n������ �����մϴ�.";
}