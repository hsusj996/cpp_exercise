#include <iostream>
#include <time.h>

using namespace std;

enum GAME_MODE {
	GM_NONE,
	GM_NEW,
	GM_LOAD,
	GM_END
};

enum MAIN_MENU {
	MM_NONE,
	MM_MAP,
	MM_STORE,
	MM_INVENTORY,
	MM_EXIT
};

enum MAP_TYPE {
	MT_NONE,
	MT_EASY,
	MT_NORMAL,
	MT_HARD,
	MT_BACK
};

enum JOB {
	JOB_NONE,
	JOB_KNIGHT,
	JOB_ARCHER,
	JOB_WIZARD,
	JOB_END
};

enum BATTLE {
	BATTLE_NONE,
	BATTLE_ATTACK,
	BATTLE_BACK
};

enum ITEM_TYPE {
	IT_NONE,
	IT_WEAPON,
	IT_ARMOR,
	IT_BACK
};

enum STORE_MENU {
	SM_NONE,
	SM_WEAPON,
	SM_ARMOR,
	SM_BACK
};

enum EQUIP {
	EQ_WEAPON,
	EQ_ARMOR,
	EQ_MAX
};

#define NAME_SIZE 32
#define ITEM_DESC_LENGTH 512
#define INVENTORY_MAX 20
#define STORE_WEAPON_MAX 3
#define STORE_ARMOR_MAX 3
#define LEVEL_MAX 10

struct _tagItem {
	char strName[NAME_SIZE];
	char strTypeName[NAME_SIZE];
	ITEM_TYPE eType;
	int iMin;
	int iMax;
	int iPrice;
	int iSell;
	char strDesc[ITEM_DESC_LENGTH];
};

struct _taginventory {
	_tagItem tItem[INVENTORY_MAX];
	int iItemCount;
	int iGold;
};

struct _tagPlayer {
	char strName[NAME_SIZE];
	char strJobName[NAME_SIZE];
	JOB eJob;
	int iAttackMin, iAttackMax;
	int iArmorMin, iArmorMax;
	int iHP;
	int iHPMax;
	int iMP;
	int iMPMax;
	int iExp;
	int iLevel;
	_tagItem tEquip[EQ_MAX];
	bool bEquip[EQ_MAX];
	_taginventory tInventory;
};

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

struct _tagLevelupStatus {
	int iAttackMin;
	int iAttackMax;
	int iArmorMin;
	int iArmorMax;
	int iHpMin;
	int iHpMax;
	int iMpMin;
	int iMpMax;
};

const int g_iLevelUpExp[LEVEL_MAX] = { 4000,10000,20000,35000,50000,70000,100000,150000,200000,400000 };
_tagLevelupStatus g_tLvUpTable[JOB_END - 1] = {};

//숫자 입력을 받고, 오류처리 (INT_MAX -> 오류)
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

int OutputMainMenu() {
	system("cls");
	cout << "****************************로비****************************\n";
	cout << "1. 맵" << endl;
	cout << "2. 상점" << endl;
	cout << "3. 가방" << endl;
	cout << "4. 종료" << endl;
	cout << "메뉴를 선택하세요 : ";
	int iMenu = InputInt();

	if (iMenu == INT_MAX || iMenu <= MM_NONE || iMenu > MM_EXIT) {
		return MM_NONE;
	}
	return iMenu;
}

int OutputMapMenu() {
	system("cls");
	cout << "****************************맵****************************\n";
	cout << "1. 쉬움" << endl;
	cout << "2. 보통" << endl;
	cout << "3. 어려움" << endl;
	cout << "4. 뒤로가기" << endl;
	cout << "맵을 선택하세요 : ";
	int iMenu = InputInt();

	if (iMenu == INT_MAX || iMenu <= MT_NONE || iMenu > MT_BACK) {
		return MT_NONE;
	}
	return iMenu;
}

void OutputBattleTag(int iMenu) {
	switch (iMenu) {
	case MT_EASY:
		cout << "****************************쉬움****************************\n";
		break;
	case MT_NORMAL:
		cout << "****************************보통****************************\n";
		break;
	case MT_HARD:
		cout << "****************************어려움****************************\n";
		break;
	}
}

void OutputPlayer(_tagPlayer* pPlayer) {
	cout << "======================Player======================" << endl;
	cout << "이름 : " << pPlayer->strName << "\t직업 : " <<
		pPlayer->strJobName << endl;
	cout << "레벨 : " << pPlayer->iLevel << "\t경험치 : " <<
		pPlayer->iExp << " / " << g_iLevelUpExp[pPlayer->iLevel - 1] << endl;

	if (pPlayer->bEquip[EQ_WEAPON] == true) {
		cout << "공격력 : " << pPlayer->iAttackMin << " + " <<
			pPlayer->tEquip[EQ_WEAPON].iMin << " - " <<
			pPlayer->iAttackMax << " + " << pPlayer->tEquip[EQ_WEAPON].iMax;
	}
	else {
		cout << "공격력 : " << pPlayer->iAttackMin << " - " <<
			pPlayer->iAttackMax;
	}

	if (pPlayer->bEquip[EQ_ARMOR] == true) {
		cout << "\t방어력 : " << pPlayer->iArmorMin << " + " <<
			pPlayer->tEquip[EQ_ARMOR].iMin << " - " <<
			pPlayer->iArmorMax << " + " << pPlayer->tEquip[EQ_ARMOR].iMax << endl;
	}
	else {
		cout << "\t방어력 : " << pPlayer->iArmorMin << " - " <<
			pPlayer->iArmorMax << endl;
	}

	cout << "체력 : " << pPlayer->iHP << " / " << pPlayer->iHPMax <<
		"\t마나 : " << pPlayer->iMP << " / " << pPlayer->iMPMax << endl;

	if (pPlayer->bEquip[EQ_WEAPON])
		cout << "장착무기 : " << pPlayer->tEquip[EQ_WEAPON].strName;
	else
		cout << "장착무기 : 없음";

	if (pPlayer->bEquip[EQ_ARMOR])
		cout << "\t장착방어구 : " << pPlayer->tEquip[EQ_ARMOR].strName << endl;
	else
		cout << "\t장착방어구 : 없음" << endl;

	cout << "보유골드 : " << pPlayer->tInventory.iGold << "Gold" << endl;
}

void OutputMonster(_tagMonster *pMonster) {
	cout << "======================Monster======================" << endl;
	cout << "이름 : " << pMonster->strName << "\t레벨  " <<
		pMonster->iLevel << endl;
	cout << "공격력 : " << pMonster->iAttackMin << " - " <<
		pMonster->iAttackMax << "\t방어력 : " << pMonster->iArmorMin <<
		" - " << pMonster->iArmorMax << endl;
	cout << "체력 : " << pMonster->iHP << " / " << pMonster->iHPMax <<
		"\t마나" << pMonster->iMP << " / " << pMonster->iMPMax << endl;
	cout << "획득 경험치 : " << pMonster->iExp << "\t획득 골드 : " <<
		pMonster->iGoldMin << " - " << pMonster->iGoldMax << endl << endl;
}

int OutputBattleMenu() {
	cout << "1. 공격" << endl;
	cout << "2. 도망가기" << endl;
	cout << "메뉴를 선택하세요 : ";
	int iMenu = InputInt();

	if (iMenu == INT_MAX || iMenu <= BATTLE_NONE || iMenu > BATTLE_BACK)
		return BATTLE_NONE;

	return iMenu;
}

void Battle(_tagPlayer* pPlayer, _tagMonster* pMonster) {
	int iAttackMin = pPlayer->iAttackMin;
	int iAttackMax = pPlayer->iAttackMax;

	if (pPlayer->bEquip[EQ_WEAPON]) {
		iAttackMin += pPlayer->tEquip[EQ_WEAPON].iMin;
		iAttackMax += pPlayer->tEquip[EQ_WEAPON].iMax;
	}

	int iAttack = rand() % (iAttackMax - iAttackMin + 1) +
		iAttackMin;
	int iArmor = rand() % (pMonster->iArmorMax - pMonster->iArmorMin + 1) +
		pMonster->iArmorMin;

	int iDamage = iAttack - iArmor;
	//삼항연산자 : 조건식 ? true일때 값 : false 일때 값
	iDamage = iDamage < 1 ? 1 : iDamage;

	//몬스터 hp를 감소시킨다.
	pMonster->iHP -= iDamage;
	cout << pPlayer->strName << " 가 " << pMonster->strName << "에게 "
		<< iDamage << " 피해를 입혔습니다. " << endl;

	//몬스터가 죽었을 경우를 처리한다.
	if (pMonster->iHP <= 0) {
		cout << pMonster->strName << " 몬스터가 사망하였습니다." << endl;

		pPlayer->iExp += pMonster->iExp;
		int iGold = (rand() % (pMonster->iGoldMax - pMonster->iGoldMin + 1) +
			pMonster->iGoldMin);
		pPlayer->tInventory.iGold += iGold;

		cout << pMonster->iExp << "경험치를 획득하였습니다." << endl;
		cout << iGold << " Gold를 획득하였습니다. " << endl;

		pMonster->iHP = pMonster->iHPMax;
		pMonster->iMP = pMonster->iMPMax;

		if (pPlayer->iExp >= g_iLevelUpExp[pPlayer->iLevel - 1]) {
			pPlayer->iExp -= g_iLevelUpExp[pPlayer->iLevel - 1];
			pPlayer->iLevel++;

			cout << "레벨업 하였습니다." << endl;

			int iJobIndex = pPlayer->eJob - 1;
			int iHPUp = rand() % (g_tLvUpTable[iJobIndex].iHpMax - g_tLvUpTable[iJobIndex].iHpMin + 1);
			int iMpUp = rand() % (g_tLvUpTable[iJobIndex].iMpMax - g_tLvUpTable[iJobIndex].iMpMin + 1);
			pPlayer->iAttackMin += g_tLvUpTable[iJobIndex].iAttackMin;
			pPlayer->iAttackMax += g_tLvUpTable[iJobIndex].iAttackMax;
			pPlayer->iArmorMin += g_tLvUpTable[iJobIndex].iArmorMin;
			pPlayer->iArmorMax += g_tLvUpTable[iJobIndex].iArmorMax;

			pPlayer->iHP += iHPUp;
			pPlayer->iMP += iMpUp;
		}
		return;
	}
	//몬스터가 플레이어를 공격한다.
	iAttack = rand() % (pMonster->iAttackMax - pMonster->iAttackMin + 1) +
		pMonster->iAttackMin;

	int iArmorMin = pPlayer->iArmorMin;
	int iArmorMax = pPlayer->iArmorMax;

	if (pPlayer->bEquip[EQ_ARMOR]) {
		iArmorMin += pPlayer->tEquip[EQ_ARMOR].iMin;
		iArmorMax += pPlayer->tEquip[EQ_ARMOR].iMax;
	}

	iArmor = rand() % (iArmorMax - iArmorMin + 1) + iArmorMin;

	iDamage = iAttack - iArmor;
	//삼항연산자 : 조건식 ? true일때 값 : false 일때 값
	iDamage = iDamage < 1 ? 1 : iDamage;

	//플레이어 hp를 감소시킨다.
	pPlayer->iHP -= iDamage;
	cout << pMonster->strName << " 가 " << pPlayer->strName << "에게 "
		<< iDamage << " 피해를 입혔습니다. " << endl;

	//플레이어가 죽었을 경우
	if (pPlayer->iHP <= 0) {
		cout << pPlayer->strName << " 플레이어가 사망하였습니다." << endl;

		int iExp = pPlayer->iExp * 0.1f;
		int iGold = pPlayer->tInventory.iGold * 0.1f;

		pPlayer->iExp -= iExp;
		pPlayer->tInventory.iGold -= iGold;

		cout << iExp << " 경험치를 잃었습니다." << endl;
		cout << iGold << " 골드를 잃었습니다." << endl;

		pPlayer->iHP = pPlayer->iHPMax;
		pPlayer->iMP = pPlayer->iMPMax;

		return;
	}
}

void RunBattle(_tagPlayer* pPlayer, _tagMonster* pMonsterArr,
	int iMenu) {
	_tagMonster tMonster = pMonsterArr[iMenu - 1];
	bool bLoop = true;
	while (bLoop) {
		system("cls");
		OutputBattleTag(iMenu);

		OutputPlayer(pPlayer);

		OutputMonster(&tMonster);

		switch (OutputBattleMenu()) {
		case BATTLE_ATTACK:
			Battle(pPlayer, &tMonster);
			system("pause");
			break;
		case BATTLE_BACK:
			bLoop = false;

			break;
		}
	}
}

void RunMap(_tagPlayer *pPlayer, _tagMonster *pMonster) {
	bool bLoop = true;

	while (bLoop) {
		int iMenu = OutputMapMenu();

		if (iMenu == MT_BACK)
			return;
	
		if (iMenu == MT_NONE)
			continue;

		//전투를 시작한다.
		RunBattle(pPlayer, pMonster, iMenu);
	}
}

int SelectJob() {
	int iJob = JOB_NONE;
	while (iJob == JOB_NONE) {
		system("cls");
		cout << "1. 기사" << endl;
		cout << "2. 궁수" << endl;
		cout << "3. 마법사" << endl;
		cout << "직업을 선택하세요 : ";
		iJob = InputInt();

		//열거체에 직업을 추가할때 오류발생 조건을 아래와 같이하면
		//따로 수정할 필요가 없다.
		if (iJob <= JOB_NONE || iJob >= JOB_END) {
			iJob = JOB_NONE;
		}
	}
	return iJob;
}
//파일이 정상적인지 알기위해 bool사용
bool LoadPlayer(_tagPlayer* pPlayer) {
	FILE* pFile = NULL;

	fopen_s(&pFile, "Player.ply", "rb");

	if (pFile) {
		//이름인 경우 char형 배열이기 떄문에 변수명이 메모리 주소가 된다.
		fread(pPlayer->strName, 1, NAME_SIZE, pFile);
		//열거체는 4byte로 설정
		fread(&pPlayer->eJob, sizeof(JOB), 1, pFile);
		fread(pPlayer->strJobName, 1, NAME_SIZE, pFile);
		//플레이어 스탯을 읽어온다.
		fread(&pPlayer->iAttackMin, 4,1, pFile);
		fread(&pPlayer->iAttackMax, 4, 1, pFile);
		fread(&pPlayer->iArmorMin, 4, 1, pFile);
		fread(&pPlayer->iArmorMax, 4, 1, pFile);
		fread(&pPlayer->iHP, 4, 1, pFile);
		fread(&pPlayer->iHPMax, 4, 1, pFile);
		fread(&pPlayer->iMP, 4, 1, pFile);
		fread(&pPlayer->iMPMax, 4, 1, pFile);
		//경험치와 레벨을 읽어온다.
		fread(&pPlayer->iExp, 4, 1, pFile);
		fread(&pPlayer->iLevel, 4, 1, pFile);
		//무기아이템 착용여부를 읽어온다.
		fread(&pPlayer->bEquip[EQ_WEAPON], 1, 1, pFile);
		//만약 저장할때 무기를 차고 있었다면 해당 무기정보도
		//같이 저장이 되었다. 그러므로 여기서 차고 있을 경우
		//읽어야 한다.
		if (pPlayer->bEquip[EQ_WEAPON])
			fread(&pPlayer->tEquip[EQ_WEAPON], sizeof(_tagItem), 1, pFile);
		
		//방어구도 무기와 마찬가지
		fread(&pPlayer->bEquip[EQ_ARMOR], 1, 1, pFile);
		if (pPlayer->bEquip[EQ_ARMOR])
			fread(&pPlayer->tEquip[EQ_ARMOR], sizeof(_tagItem), 1, pFile);

		//골드를 읽어온다. 
		fread(&pPlayer->tInventory.iGold, 4, 1, pFile);
		//인벤토리 아이템 수를 읽어온다.
		fread(&pPlayer->tInventory.iItemCount, 4, 1, pFile);
		//읽어온 아이템 수 만큼 인벤토리에 아이템정보를 읽어온다.
		fread(pPlayer->tInventory.tItem, sizeof(_tagItem),
			pPlayer->tInventory.iItemCount, pFile);

		fclose(pFile);
		return true;
	}

	return false;
}

bool SavePlayer(_tagPlayer* pPlayer) {
	FILE* pFile = NULL;
	fopen_s(&pFile, "Player.ply", "wb");
	if (pFile) {
		//이름인 경우 char형 배열이기 떄문에 변수명이 메모리 주소가 된다.
		fwrite(pPlayer->strName, 1, NAME_SIZE, pFile);
		//열거체는 4byte로 설정
		fwrite(&pPlayer->eJob, sizeof(JOB), 1, pFile);
		fwrite(pPlayer->strJobName, 1, NAME_SIZE, pFile);
		//플레이어 스탯을 저장.
		fwrite(&pPlayer->iAttackMin, 4, 1, pFile);
		fwrite(&pPlayer->iAttackMax, 4, 1, pFile);
		fwrite(&pPlayer->iArmorMin, 4, 1, pFile);
		fwrite(&pPlayer->iArmorMax, 4, 1, pFile);
		fwrite(&pPlayer->iHP, 4, 1, pFile);
		fwrite(&pPlayer->iHPMax, 4, 1, pFile);
		fwrite(&pPlayer->iMP, 4, 1, pFile);
		fwrite(&pPlayer->iMPMax, 4, 1, pFile);
		//경험치와 레벨을 저장
		fwrite(&pPlayer->iExp, 4, 1, pFile);
		fwrite(&pPlayer->iLevel, 4, 1, pFile);
		//무기아이템 착용여부를 저장
		fwrite(&pPlayer->bEquip[EQ_WEAPON], 1, 1, pFile);
		//만약 저장할때 무기를 차고 있었다면 해당 무기정보도
		//같이 저장이 되었다. 그러므로 여기서 차고 있을 경우
		//저장.
		if (pPlayer->bEquip[EQ_WEAPON])
			fwrite(&pPlayer->tEquip[EQ_WEAPON], sizeof(_tagItem), 1, pFile);

		//방어구도 무기와 마찬가지
		fwrite(&pPlayer->bEquip[EQ_ARMOR], 1, 1, pFile);
		if (pPlayer->bEquip[EQ_ARMOR])
			fwrite(&pPlayer->tEquip[EQ_ARMOR], sizeof(_tagItem), 1, pFile);

		//골드를 저장
		fwrite(&pPlayer->tInventory.iGold, 4, 1, pFile);
		//인벤토리 아이템 수를 저장
		fwrite(&pPlayer->tInventory.iItemCount, 4, 1, pFile);
		//읽어온 아이템 수 만큼 인벤토리에 아이템정보를 저장
		fwrite(pPlayer->tInventory.tItem, sizeof(_tagItem),
			pPlayer->tInventory.iItemCount, pFile);

		fclose(pFile);
		return true;
	}
	return false;
}

void SetPlayer(_tagPlayer *pPlayer) {
	system("cls");
	cin.clear();
	cin.ignore(1024, '\n');

	cout << "이름 : ";
	cin.getline(pPlayer->strName, NAME_SIZE - 1); //문자열의 끝은 null이어야 하기 때문에 -1

	pPlayer->eJob = (JOB)SelectJob();
	pPlayer->iLevel = 1;
	pPlayer->iExp = 0;
	pPlayer->tInventory.iGold = 10000;

	switch (pPlayer->eJob) {
	case JOB_KNIGHT:
		strcpy_s(pPlayer->strJobName, "기사");
		pPlayer->iAttackMax = 10;
		pPlayer->iArmorMin = 15;
		pPlayer->iArmorMax = 20;
		pPlayer->iHPMax = 500;
		pPlayer->iHP = 500;
		pPlayer->iMP = 100;
		pPlayer->iAttackMin = 5;
		pPlayer->iMPMax = 100;
		break;
	case JOB_ARCHER:
		strcpy_s(pPlayer->strJobName, "궁수");
		pPlayer->iAttackMin = 10;
		pPlayer->iAttackMax = 15;
		pPlayer->iArmorMin = 10;
		pPlayer->iArmorMax = 15;
		pPlayer->iHP = 400;
		pPlayer->iHPMax = 400;
		pPlayer->iMP = 200;
		pPlayer->iMPMax = 200;
		break;
	case JOB_WIZARD:
		strcpy_s(pPlayer->strJobName, "마법사");
		pPlayer->iAttackMin = 15;
		pPlayer->iAttackMax = 20;
		pPlayer->iArmorMin = 5;
		pPlayer->iArmorMax = 10;
		pPlayer->iHPMax = 300;
		pPlayer->iHP = 300;
		pPlayer->iMP = 300;
		pPlayer->iMPMax = 300;
		break;
	}
}

_tagMonster CreateMonster(const char *pName,int iAttackMin,
	int iAttackMax, int iArmorMin, int iArmorMax, int iHP,
	int iMP, int iLevel, int iExp, int iGoldMin, int iGoldMax) {
	_tagMonster tMonster = {};

	strcpy_s(tMonster.strName, pName);
	tMonster.iAttackMin = iAttackMin;
	tMonster.iAttackMax = iAttackMax;
	tMonster.iArmorMin = iArmorMin;
	tMonster.iArmorMax = iArmorMax;
	tMonster.iHP = iHP;
	tMonster.iHPMax = iHP;
	tMonster.iMP = iMP;
	tMonster.iMPMax = iMP;
	tMonster.iLevel = iLevel;
	tMonster.iExp = iExp;
	tMonster.iGoldMin = iGoldMin;
	tMonster.iGoldMax = iGoldMax;

	return tMonster;
}

void SetMonster(_tagMonster* pMonsterArr) {
	FILE* pFile = NULL;

	fopen_s(&pFile, "Monster.mst", "rb");

	if (pFile) {
		fread(pMonsterArr, sizeof(_tagMonster), MT_BACK - 1, pFile);
		fclose(pFile);
	}

	//pMonsterArr[0] = CreateMonster("고블린", 20, 30, 2, 5,
	//	100, 10, 1, 1000, 500, 1500);
	//pMonsterArr[1] = CreateMonster("트롤", 80, 130, 60, 90,
	//	2000, 100, 5, 7000, 6000, 8000);
	//pMonsterArr[2] = CreateMonster("드래곤", 250, 500, 200, 400,
	//	30000, 20000, 10, 30000, 20000, 50000 );

	
}

_tagLevelupStatus CreateLvUpStatus(int iAttackMin, int iAttackMax,
	int iArmorMin, int iArmorMax, int iHPMin, int iHPMax,
	int iMPMin, int iMPMax) {
	_tagLevelupStatus tStatus = {};

	tStatus.iAttackMin = iAttackMin;
	tStatus.iAttackMax = iAttackMax;
	tStatus.iArmorMin = iArmorMin;
	tStatus.iArmorMax = iArmorMax;
	tStatus.iHpMin = iHPMax;
	tStatus.iHpMax = iHPMax;
	tStatus.iMpMin = iMPMin;
	tStatus.iMpMax = iMPMax;

	return tStatus;
}

int OutputStoreMenu() {
	system("cls");
	cout << "======================상점======================" << endl;
	cout << "1. 무기상점" << endl;
	cout << "2. 방어구상점" << endl;
	cout << "3. 뒤로가기" << endl;
	cout << "상점을 선택하세요 : ";
	int iMenu = InputInt();

	if (iMenu <= SM_NONE || iMenu > SM_BACK)
		return SM_NONE;

	return iMenu;
}

int OutputStoreItemList(_taginventory* pInventory, _tagItem* pStore,
	int iItemCount) {
	system("cls");
	for (int i = 0; i < iItemCount; i++) {
		cout << i + 1 << ". " <<  pStore[i].strName << endl;
		cout << "사용가능 직업 : " << pStore[i].strTypeName << endl;
		cout << "공격력 : " << pStore[i].iMin << " - " << pStore[i].iMax << endl;
		cout << "설명 : " << pStore[i].strDesc << endl;
		cout << "가격 : " << pStore[i].iPrice << endl;
		cout << "==================================================" << endl;
	}
	cout << iItemCount + 1 << ". 뒤로가기" << endl;
	cout << "보유금액 : " << pInventory->iGold << " Gold" << endl;
	cout << "남은공간 : " << INVENTORY_MAX - pInventory->iItemCount << endl;
	cout << "구입할 아이템을 선택하세요. : ";
	int iMenu = InputInt();

	if (iMenu < 1 || iMenu > iItemCount + 1)
		return INT_MAX;

	return iMenu;
}

void BuyItem(_taginventory* pInventory, _tagItem* pStore,
	int iItemCount, int iStoreType) {
	while (true) {
		system("cls");
		switch (iStoreType) {
		case SM_WEAPON:
			cout << "******************** 무기상점 ***********************";
			break;
		case SM_ARMOR:
			cout << "******************** 방어구상점 **********************";
			break;
		}
		int iInput = OutputStoreItemList(pInventory, pStore, iItemCount);

		if (iInput == INT_MAX) {
			cout << "잘못 입력하였습니다." << endl;
			system("pause");
			continue;
		}
		else if (iInput == iItemCount + 1)
			break;

		int iIndex = iInput - 1;

		if (pInventory->iItemCount == INVENTORY_MAX) {
			cout << "가방이 꽉 찼습니다." << endl;
			system("pause"); 
			continue;
		}
		else if (pInventory->iGold < pStore[iIndex].iPrice) {
			cout << "보유 금액이 부족합니다. " << endl;
			system("pause");
			continue;
		}

		pInventory->tItem[pInventory->iItemCount] = pStore[iIndex];
		pInventory->iItemCount++;

		pInventory->iGold -= pStore[iIndex].iPrice;

		cout << pStore[iIndex].strName << " 아이템을 구매하였습니다." << endl;
		system("pause");
	}
}

void RunStore(_taginventory* pInventory,_tagItem *pWeapon,
	_tagItem *pArmor) {
	while (true) {
		switch (OutputStoreMenu()) {
		case SM_WEAPON:
			BuyItem(pInventory, pWeapon, STORE_WEAPON_MAX, SM_WEAPON);
			break;
		case SM_ARMOR:
			BuyItem(pInventory, pArmor, STORE_ARMOR_MAX, SM_ARMOR);
			break;
		case SM_BACK:
			return;
		}
	}
}

_tagItem CreateItem(const char* pName, ITEM_TYPE eType, int iMin,
	int iMax, int iPrice, int iSell, const char* pDesc) {
	_tagItem tItem = {};

	strcpy_s(tItem.strName, pName);
	strcpy_s(tItem.strDesc, pDesc);

	tItem.eType = eType;

	switch (eType) {
	case IT_WEAPON:
		strcpy_s(tItem.strTypeName, "무기");
		break;
	case IT_ARMOR:
		strcpy_s(tItem.strTypeName, "방어구");
		break;
	}

	tItem.iMin = iMin;
	tItem.iMax = iMax;
	tItem.iPrice = iPrice;
	tItem.iSell = iSell;

	return tItem;
}

int OutputInventory(_tagPlayer* pPlayer) {
	system("cls");
	cout << "************************* 가방 ****************************" << endl;

	OutputPlayer(pPlayer);
	cout << endl << endl;


	for (int i = 0; i < pPlayer->tInventory.iItemCount; i++) {
		cout << i + 1 << ". 이름  : " << pPlayer->tInventory.tItem[i].strName <<
			"\t종류 : " << pPlayer->tInventory.tItem[i].strTypeName << endl;
		cout << "공격력 : " << pPlayer->tInventory.tItem[i].iMin << " - " <<
			pPlayer->tInventory.tItem[i].iMax << endl;
		cout << "판매가격 : " << pPlayer->tInventory.tItem[i].iPrice <<
			"\t구매가격 : " << pPlayer->tInventory.tItem[i].iSell << endl;
		cout << "설명 : " << pPlayer->tInventory.tItem[i].strDesc << endl << endl;
	}

	cout << pPlayer->tInventory.iItemCount + 1 << ". 뒤로가기" << endl;
	cout << "장착할 아이템을 선택하세요. : ";
	
	int iMenu = InputInt();

	if (iMenu < 1 || iMenu > pPlayer->tInventory.iItemCount + 1)
		return INT_MAX;

	return iMenu;
}

EQUIP ComputeEquipType(ITEM_TYPE eType) {
	EQUIP eq;

	switch (eType) {
	case IT_WEAPON:
		eq = EQ_WEAPON;
		break;
	case IT_ARMOR:
		eq = EQ_ARMOR;
		break;
	}
	return eq;
}

void RunInventory(_tagPlayer* pPlayer) {
	while (true) {
		int iInput = OutputInventory(pPlayer);

		if (iInput == INT_MAX)
			continue;
		else if (iInput == pPlayer->tInventory.iItemCount + 1)
			break;
		else {
			int idx = iInput - 1;

			EQUIP eq = ComputeEquipType(pPlayer->tInventory.tItem[idx].eType);

			if (pPlayer->bEquip[eq] == true) {
				_tagItem tSwap = pPlayer->tEquip[eq];
				pPlayer->tEquip[eq] = pPlayer->tInventory.tItem[idx];
				pPlayer->tInventory.tItem[idx] = tSwap;
			}

			else {
				pPlayer->tEquip[eq] = pPlayer->tInventory.tItem[idx];

				for (int i = idx; i < pPlayer->tInventory.iItemCount - 1; i++) {
					pPlayer->tInventory.tItem[i] = pPlayer->tInventory.tItem[i + 1];
				}

				pPlayer->tInventory.iItemCount--;

				pPlayer->bEquip[eq] = true;
			}
			cout << pPlayer->tEquip[eq].strName << " 아이템을 장착하였습니다." << endl;

			system("pause");
		}
	}
}

int main() {
	srand((unsigned int)time(0));

	_tagPlayer tPlayer = {};

	int iGameMode = 0;

	while (iGameMode <= GM_NONE || iGameMode > GM_END) {
		system("cls");
		cout << "1. 새로하기" << endl;
		cout << "2. 이어하기" << endl;
		cout << "3. 종료" << endl;
		cout << "게임모드를 선택하세요. : ";
		iGameMode = InputInt();
	}
	if (iGameMode == GM_END)
		return 0;

	switch (iGameMode) {
	case GM_NEW:
		SetPlayer(&tPlayer);
		break;
	case GM_LOAD:
		if (!LoadPlayer(&tPlayer)) {
			cout << "플레이어 파일 오류!!" << endl;
			return 0;
		}
		break;
	}

	_tagMonster tMonsterArr[MT_BACK - 1] = {};

	SetMonster(tMonsterArr);

	g_tLvUpTable[JOB_KNIGHT - 1] = CreateLvUpStatus(4, 10, 8, 16, 50, 100, 10, 20);
	g_tLvUpTable[JOB_ARCHER - 1] = CreateLvUpStatus(10, 15, 5, 10, 30, 60, 30, 50);
	g_tLvUpTable[JOB_WIZARD - 1] = CreateLvUpStatus(15, 20, 3, 7, 20, 40, 50, 100);

	//상점에서 판매할 아이템 목록을 생성한다.
	_tagItem tStoreWeapon[STORE_WEAPON_MAX] = {};
	_tagItem tStoreArmor[STORE_ARMOR_MAX] = {};

	tStoreWeapon[0] = CreateItem("목검", IT_WEAPON, 5, 10,
		1000, 500, "나무로 만든 칼");
	tStoreWeapon[1] = CreateItem("장궁", IT_WEAPON, 20, 10,
		7000, 3500, "짱짱한 활");
	tStoreWeapon[2] = CreateItem("지팡이", IT_WEAPON, 90, 150,
		30000, 15000, "나무로 만든 지팡이");

	tStoreArmor[0] = CreateItem("천갑옷", IT_ARMOR, 2, 5,
		1000, 500, "천으로 만든 허접한 갑옷");
	tStoreArmor[1] = CreateItem("가죽갑옷", IT_ARMOR, 10, 20,
		7000, 3500, "동물 가죽으로 만든 질긴 갑옷");
	tStoreArmor[2] = CreateItem("풀플레이트아머", IT_ARMOR, 70, 90,
		30000, 15000, "강철로 만든 판금갑옷");

	bool bLoop = true;

	while (bLoop) {
		switch (OutputMainMenu()) {
		case MM_MAP:
			RunMap(&tPlayer, tMonsterArr);
			break;
		case MM_STORE:
			RunStore(&tPlayer.tInventory, tStoreWeapon, tStoreArmor);
			break;
		case MM_INVENTORY:
			RunInventory(&tPlayer);
			break;
		case MM_EXIT:
			bLoop = false;
			break;
		}
	}
	SavePlayer(&tPlayer);
	cout << "저장완료!" << endl;
	system("pause");

	return 0;
}