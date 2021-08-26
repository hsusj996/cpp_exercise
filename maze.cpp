#include <iostream>
#include <conio.h>
#include <time.h>
using namespace std;

/*
0 : ������
1 : ��
2 : ������
3 : ������
4 : ��ź
5 : �Ŀ�
6 : ���б�
7 : ����A
8 : ��Ȧ
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
	//MazeList.txt ������ �о�ͼ� �̷� ����� �����.

	FILE* pFile = NULL;
	//�̷� ���� ����������
	char** pMazeList = NULL;

	fopen_s(&pFile, "MazeList.txt", "rt");

	if (pFile) {
		char cCount;
		
		fread(&cCount, 1, 1, pFile);
		//�׳� ������ �������·� ����Ǳ� ������ �������·� ��ȯ
		int iMazeCount = atoi(&cCount);

		fread(&cCount, 1, 1, pFile);

		//�� ����(iMazeCount)��ŭ �޸𸮸� �Ҵ��Ѵ�.
		pMazeList = new char* [iMazeCount];
		//�� ���� ���ϸ��� �����Ѵ�.
		for (int i = 0; i < iMazeCount; i++) {
			//���ϸ��� ���ڰ���
			int iNameCount = 0;
			//���ϸ��� �˳��ϰ� 256����Ʈ�� �迭�� �Ҵ��Ѵ�.
			pMazeList[i] = new char[256];
			//���� �ϳ��� �о ���๮�ڸ� �����Ͽ� �����Ѥ���
			while (true) {
				fread(&cCount, 1, 1, pFile);

				if (cCount != '\n') {
					pMazeList[i][iNameCount] = cCount;
					iNameCount++;
				}
				else
					break;
			}
			//�����̸��� ��� ������ ���ڿ��� �������� 0�� �־
			//���ڿ��� ���� �˷��ش�.
			pMazeList[i][iNameCount] = 0;
		}
		fclose(pFile);

		//���� ���� ����� ����������Ƿ� �� ������ �ϳ��� �����ؼ�
		//�̷θ� �о�ͼ� �����Ѵ�.

		for (int i = 0; i < iMazeCount; i++) {
			cout << i + 1 << ". " << pMazeList[i] << endl;
		}

		cout << "�̷θ� �����ϼ���. :";
		int iSelect;
		cin >> iSelect;

		fopen_s(&pFile, pMazeList[iSelect - 1], "rt");

		if (pFile) {
			//�̷��� ���� �� ����ŭ �ݺ��ϸ� �� �� ���� �о�´�.
			for (int i = 0; i < 20; i++) {
				fread(Maze[i], 1, 20, pFile);
				//��ǥ������ ���� ������, �������� ��츦
				//�и��Ѵ�
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
				cout << "��";
			else if (pPlayer->tPos.y == i && pPlayer->tPos.x == j)
				cout << "��";
			else if (Maze[i][j] == '0')
				cout << "��";
			else if (Maze[i][j] == '1')
				cout << "  ";
			else if (Maze[i][j] == '2')
				cout << "��";
			else if (Maze[i][j] == '3')
				cout << "��";
			else if (Maze[i][j] == '5')
				cout << "��";
			else if (Maze[i][j] == '6')
				cout << "��";
			else if (Maze[i][j] == '7')
				cout << "��";
		}
		cout << endl;
	}
	cout << "��ź�Ŀ� : " << pPlayer->iBombPower << endl;
	cout << "����� : ";
	if (pPlayer->bTransparency) {
		cout << "O\t";
		if (pPlayer->bTransparencyOn)
			cout << "ON\t";
		else
			cout << "OFF\t";
	}
	else
		cout << "X\t";

	cout << "���б� : ";
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
	//-1�� ���� ȭ���
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
	//-1�� ���� ȭ���
	if (pPlayer->tPos.x - 1 >= 0) {
		//������� �����Ҷ� ���� ���� ������� �̵�
		if (pPlayer->bTransparencyOn) {
			if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1], pPlayer))
				Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] = '1';
			pPlayer->tPos.x--;
			return;
		}
		//������� �Ұ����Ҷ� ���� ��� �Ұ���
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

					//���� �μ��� Ȯ���� ���� ������ ����

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

					//���� �μ��� Ȯ���� ���� ������ ����

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

					//���� �μ��� Ȯ���� ���� ������ ����
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

					//���� �μ��� Ȯ���� ���� ������ ����
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
	// 20 x 20 �̷θ� �����.
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

		//�̷θ� ���
		OutputMaze(strMaze, &tPlayer);

		if (tPlayer.tPos.x == tEndPos.x && tPlayer.tPos.y == tEndPos.y) {
			cout << " ���� " << endl;
			break;
		}

		cout << "w : ��   a : ��   s : ��   d : ��" << endl;
		cout << "t: ��ź��ġ   u : ����   i : ���б� ON/OFF   o : ����ȭ ON/OFF" << endl;
		cout << "q: ������" << endl;
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