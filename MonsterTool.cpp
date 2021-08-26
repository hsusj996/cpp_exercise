#include <iostream>

using namespace std;

enum MAP_TYPE {
	MT_EASY,
	MT_NORMAL,
	MT_HARD,
	MT_END
};

enum MAIN_MENU {
	MM_NONE,
	MM_ADD,
	MM_LOAD,
	MM_SAVE,
	MM_OUTPUT,
	MM_EXIT
};

#define NAME_SIZE 32

struct _tagMonster {
	char strName[NAME_SIZE];
	int iAttackMin, iAttackMax;
	int iArmorMin, iArmorMax;
	int iHP, iHPMax;
	int iMP, iMPMax;
	int iLevel;
	int iExp;
	int iGoldMin, iGoldMax;
};

int InputInt() {
	int iInput;
	cin >> iInput;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(1024, '\n');
		return INT_MAX; //오류를 반환
	}
	return iInput;
}

void AddMonster(_tagMonster* pMonsterArr) {
	int iMap = 0;
	system("cls");
	while (true) {
		system("cls");
		cout << "1. 쉬움" << endl;
		cout << "2. 보통" << endl;
		cout << "3. 어려움" << endl;
		cout << "추가할 난이도를 선택하세요. : ";
		iMap = InputInt();

		if (iMap == 4)
			return;
		else if (iMap < 1 || iMap > 4)
			continue;

		//1부터 시작이기 때문에 1을 감소시켜야 사냥터 인덱스가
		// 된다.
		--iMap;
		break;
	}

	cin.clear();
	cin.ignore(1024, '\n');

	//몬스터 이름을 입력받는다.
	cout << "이름 : ";
	cin.getline(pMonsterArr[iMap].strName, NAME_SIZE);
	//스탯을 입력받는다.
	cout << "최소공격력 :";
	pMonsterArr[iMap].iAttackMin = InputInt();
	cout << "최대공격력 :";
	pMonsterArr[iMap].iAttackMax = InputInt();
	cout << "최소방어력 :";
	pMonsterArr[iMap].iArmorMin = InputInt();
	cout << "최대방어력 :";
	pMonsterArr[iMap].iArmorMax = InputInt();
	cout << "최대 체력 :";
	pMonsterArr[iMap].iHPMax = InputInt();
	pMonsterArr[iMap].iHP = pMonsterArr[iMap].iHPMax;
	cout << "최대 마나 :";
	pMonsterArr[iMap].iMPMax = InputInt();
	pMonsterArr[iMap].iMP = pMonsterArr[iMap].iMPMax;
	cout << "레벨 :";
	pMonsterArr[iMap].iLevel = InputInt();
	cout << "획득 경험치 :";
	pMonsterArr[iMap].iExp = InputInt();
	cout << "최소 골드 :";
	pMonsterArr[iMap].iGoldMin = InputInt();
	cout << "최대 골드 :";
	pMonsterArr[iMap].iGoldMax = InputInt();
}

bool SaveMonster(_tagMonster* pMonsterArr) {
	FILE* pFile = NULL;

	fopen_s(&pFile, "Monster.mst", "wb");
	if (pFile) {
		fwrite(pMonsterArr, sizeof(_tagMonster), MT_END, pFile);
		fclose(pFile);
		return true;
	}
	return false;
}

bool LoadMonster(_tagMonster* pMonsterArr) {
	FILE* pFile = NULL;

	fopen_s(&pFile, "Monster.mst", "rb");

	if (pFile) {
		fread(pMonsterArr, sizeof(_tagMonster), MT_END, pFile);
		return true;
	}
	return false;
}

void OutputMonster(_tagMonster* pMonsterArr) {
	system("cls");
	cout << "======================Monster======================" << endl;
	for (int i = 0; i < MT_END; i++) {
		
		cout << "이름 : " << pMonsterArr[i].strName << "\t레벨  " <<
			pMonsterArr[i].iLevel << endl;
		cout << "공격력 : " << pMonsterArr[i].iAttackMin << " - " <<
			pMonsterArr[i].iAttackMax << "\t방어력 : " << pMonsterArr[i].iArmorMin <<
			" - " << pMonsterArr[i].iArmorMax << endl;
		cout << "체력 : " << pMonsterArr[i].iHP << " / " << pMonsterArr[i].iHPMax <<
			"\t마나" << pMonsterArr[i].iMP << " / " << pMonsterArr[i].iMPMax << endl;
		cout << "획득 경험치 : " << pMonsterArr[i].iExp << "\t획득 골드 : " <<
			pMonsterArr[i].iGoldMin << " - " << pMonsterArr[i].iGoldMax << endl << endl;
	}
	system("pause");
}

int main() {
	_tagMonster tMonster[MT_END] = {};

	while (true) {
		system("cls");
		cout << "1. 몬스터 추가" << endl;
		cout << "2. 읽어오기" << endl;
		cout << "3. 저장" << endl;
		cout << "4. 몬스터 출력" << endl;
		cout << "5. 종료" << endl;
		cout << "메뉴를 선택하세요. " << endl;
		int iMenu = InputInt();

		if (iMenu == MM_EXIT)
			break;
		switch (iMenu) {
		case MM_ADD:
			AddMonster(tMonster);
			break;
		case MM_LOAD:
			LoadMonster(tMonster);
			break;
		case MM_SAVE:
			SaveMonster(tMonster);
			break;
		case MM_OUTPUT:
			OutputMonster(tMonster);
			break;
			
		}
	}

	//자동저장기능
	SaveMonster(tMonster);
	return 0;
}