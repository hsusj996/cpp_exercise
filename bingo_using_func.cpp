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
		cout << "AI 모드를 선택하세요. : ";
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
	//Easy 모드의 경우 선택되지 않은 수들중에서 랜덤으로 수를 뽑는다
	int iNoneSelect[25] = {};
	int iNoneSelectCount = 0;

	switch (eAIMode) {
	case AM_EASY:
		//Easy 모드의 경우 선택되지 않은 수들중에서 랜덤으로 수를 뽑는다
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
		//하드모드는 현재 숫자중 빙고줄 완성 가능성이 가장 높은 줄을
		//찾아서 그 줄에 있는 숫자중 하나를 *로 만들어준다.
		int iLine;
		int iStarCount = 0;
		int iSaveCount = 0;

		//가로 라인을 체크
		for (int i = 0; i < 5; i++) {
			iStarCount = 0;
			for (int j = 0; j < 5; j++) {
				if (pArray[i * 5 + j] == INT_MAX)
					iStarCount++;
			}
			//별이 5개 미만이어야 빙고 줄이 아니고 기존에 가장많은
			//라인의 별보다 커야 가장 별이 많은 라인이므로 라인을
			//교체해주고 저장된 별 수를 교체한다.
			if (iStarCount < 5 && iSaveCount < iStarCount)
			{
				iLine = i;
				iSaveCount = iStarCount;
			}
		}

		//세로 라인을 체크
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

		//왼쪽 -> 오른쪽 대각선 체크
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
		//오른쪽 -> 왼쪽 대각선 체크
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
		//모든 라인을 조사했으면 iLine에 가능성이 가장 높은 줄 번호가
		// 저장되었다.
		// 그 줄에 있는 *이 아닌 숫자중 하나를 선택하게 한다.
		//가로줄일 경우
		if (iLine <= LN_H5) {
			//가로줄일 경우 iLine이 0~4 사이의 값이다.
			for (int i = 0; i < 5; i++) {
				if (pArray[iLine * 5 + i] != INT_MAX) {
					return pArray[iLine * 5 + i];
					break;
				}
			}
		}
		else if (iLine <= LN_V5) {
			//세로줄일 경우 iLine이 5~9사이의 값이다.
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
	//랜덤테이블
	srand((unsigned int)time(NULL));
	//1 ~ 25 숫자 할당
	SetNumber(iNumber);
	SetNumber(iAINumber);

	//모두 랜덤하게 섞어준다.
	Shuffle(iNumber);
	Shuffle(iAINumber);

	//AI 모드 선택
	AI_MODE eAIMode = SelectAIMode();

	//게임시작
	while (1) {
		system("cls");
		//빙고테이블 출력
		cout << "==========player===========\n";
		OutputNumber(iNumber, ibingo);

		//AI 빙고테이블 출력
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

		//bingo >= 5라면 승리, 게임 종료
		if (ibingo >= 5) {
			cout << "\n player 승리!! \n";
			break;
		}
		if (iAIbingo >= 5) {
			cout << "\n AI 승리!! \n";
			break;
		}

		//원하는 숫자 입력
		cout << "숫자를 입력하세요 (0 : 종료) : ";
		ibingo = 0;
		iAIbingo = 0;
		int iInput;
		cin >> iInput;
		bool bnum = ChangeNumber(iNumber, iInput); //중복입력을 방지(true : 중복인 상태)
		//예외처리
		if (iInput == 0) {
			break;
		}
		else if (iInput < 1 || iInput>25) {
			continue;
		}

		//bnum이 true일 경우는 위 반복문에서 입력과 같은 문자가 없는 경우(중복인 경우)이다.
		//따라서 입력을 다시 받는다.
		if (bnum)
			continue;

		//AI역시 해당숫자를 *로 치환한다.
		ChangeNumber(iAINumber, iInput);

		iInput = SelectAINumber(iAINumber, eAIMode);

		//숫자가 입력되면 해당숫자를 *로 치환한다.
		ChangeNumber(iNumber, iInput);

		//AI역시 해당숫자를 *로 치환한다.
		ChangeNumber(iAINumber, iInput);

		ibingo = BingoCounting(iNumber);
		iAIbingo = BingoCounting(iAINumber);
	}
	cout << "\n게임을 종료합니다.";
}