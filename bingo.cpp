#include <iostream>
#include <time.h>
using namespace std;

enum AI_MODE
{
	AM_EASY = 1,
	AM_HARD
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
//현재원인 : 확인한 빙고를 계속 누적시켜서 빙고갯수가 초과하여 나온다.
//-> 반복시행마다 bingo변수가 계속 누적되어 왔기때문
//-> 변수의 선언을 반복문 밖에서 하고 매 수행시 0으로 초기화함
//버그2 : 우상향 대각선의 bingo에서 오류가 났음
//-> i < 25일 경우 i = 24의 경우까지 포함하기 때문에 수정해야함