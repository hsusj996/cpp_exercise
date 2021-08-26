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
	//랜덤테이블
	srand((unsigned int)time(NULL));
	//1 ~ 25 숫자 할당
	for (int i = 0; i < 25; i++) {
		iNumber[i] = i + 1;
		iAINumber[i] = i + 1;
	}
	//모두 랜덤하게 섞어준다.
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
	//AI 모드 선택
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
	//Easy 모드의 경우 선택되지 않은 수들중에서 랜덤으로 수를 뽑는다
	int iNoneSelect[25] = {};
	int iNoneSelectCount = 0;
	//게임시작
	while (1) {
		system("cls");
		//빙고테이블 출력
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

		//AI 빙고테이블 출력
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

		//bingo >= 5라면 승리, 게임 종료
		if (bingo >= 5) {
			cout << "\n player 승리!! \n";
			break;
		}
		if (AIbingo >= 5) {
			cout << "\n AI 승리!! \n";
			break;
		}
		//원하는 숫자 입력
		cout << "숫자를 입력하세요 (0 : 종료) : ";
		bingo = 0;
		AIbingo = 0;
		int n;
		cin >> n;
		bool bnum = true; //중복입력을 방지(true : 중복인 상태)
		//예외처리
		if (n == 0) {
			break;
		}
		else if (n < 1 || n>25) {
			continue;
		}
		//숫자가 입력되면 해당숫자를 *로 치환한다.
		for (int i = 0; i < 25; i++) {
			if (iNumber[i] == n) {
				iNumber[i] = INT_MAX;
				bnum = false;
				break;
			}
		}
		//AI역시 해당숫자를 *로 치환한다.
		for (int i = 0; i < 25; i++) {
			if (iAINumber[i] == n) {
				iAINumber[i] = INT_MAX;
				break;
			}
		}
		switch (iAIMode) {
		case AM_EASY:
			//Easy 모드의 경우 선택되지 않은 수들중에서 랜덤으로 수를 뽑는다
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
			//하드모드는 현재 숫자중 빙고줄 완성 가능성이 가장 높은 줄을
			//찾아서 그 줄에 있는 숫자중 하나를 *로 만들어준다.
			int iLine;
			int iStarCount = 0;
			int iSaveCount = 0;

			//가로 라인을 체크
			for (int i = 0; i < 5; i++) {
				iStarCount = 0;
				for (int j = 0; j < 5; j++) {
					if (iAINumber[i * 5 + j] == INT_MAX)
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
					if (iAINumber[j * 5 + i] == INT_MAX)
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
				if (iAINumber[i] == INT_MAX)
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
				if (iAINumber[i] == INT_MAX)
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
					if (iAINumber[iLine * 5 + i] != INT_MAX) {
						n = iAINumber[iLine * 5 + i];
						break;
					}
				}
			}
			else if (iLine <= LN_V5) {
				//세로줄일 경우 iLine이 5~9사이의 값이다.
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
		//숫자가 입력되면 해당숫자를 *로 치환한다.
		for (int i = 0; i < 25; i++) {
			if (iNumber[i] == n) {
				iNumber[i] = INT_MAX;
				bnum = false;
				break;
			}
		}
		//AI역시 해당숫자를 *로 치환한다.
		for (int i = 0; i < 25; i++) {
			if (iAINumber[i] == n) {
				iAINumber[i] = INT_MAX;
				break;
			}
		}
		//중복인 경우 bnum = true 다시 입력받는다.
		if (bnum) {
			continue;
		}
		//빙고개수를 출력하기
		int star1;
		int star2;
		int AIstar1;
		int AIstar2;
		//열과 행을 따로 셀때 만약 *이 5개라면 빙고++
		//이 부분은 대각빙고는 다루지 않음
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
		//AI 열,행 빙고
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
		//대각빙고

		//우하향대각
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
		//우상향대각
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
	cout << "\n게임을 종료합니다.";
}