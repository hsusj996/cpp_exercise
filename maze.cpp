#include <iostream>
#include <conio.h>
#include <time.h>
using namespace std;

/*
0 : 도착점
1 : 길
2 : 시작점
3 : 도착점
4 : 폭탄
5 : 파워
6 : 벽밀기
7 : 투명A
8 : 웜홀
*/
struct _tagPoint {
	int x;
	int y;
};

typedef _tagPoint POINT;
typedef _tagPoint* PPOINT;

typedef struct _tagPlayer {
	_tagPoint tPos;
	bool bWallPush;
	bool bWallPushOn;
	bool bTransparency;
	bool bTransparencyOn;
	int iBombPower;
}PLAYER, *PPLAYER;

void SetMaze(char Maze[21][21], PPLAYER pPlayer, PPOINT pStartPos, PPOINT pEndPos) {
	//MazeList.txt 파일을 읽어와서 미로 목록을 만든다.

	FILE* pFile = NULL;
	//미로 맵의 이중포인터
	char** pMazeList = NULL;

	fopen_s(&pFile, "MazeList.txt", "rt");

	if (pFile) {
		char cCount;
		
		fread(&cCount, 1, 1, pFile);
		//그냥 읽으면 문자형태로 저장되기 떄문에 정수형태로 변환
		int iMazeCount = atoi(&cCount);

		fread(&cCount, 1, 1, pFile);

		//맵 개수(iMazeCount)만큼 메모리를 할당한다.
		pMazeList = new char* [iMazeCount];
		//각 맵의 파일명을 저장한다.
		for (int i = 0; i < iMazeCount; i++) {
			//파일명의 문자개수
			int iNameCount = 0;
			//파일명을 넉넉하게 256바이트의 배열을 할당한다.
			pMazeList[i] = new char[256];
			//문자 하나씩 읽어서 개행문자를 기준하여 구분한ㄴ다
			while (true) {
				fread(&cCount, 1, 1, pFile);

				if (cCount != '\n') {
					pMazeList[i][iNameCount] = cCount;
					iNameCount++;
				}
				else
					break;
			}
			//파일이름을 모두 읽으면 문자열의 마지막에 0을 넣어서
			//문자열의 끝을 알려준다.
			pMazeList[i][iNameCount] = 0;
		}
		fclose(pFile);

		//읽을 파일 목록이 만들어졌으므로 각 파일중 하나를 선택해서
		//미로를 읽어와서 선택한다.

		for (int i = 0; i < iMazeCount; i++) {
			cout << i + 1 << ". " << pMazeList[i] << endl;
		}

		cout << "미로를 선택하세요. :";
		int iSelect;
		cin >> iSelect;

		fopen_s(&pFile, pMazeList[iSelect - 1], "rt");

		if (pFile) {
			//미로의 세로 줄 수만큼 반복하며 각 줄 별로 읽어온다.
			for (int i = 0; i < 20; i++) {
				fread(Maze[i], 1, 20, pFile);
				//좌표설정을 위해 시작점, 도착점의 경우를
				//분리한다
				for (int j = 0; j < 20; j++) {
					if (Maze[i][j] == '2') {
						pStartPos->x = j;
						pStartPos->y = i;
						pPlayer->tPos = *pStartPos;
					}
					else if (Maze[i][j] == '3') {
						pEndPos->x = j;
						pEndPos->y = i;
					}
				}

				fread(&cCount, 1, 1, pFile);
			}

			fclose(pFile);
		}
	}

	/*pStartPos->x = 0;
	pStartPos->y = 0;

	pEndPos->x = 19;
	pEndPos->y = 19;

	pPlayer->tPos = *pStartPos;

	strcpy_s(Maze[0],  "21110000000000000000");
	strcpy_s(Maze[1],  "00010000000000000000");
	strcpy_s(Maze[2],  "00011111111111000000");
	strcpy_s(Maze[3],  "00010000000001100000");
	strcpy_s(Maze[4],  "00010000000000100000");
	strcpy_s(Maze[5],  "01110000000000100000");
	strcpy_s(Maze[6],  "00000000000000100000");
	strcpy_s(Maze[7],  "00000000001111111100");
	strcpy_s(Maze[8],  "00000010001000000100");
	strcpy_s(Maze[9],  "00000010001000000100");
	strcpy_s(Maze[10], "00000011111000000100");
	strcpy_s(Maze[11], "00001110000000000100");
	strcpy_s(Maze[12], "00000000000011111100");
	strcpy_s(Maze[13], "00000000000010000000");
	strcpy_s(Maze[14], "00000100000010000000");
	strcpy_s(Maze[15], "00000100000010000000");
	strcpy_s(Maze[16], "00000100000010000000");
	strcpy_s(Maze[17], "00111111111111111000");
	strcpy_s(Maze[18], "00100000000000001111");
	strcpy_s(Maze[19], "00000000000000000003");*/
}

void OutputMaze(char Maze[21][21], PPLAYER pPlayer) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (Maze[i][j] == '4')
				cout << "♨";
			else if (pPlayer->tPos.y == i && pPlayer->tPos.x == j)
				cout << "☆";
			else if (Maze[i][j] == '0')
				cout << "■";
			else if (Maze[i][j] == '1')
				cout << "  ";
			else if (Maze[i][j] == '2')
				cout << "★";
			else if (Maze[i][j] == '3')
				cout << "◎";
			else if (Maze[i][j] == '5')
				cout << "△";
			else if (Maze[i][j] == '6')
				cout << "※";
			else if (Maze[i][j] == '7')
				cout << "⊙";
		}
		cout << endl;
	}
	cout << "폭탄파워 : " << pPlayer->iBombPower << endl;
	cout << "벽통과 : ";
	if (pPlayer->bTransparency) {
		cout << "O\t";
		if (pPlayer->bTransparencyOn)
			cout << "ON\t";
		else
			cout << "OFF\t";
	}
	else
		cout << "X\t";

	cout << "벽밀기 : ";
	if (pPlayer->bWallPush) {
		cout << "O\t";
		if (pPlayer->bWallPushOn)
			cout << "ON" << endl;
		else
			cout << "OFF" << endl;
	}
	else
		cout << "X" << endl;

	cout << endl << endl;
}

bool AddItem(char cItemType, PPLAYER pPlayer) {
	if (cItemType == '5') {
		if (pPlayer->iBombPower < 5)
			pPlayer->iBombPower++;

		return true;
	}
	else if (cItemType == '6') {
		pPlayer->bWallPush = true;

		return true;
	}
	else if (cItemType == '7') {
		pPlayer->bTransparency = true;

		return true;
	}
	return false;
}

void MoveUp(char Maze[21][21], PPLAYER pPlayer) {
	//-1인 경우는 화면밖
	if (pPlayer->tPos.y - 1 >= 0) {
		if (pPlayer->bTransparencyOn) {
			if (pPlayer->bWallPushOn) {
				if (Maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] == '0') {
					pPlayer->tPos.y--;
				}
				else if(Maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] == '1' &&
					    Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] == '0'){
							Maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] = '0';
							Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] = '1';
							pPlayer->tPos.y--;
				}
			}
			else {
				pPlayer->tPos.y--;
			}
		}
		else {
			if (pPlayer->bWallPushOn) {
				if (Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] == '1') {
					pPlayer->tPos.y--;
				}
				else if (Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] == '0' &&
					Maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] == '1') {
					Maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] = '0';
					Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] = '1';
					pPlayer->tPos.y--;
				}
			}
			else {
				if (Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] == '1') {
					pPlayer->tPos.y--;
				}
			}
		}
	}
	return;
}
void MoveLeft(char Maze[21][21], PPLAYER pPlayer) {
	//-1인 경우는 화면밖
	if (pPlayer->tPos.x - 1 >= 0) {
		//벽통과가 가능할때 벽에 대한 제약없이 이동
		if (pPlayer->bTransparencyOn) {
			if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1], pPlayer))
				Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] = '1';
			pPlayer->tPos.x--;
			return;
		}
		//벽통과가 불가능할때 벽은 통과 불가능
		else if (Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '0' && 
				 Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '4') {
			if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1], pPlayer))
				Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] = '1';

			pPlayer->tPos.x--;
		}
	}
	return;
}
void MoveDown(char Maze[21][21], PPLAYER pPlayer) {
	if (pPlayer->tPos.y + 1 <= 19) {
		if (pPlayer->bTransparencyOn) {
			if (AddItem(Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x], pPlayer))
				Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] = '1';
			pPlayer->tPos.y++;
			return;
		}

		else if (Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '0' &&
			     Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '4') {

			if (AddItem(Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x], pPlayer))
				Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] = '1';
			pPlayer->tPos.y++;
		}
	}
	return;
}
void MoveRight(char Maze[21][21], PPLAYER pPlayer) {
	if (pPlayer->tPos.x + 1 <= 19) {
		if (pPlayer->bTransparencyOn) {
			if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1], pPlayer))
				Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] = '1';
			pPlayer->tPos.x++;
			return;
		}

		else if (Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] != '0' &&
			     Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] != '4') {

			if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1], pPlayer))
				Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] = '1';

			pPlayer->tPos.x++;
		}
	}
	return;
}

void MovePlayer(char Maze[21][21], const PPLAYER pPlayer, char cInput) {
	switch (cInput) {
	case 'W':
	case 'w':
		MoveUp(Maze, pPlayer);
		break;
	case 'A':
	case 'a':
		MoveLeft(Maze, pPlayer);
		break;
	case 'S':
	case 's':
		MoveDown(Maze, pPlayer);
		break;
	case 'D':
	case 'd':
		MoveRight(Maze, pPlayer);
		break;
	default:
		return;
	}
}

void CreateBomb(char Maze[21][21], const PPLAYER pPlayer, int *pBombCount, PPOINT pBombArr) {
	if (*pBombCount == 5)
		return;
	else if (Maze[pPlayer->tPos.y][pPlayer->tPos.x] == '0')
		return;

	for (int i = 0; i < *pBombCount; i++) {
		if (pPlayer->tPos.x == pBombArr[i].x &&
			pPlayer->tPos.y == pBombArr[i].y)
			return;
	} 

	pBombArr[*pBombCount] = pPlayer->tPos;
	++(*pBombCount);

	Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '4';
}

void Fire(char Maze[21][21], const PPLAYER pPlayer, int* pBombCount, PPOINT pBombArr) {
	for (int i = 0; i < *pBombCount; i++) {
		for (int j = 1; j <= pPlayer->iBombPower; j++) {
			Maze[pBombArr[i].y][pBombArr[i].x] = '1';

			if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y) {
				pPlayer->tPos.x = 0;
				pPlayer->tPos.y = 0;
			}
			if (pBombArr[i].y - j >= 0) {
				if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y - j == pBombArr[i].y) {
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}

				if (Maze[pBombArr[i].y - j][pBombArr[i].x] == '0')
				{
					Maze[pBombArr[i].y - j][pBombArr[i].x] = '1';

					//벽을 부수면 확률에 따라 아이템 생성

					if (rand() % 100 < 20) {
						int iPercent = rand() % 100;
						if (iPercent < 70)
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '5';
						else if (iPercent < 80)
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '6';
						else
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '7';
					}
				}
			}
			if (pBombArr[i].x - j >= 0) {
				if (pPlayer->tPos.x == pBombArr[i].x - j && pPlayer->tPos.y == pBombArr[i].y) {
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}

				if (Maze[pBombArr[i].y][pBombArr[i].x - j] == '0')
				{
					Maze[pBombArr[i].y][pBombArr[i].x - j] = '1';

					//벽을 부수면 확률에 따라 아이템 생성

					if (rand() % 100 < 20) {
						int iPercent = rand() % 100;
						if (iPercent < 70)
							Maze[pBombArr[i].y][pBombArr[i].x - j] = '5';
						else if (iPercent < 80)
							Maze[pBombArr[i].y][pBombArr[i].x - j] = '6';
						else
							Maze[pBombArr[i].y][pBombArr[i].x - j] = '7';
					}
				}
			}
			if (pBombArr[i].y + j < 20) {
				if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y + j == pBombArr[i].y) {
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}

				if (Maze[pBombArr[i].y + j][pBombArr[i].x] == '0')
				{
					Maze[pBombArr[i].y + j][pBombArr[i].x] = '1';

					//벽을 부수면 확률에 따라 아이템 생성
					if (rand() % 100 < 20) {
						int iPercent = rand() % 100;
						if (iPercent < 70)
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '5';
						else if (iPercent < 80)
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '6';
						else
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '7';
					}
				}
			}
			if (pBombArr[i].x + j < 20) {
				if (pPlayer->tPos.x == pBombArr[i].x + j && pPlayer->tPos.y == pBombArr[i].y) {
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}

				if (Maze[pBombArr[i].y][pBombArr[i].x + j] == '0')
				{
					Maze[pBombArr[i].y][pBombArr[i].x + j] = '1';

					//벽을 부수면 확률에 따라 아이템 생성
					if (rand() % 100 < 20) {
						int iPercent = rand() % 100;
						if (iPercent < 70)
							Maze[pBombArr[i].y][pBombArr[i].x + j] = '5';
						else if (iPercent < 80)
							Maze[pBombArr[i].y][pBombArr[i].x + j] = '6';
						else
							Maze[pBombArr[i].y][pBombArr[i].x + j] = '7';
					}
				}
			}
		}
	}
	*pBombCount = 0;
}

int main() {
	srand((unsigned int)time(0));
	// 20 x 20 미로를 만든다.
	char strMaze[21][21] = {};

	PLAYER tPlayer = {};
	POINT tStartPos;
	POINT tEndPos;

	tPlayer.iBombPower = 1;

	int iBombCount = 0;

	POINT tBombPos[5];

	SetMaze(strMaze, &tPlayer, &tStartPos, &tEndPos);

	while (true) {
		system("cls");

		//미로를 출력
		OutputMaze(strMaze, &tPlayer);

		if (tPlayer.tPos.x == tEndPos.x && tPlayer.tPos.y == tEndPos.y) {
			cout << " 도착 " << endl;
			break;
		}

		cout << "w : ↑   a : ←   s : ↓   d : →" << endl;
		cout << "t: 폭탄설치   u : 폭파   i : 벽밀기 ON/OFF   o : 투명화 ON/OFF" << endl;
		cout << "q: 끝내기" << endl;
		char cInput = _getch();

		if (cInput == 'q' || cInput == 'Q')
			break;

		else if (cInput == 't' || cInput == 'T') {
			CreateBomb(strMaze, &tPlayer, &iBombCount, tBombPos);
		}

		else if (cInput == 'u' || cInput == 'U') {
			Fire(strMaze, &tPlayer, &iBombCount, tBombPos);
		}
		else if (cInput == 'i' || cInput == 'I') {
			if (tPlayer.bWallPush)
				tPlayer.bWallPushOn = !tPlayer.bWallPushOn;
		}
		else if (cInput == 'o' || cInput == 'O') {
			if (tPlayer.bTransparency)
				tPlayer.bTransparencyOn = !tPlayer.bTransparencyOn;
		}

		MovePlayer(strMaze, &tPlayer, cInput);
	}
	return 0;
}