#include <iostream>
#include <time.h>
#include <string.h>
using namespace std;

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

int main() {
	srand((unsigned int)time(0));

	const int iLevelUpExp[LEVEL_MAX] = { 4000,10000,20000,35000,50000,70000,100000,150000,200000,400000 };

	_tagLevelupStatus tLvUpTable[JOB_END - 1] = {};


	tLvUpTable[JOB_KNIGHT - 1].iAttackMin = 4;
	tLvUpTable[JOB_KNIGHT - 1].iAttackMax = 10;
	tLvUpTable[JOB_KNIGHT - 1].iArmorMin = 8;
	tLvUpTable[JOB_KNIGHT - 1].iArmorMax = 16;
	tLvUpTable[JOB_KNIGHT - 1].iHpMin = 50;
	tLvUpTable[JOB_KNIGHT - 1].iHpMax = 100;
	tLvUpTable[JOB_KNIGHT - 1].iMpMin = 10;
	tLvUpTable[JOB_KNIGHT - 1].iMpMax = 20;

	tLvUpTable[JOB_ARCHER - 1].iAttackMin = 10;
	tLvUpTable[JOB_ARCHER - 1].iAttackMax = 15;
	tLvUpTable[JOB_ARCHER - 1].iArmorMin = 5;
	tLvUpTable[JOB_ARCHER - 1].iArmorMax = 10;
	tLvUpTable[JOB_ARCHER - 1].iHpMin = 30;
	tLvUpTable[JOB_ARCHER - 1].iHpMax = 60;
	tLvUpTable[JOB_ARCHER - 1].iMpMin = 30;
	tLvUpTable[JOB_ARCHER - 1].iMpMax = 50;

	tLvUpTable[JOB_WIZARD - 1].iAttackMin = 15;
	tLvUpTable[JOB_WIZARD - 1].iAttackMax = 20;
	tLvUpTable[JOB_WIZARD - 1].iArmorMin = 3;
	tLvUpTable[JOB_WIZARD - 1].iArmorMax = 7;
	tLvUpTable[JOB_WIZARD - 1].iHpMin = 20;
	tLvUpTable[JOB_WIZARD - 1].iHpMax = 40;
	tLvUpTable[JOB_WIZARD - 1].iMpMin = 50;
	tLvUpTable[JOB_WIZARD - 1].iMpMax = 100;

	//게임을 시작할때 플레이어 정보를 설정
	_tagPlayer tPlayer = {};
	cout << "이름 : ";
	cin.getline(tPlayer.strName, NAME_SIZE - 1); //문자열의 끝은 null이어야 하기 때문에 -1
	
	int iJob = JOB_NONE;
	while (iJob == JOB_NONE) {
		system("cls");
		cout << "1. 기사" << endl;
		cout << "2. 궁수" << endl;
		cout << "3. 마법사" << endl;
		cout << "직업을 선택하세요 : ";
		cin >> iJob;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		//열거체에 직업을 추가할때 오류발생 조건을 아래와 같이하면
		//따로 수정할 필요가 없다.
		else if (iJob <= JOB_NONE || iJob >= JOB_END) {
			iJob = JOB_NONE;
		}
	}

	//플레이어정보 초기설정
	tPlayer.iLevel = 1;
	tPlayer.iExp = 0;
	tPlayer.eJob = (JOB)iJob;
	tPlayer.tInventory.iGold = 10000;
	//능력치설정
	switch (tPlayer.eJob) {
	case JOB_KNIGHT:
		strcpy_s(tPlayer.strJobName, "기사");
		tPlayer.iAttackMin = 5;
		tPlayer.iAttackMax = 10;
		tPlayer.iArmorMin = 15;
		tPlayer.iArmorMax = 20;
		tPlayer.iHPMax = 500;
		tPlayer.iHP = 500;
		tPlayer.iMP = 100;
		tPlayer.iMPMax = 100;
		break;
	case JOB_ARCHER:
		strcpy_s(tPlayer.strJobName, "궁수");
		tPlayer.iAttackMin = 10;
		tPlayer.iAttackMax = 15;
		tPlayer.iArmorMin = 10;
		tPlayer.iArmorMax = 15;
		tPlayer.iHP = 400;
		tPlayer.iHPMax = 400;
		tPlayer.iMP = 200;
		tPlayer.iMPMax = 200;
		break;
	case JOB_WIZARD:
		strcpy_s(tPlayer.strJobName, "마법사");
		tPlayer.iAttackMin = 15;
		tPlayer.iAttackMax = 20;
		tPlayer.iArmorMin = 5;
		tPlayer.iArmorMax = 10;
		tPlayer.iHPMax = 300;
		tPlayer.iHP = 300;
		tPlayer.iMP = 300;
		tPlayer.iMPMax = 300;
		break;
	}

	//몬스터를 생산한다.(난이도별로 하나씩 총 3개)
	_tagMonster tMonsterArr[MT_BACK - 1] = {};

	// 고블린 생성
	strcpy_s(tMonsterArr[0].strName, "고블린");
	tMonsterArr[0].iAttackMin = 20;
	tMonsterArr[0].iAttackMax = 30;
	tMonsterArr[0].iArmorMin = 2;
	tMonsterArr[0].iArmorMax = 5;
	tMonsterArr[0].iHP = 100;
	tMonsterArr[0].iHPMax = 100;
	tMonsterArr[0].iMP = 10;
	tMonsterArr[0].iMPMax = 10;
	tMonsterArr[0].iLevel = 1;
	tMonsterArr[0].iExp = 1000;
	tMonsterArr[0].iGoldMin = 500;
	tMonsterArr[0].iGoldMax = 1500;
	//트롤 생성
	strcpy_s(tMonsterArr[1].strName, "트롤");
	tMonsterArr[1].iAttackMin = 80;
	tMonsterArr[1].iAttackMax = 130;
	tMonsterArr[1].iArmorMin = 60;
	tMonsterArr[1].iArmorMax = 90;
	tMonsterArr[1].iHP = 2000;
	tMonsterArr[1].iHPMax = 2000;
	tMonsterArr[1].iMP = 100;
	tMonsterArr[1].iMPMax = 100;
	tMonsterArr[1].iLevel = 5;
	tMonsterArr[1].iExp = 7000;
	tMonsterArr[1].iGoldMin = 6000;
	tMonsterArr[1].iGoldMax = 8000;
	//드래곤 생성
	strcpy_s(tMonsterArr[2].strName, "드래곤");
	tMonsterArr[2].iAttackMin = 250;
	tMonsterArr[2].iAttackMax = 500;
	tMonsterArr[2].iArmorMin = 200;
	tMonsterArr[2].iArmorMax =400;
	tMonsterArr[2].iHP = 30000;
	tMonsterArr[2].iHPMax = 30000;
	tMonsterArr[2].iMP = 20000;
	tMonsterArr[2].iMPMax = 20000;
	tMonsterArr[2].iLevel = 10;
	tMonsterArr[2].iExp = 30000;
	tMonsterArr[2].iGoldMin = 20000;
	tMonsterArr[2].iGoldMax = 50000;

	//상점에서 판매할 아이템 목록을 생성한다.
	_tagItem tStoreWeapon[STORE_WEAPON_MAX] = {};
	_tagItem tStoreArmor[STORE_ARMOR_MAX] = {};
	/*
	char strName[NAME_SIZE];
	char strTypeName[NAME_SIZE];
	ITEM_TYPE eType;
	int iMin;
	int iMax;
	int iPrice;
	int iSell;
	char strDesc[ITEM_DESC_LENGTH];*/

	strcpy_s(tStoreWeapon[0].strName, "하급무기");
	strcpy_s(tStoreWeapon[0].strTypeName, "공용");
	strcpy_s(tStoreWeapon[0].strDesc, "나무로 된 무기");
	tStoreWeapon[0].eType = IT_WEAPON;
	tStoreWeapon[0].iMin = 10;
	tStoreWeapon[0].iMax = 15;
	tStoreWeapon[0].iPrice = 5000;
	tStoreWeapon[0].iSell = 1000;

	strcpy_s(tStoreWeapon[1].strName, "중급무기");
	strcpy_s(tStoreWeapon[1].strTypeName, "공용");
	strcpy_s(tStoreWeapon[1].strDesc, "돌로 된 무기");
	tStoreWeapon[1].eType = IT_WEAPON;
	tStoreWeapon[1].iMin = 100;
	tStoreWeapon[1].iMax = 150;
	tStoreWeapon[1].iPrice = 10000;
	tStoreWeapon[1].iSell = 2000;

	strcpy_s(tStoreWeapon[2].strName, "상급무기");
	strcpy_s(tStoreWeapon[2].strTypeName, "공용");
	strcpy_s(tStoreWeapon[2].strDesc, "강철로 된 무기");
	tStoreWeapon[2].eType = IT_WEAPON;
	tStoreWeapon[2].iMin = 300;
	tStoreWeapon[2].iMax = 400;
	tStoreWeapon[2].iPrice = 50000;
	tStoreWeapon[2].iSell = 10000;

	strcpy_s(tStoreArmor[0].strName, "하급방어구");
	strcpy_s(tStoreArmor[0].strTypeName, "공용");
	strcpy_s(tStoreArmor[0].strDesc, "나무로 된 방어구");
	tStoreArmor[0].eType = IT_ARMOR;
	tStoreArmor[0].iMin = 5;
	tStoreArmor[0].iMax = 7;
	tStoreArmor[0].iPrice = 5000;
	tStoreArmor[0].iSell = 1000;

	strcpy_s(tStoreArmor[1].strName, "중급방어구");
	strcpy_s(tStoreArmor[1].strTypeName, "공용");
	strcpy_s(tStoreArmor[1].strDesc, "돌로 된 방어구");
	tStoreArmor[1].eType = IT_ARMOR;
	tStoreArmor[1].iMin = 40;
	tStoreArmor[1].iMax = 60;
	tStoreArmor[1].iPrice = 10000;
	tStoreArmor[1].iSell = 2000;

	strcpy_s(tStoreArmor[2].strName, "상급방어구");
	strcpy_s(tStoreArmor[2].strTypeName, "공용");
	strcpy_s(tStoreArmor[2].strDesc, "강철로 된 방어구");
	tStoreArmor[2].eType = IT_ARMOR;
	tStoreArmor[2].iMin = 120;
	tStoreArmor[2].iMax = 140;
	tStoreArmor[2].iPrice = 50000;
	tStoreArmor[2].iSell = 10000;


	//각 아이템 정보를 갱신

	while (true) {
		system("cls");
		cout << "****************************로비****************************\n";
		cout << "1. 맵" << endl;
		cout << "2. 상점" << endl;
		cout << "3. 가방" << endl;
		cout << "4. 종료" << endl;
		cout << "메뉴를 선택하세요 : ";
		int iMenu;
		cin >> iMenu;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		if (iMenu == MM_EXIT)
			break;

		switch (iMenu) {
		case MM_MAP:
			while (true) {
				system("cls");
				cout << "****************************맵****************************\n";
				cout << "1. 쉬움" << endl;
				cout << "2. 보통" << endl;
				cout << "3. 어려움" << endl;
				cout << "4. 뒤로가기" << endl;
				cout << "맵을 선택하세요 : ";
				cin >> iMenu;

				if (cin.fail()) {
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}
				if (iMenu == MT_BACK)
					break;

				//선택한 메뉴에서 1을 빼주면 몬스터 배열의 인덱스가 된다.
				// 그렇게 해서 해당 맵의 몬스터를 생성해준다.
				_tagMonster tMonster = tMonsterArr[iMenu - 1];

				while (true) {
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

					system("cls");

					//플레이어 정보를 출력한다.
					cout << "======================Player======================" << endl;
					cout << "이름 : " << tPlayer.strName << "\t직업 : " <<
						tPlayer.strJobName << endl;
					cout << "레벨 : " << tPlayer.iLevel << "\t경험치 : " <<
						tPlayer.iExp << " / " << iLevelUpExp[tPlayer.iLevel - 1] << endl;

					if (tPlayer.bEquip[EQ_WEAPON] == true) {
						cout << "공격력 : " << tPlayer.iAttackMin << " + " <<
							tPlayer.tEquip[EQ_WEAPON].iMin << " - " <<
							tPlayer.iAttackMax << " + " << tPlayer.tEquip[EQ_WEAPON].iMax;
					}
					else {
						cout << "공격력 : " << tPlayer.iAttackMin << " - " <<
							tPlayer.iAttackMax;
					}

					if (tPlayer.bEquip[EQ_ARMOR] == true) {
						cout << "\t방어력 : " << tPlayer.iArmorMin << " + " <<
							tPlayer.tEquip[EQ_ARMOR].iMin << " - " <<
							tPlayer.iArmorMax << " + " << tPlayer.tEquip[EQ_ARMOR].iMax << endl;
					}
					else {
						cout << "\t방어력 : " << tPlayer.iArmorMin << " - " <<
							tPlayer.iArmorMax << endl;
					}

					cout << "체력 : " << tPlayer.iHP << " / " << tPlayer.iHPMax <<
						"\t마나 : " << tPlayer.iMP << " / " << tPlayer.iMPMax << endl;

					if (tPlayer.bEquip[EQ_WEAPON])
						cout << "장착무기 : " << tPlayer.tEquip[EQ_WEAPON].strName;
					else
						cout << "장착무기 : 없음";

					if (tPlayer.bEquip[EQ_ARMOR])
						cout << "\t장착방어구 : " << tPlayer.tEquip[EQ_ARMOR].strName << endl;
					else
						cout << "\t장착방어구 : 없음" << endl;

					//몬스터 정보 출력
					cout << "======================Monster======================" << endl;
					cout << "이름 : " << tMonster.strName << "\t레벨  " <<
						tMonster.iLevel << endl;
					cout << "공격력 : " << tMonster.iAttackMin << " - " <<
						tMonster.iAttackMax << "\t방어력 : " << tMonster.iArmorMin <<
						" - " << tMonster.iArmorMax << endl;
					cout << "체력 : " << tMonster.iHP << " / " << tMonster.iHPMax <<
						"\t마나" << tMonster.iMP << " / " << tMonster.iMPMax << endl;
					cout << "획득 경험치 : " << tMonster.iExp << "\t획득 골드 : " <<
						tMonster.iGoldMin << " - " << tMonster.iGoldMax << endl << endl;

					cout << "1. 공격" << endl;
					cout << "2. 도망가기" << endl;
					cout << "메뉴를 선택하세요 : ";
					cin >> iMenu;

					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}
					else if (iMenu == BATTLE_BACK)
						break;

					switch (iMenu) {
					case BATTLE_ATTACK:
					{
						int iAttackMin = tPlayer.iAttackMin;
						int iAttackMax = tPlayer.iAttackMax;

						if (tPlayer.bEquip[EQ_WEAPON]) {
							iAttackMin += tPlayer.tEquip[EQ_WEAPON].iMin;
							iAttackMax += tPlayer.tEquip[EQ_WEAPON].iMax;
						}

						int iAttack = rand() % (iAttackMax - iAttackMin + 1) +
							iAttackMin;
						int iArmor = rand() % (tMonster.iArmorMax - tMonster.iArmorMin + 1) +
							tMonster.iArmorMin;

						int iDamage = iAttack - iArmor;
						//삼항연산자 : 조건식 ? true일때 값 : false 일때 값
						iDamage = iDamage < 1 ? 1 : iDamage;

						//몬스터 hp를 감소시킨다.
						tMonster.iHP -= iDamage;
						cout << tPlayer.strName << " 가 " << tMonster.strName << "에게 "
							<< iDamage << " 피해를 입혔습니다. " << endl;

						//몬스터가 죽었을 경우를 처리한다.
						if (tMonster.iHP <= 0) {
							cout << tMonster.strName << " 몬스터가 사망하였습니다." << endl;

							tPlayer.iExp += tMonster.iExp;
							int iGold = (rand() % (tMonster.iGoldMax - tMonster.iGoldMin + 1) +
								tMonster.iGoldMin);
							tPlayer.tInventory.iGold += iGold;

							cout << tMonster.iExp << "경험치를 획득하였습니다." << endl;
							cout << iGold << " Gold를 획득하였습니다. " << endl;

							tMonster.iHP = tMonster.iHPMax;
							tMonster.iMP = tMonster.iMPMax;

							if (tPlayer.iExp >= iLevelUpExp[tPlayer.iLevel - 1]) {
								tPlayer.iExp -= iLevelUpExp[tPlayer.iLevel - 1];
								tPlayer.iLevel++;

								cout << "레벨업 하였습니다." << endl;

								int iJobIndex = tPlayer.eJob - 1;
								int iHPUp = rand() % (tLvUpTable[iJobIndex].iHpMax - tLvUpTable[iJobIndex].iHpMin + 1);
								int iMpUp = rand() % (tLvUpTable[iJobIndex].iMpMax - tLvUpTable[iJobIndex].iMpMin + 1);
								tPlayer.iAttackMin += tLvUpTable[iJobIndex].iAttackMin;
								tPlayer.iAttackMax += tLvUpTable[iJobIndex].iAttackMax;
								tPlayer.iArmorMin += tLvUpTable[iJobIndex].iArmorMin;
								tPlayer.iArmorMax += tLvUpTable[iJobIndex].iArmorMax;

								tPlayer.iHP += iHPUp;
								tPlayer.iMP += iMpUp;
							}

							system("pause");
							break;
						}
						//몬스터가 플레이어를 공격한다.
						iAttack = rand() % (tMonster.iAttackMax - tMonster.iAttackMin + 1) +
							tMonster.iAttackMin;

						int iArmorMin = tPlayer.iArmorMin;
						int iArmorMax = tPlayer.iArmorMax;

						if (tPlayer.bEquip[EQ_ARMOR]) {
							iArmorMin += tPlayer.tEquip[EQ_ARMOR].iMin;
							iArmorMax += tPlayer.tEquip[EQ_ARMOR].iMax;
						}

						iArmor = rand() % (iArmorMax - iArmorMin + 1) + iArmorMin;

						iDamage = iAttack - iArmor;
						//삼항연산자 : 조건식 ? true일때 값 : false 일때 값
						iDamage = iDamage < 1 ? 1 : iDamage;

						//플레이어 hp를 감소시킨다.
						tPlayer.iHP -= iDamage;
						cout << tMonster.strName << " 가 " << tPlayer.strName << "에게 "
							<< iDamage << " 피해를 입혔습니다. " << endl;

						//플레이어가 죽었을 경우
						if (tPlayer.iHP <= 0) {
							cout << tPlayer.strName << " 플레이어가 사망하였습니다." << endl;

							int iExp = tPlayer.iExp * 0.1f;
							int iGold = tPlayer.tInventory.iGold * 0.1f;

							tPlayer.iExp -= iExp;
							tPlayer.tInventory.iGold -= iGold;

							cout << iExp << " 경험치를 잃었습니다." << endl;
							cout << iGold << " 골드를 잃었습니다." << endl;

							tPlayer.iHP = tPlayer.iHPMax;
							tPlayer.iMP = tPlayer.iMPMax;


						}
						system("pause");
					}
						break;
						
					}
				}
			}
			break;
		case MM_STORE:
			while (true) {
				system("cls");
				cout << "======================상점======================" << endl;
				cout << "1. 무기상점" << endl;
				cout << "2. 방어구상점" << endl;
				cout << "3. 뒤로가기" << endl;
				cout << "상점을 선택하세요 : ";
				cin >> iMenu;

				if (cin.fail()) {
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}
				else if (iMenu == SM_BACK) {
					break;
				}

				switch (iMenu) {
				case SM_WEAPON:
					while (true) {
						system("cls");
						cout << "======================무기상점======================" << endl;
						for (int i = 0; i < STORE_WEAPON_MAX; i++) {
							cout << i+1 << ". " << tStoreWeapon[i].strName << endl;
							cout << "사용가능 직업 : " << tStoreWeapon[i].strTypeName << endl;
							cout << "공격력 : " << tStoreWeapon[i].iMin << " - " << tStoreWeapon[i].iMax << endl;
							cout << "설명 : " << tStoreWeapon[i].strDesc << endl;
							cout << "가격 : " << tStoreWeapon[i].iPrice << endl;
							cout << "==================================================" << endl;
						}
						cout << STORE_WEAPON_MAX + 1 << ". 뒤로가기" << endl;
						cout << "보유금액 : " << tPlayer.tInventory.iGold << " Gold" << endl;
						cout << "남은공간 : " << INVENTORY_MAX - tPlayer.tInventory.iItemCount << endl;
						cout << "구입할 아이템을 선택하세요. : ";
						cin >> iMenu;

						if (cin.fail()) {
							cin.clear();
							cin.ignore(1024, '\n');
							continue;
						}
						else if (iMenu == STORE_WEAPON_MAX + 1)
							break;
						
						else if (iMenu<1 || iMenu>STORE_WEAPON_MAX + 1) {
							cout << "잘못 선택하였습니다." << endl;
							system("pause");
							continue;
						}

						int iWeaponIndex = iMenu - 1;

						if (tPlayer.tInventory.iItemCount == INVENTORY_MAX) {
							cout << "가방이 꽉 찼습니다." << endl;
							system("pause");
							continue;
						}
						else if (tPlayer.tInventory.iGold < tStoreWeapon[iWeaponIndex].iPrice) {
							cout << "보유 금액이 부족합니다. " << endl;
							system("pause");
							continue;
						}

						tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount] = tStoreWeapon[iWeaponIndex];
						tPlayer.tInventory.iItemCount++;

						tPlayer.tInventory.iGold -= tStoreWeapon[iWeaponIndex].iPrice;

						cout << tStoreWeapon[iWeaponIndex].strName << " 아이템을 구매하였습니다." << endl;
						system("pause");
					}
					break;
				case SM_ARMOR:
					while (true) {
						system("cls");
						cout << "======================방어구상점======================" << endl;
						for (int i = 0; i < STORE_ARMOR_MAX; i++) {
							cout << i + 1 << ". " << tStoreArmor[i].strName << endl;
							cout << "사용가능 직업 : " << tStoreArmor[i].strTypeName << endl;
							cout << "공격력 : " << tStoreArmor[i].iMin << " - " << tStoreArmor[i].iMax << endl;
							cout << "설명 : " << tStoreArmor[i].strDesc << endl;
							cout << "가격 : " << tStoreArmor[i].iPrice << endl;
							cout << "==================================================" << endl;
						}
						cout << STORE_ARMOR_MAX + 1 << ". 뒤로가기" << endl;
						cout << "보유금액 : " << tPlayer.tInventory.iGold << " Gold" << endl;
						cout << "남은공간 : " << INVENTORY_MAX - tPlayer.tInventory.iItemCount << endl;
						cout << "구입할 아이템을 선택하세요. : ";
						cin >> iMenu;

						if (cin.fail()) {
							cin.clear();
							cin.ignore(1024, '\n');
							continue;
						}
						else if (iMenu == STORE_ARMOR_MAX + 1)
							break;

						else if (iMenu<1 || iMenu>STORE_ARMOR_MAX + 1) {
							cout << "잘못 선택하였습니다." << endl;
							system("pause");
							continue;
						}

						int iArmorIndex = iMenu - 1;

						if (tPlayer.tInventory.iItemCount == INVENTORY_MAX) {
							cout << "가방이 꽉 찼습니다." << endl;
							system("pause");
							continue;
						}
						else if (tPlayer.tInventory.iGold < tStoreArmor[iArmorIndex].iPrice) {
							cout << "보유 금액이 부족합니다. " << endl;
							system("pause");
							continue;
						}

						tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount] = tStoreArmor[iArmorIndex];
						tPlayer.tInventory.iItemCount++;

						tPlayer.tInventory.iGold -= tStoreArmor[iArmorIndex].iPrice;

						cout << tStoreArmor[iArmorIndex].strName << " 아이템을 구매하였습니다." << endl;
						system("pause");
					}
					break;
				}
			}
			break;
		case MM_INVENTORY:
			while (true) {
				system("cls");
				cout << "************************* 가방 ****************************" << endl;
				cout << "===================player===================" << endl;
				cout << "이름 : " << tPlayer.strName << "\t직업 : " << tPlayer.strJobName << endl;
				cout << "레벨 : " << tPlayer.iLevel << "\t경험치 : " <<
					tPlayer.iExp << " / " << iLevelUpExp[tPlayer.iLevel - 1] << endl;

				if (tPlayer.bEquip[EQ_WEAPON] == true) {
					cout << "공격력 : " << tPlayer.iAttackMin << " + " <<
						tPlayer.tEquip[EQ_WEAPON].iMin << " - " <<
						tPlayer.iAttackMax << " + " << tPlayer.tEquip[EQ_WEAPON].iMax;
				}

				else {
					cout << "공격력 : " << tPlayer.iAttackMin << " - " <<
						tPlayer.iAttackMax;
				}

				if (tPlayer.bEquip[EQ_ARMOR] == true) {
					cout << "방어력 : " << tPlayer.iArmorMin << " + " <<
						tPlayer.tEquip[EQ_WEAPON].iMin << " - " <<
						tPlayer.iAttackMax << " + " << tPlayer.tEquip[EQ_WEAPON].iMax;
				}

				cout << "체력 : " << tPlayer.iHP << " / " << tPlayer.iHPMax <<
					"\t마나 : " << tPlayer.iMP << " / " << tPlayer.iMPMax << endl;

				if (tPlayer.bEquip[EQ_WEAPON])
					cout << "장착무기 : " << tPlayer.tEquip[EQ_WEAPON].strName;
				else
					cout << "장착무기 : 없음";

				if (tPlayer.bEquip[EQ_ARMOR])
					cout << "\t장착방어구 : " << tPlayer.tEquip[EQ_ARMOR].strName << endl;
				else
					cout << "\t장착방어구 : 없음" << endl;

				cout << "보유골드 : " << tPlayer.tInventory.iGold << " Gold" << endl << endl;

				for (int i = 0; i < tPlayer.tInventory.iItemCount; i++) {
					cout << i + 1 << ". 이름  : " << tPlayer.tInventory.tItem[i].strName <<
						"\t종류 : " << tPlayer.tInventory.tItem[i].strTypeName << endl;
					cout << "공격력 : " << tPlayer.tInventory.tItem[i].iMin << " - " <<
						tPlayer.tInventory.tItem[i].iMax << endl;
					cout << "판매가격 : " << tPlayer.tInventory.tItem[i].iPrice <<
						"\t구매가격 : " << tPlayer.tInventory.tItem[i].iSell << endl;
					cout << "설명 : " << tPlayer.tInventory.tItem[i].strDesc << endl << endl;
				}

				cout << tPlayer.tInventory.iItemCount + 1 << ". 뒤로가기" << endl;
				cout << "장착할 아이템을 선택하세요. : ";
				cin >> iMenu;

				if (cin.fail()) {
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}
				else if (iMenu == tPlayer.tInventory.iItemCount + 1)
					break;
				else if (iMenu<1 || iMenu>tPlayer.tInventory.iItemCount + 1) {
					cout << "잘못 선택하였습니다." << endl;
					system("pause");
					continue;
				}

				int idx = iMenu - 1;

				EQUIP eq;

				switch (tPlayer.tInventory.tItem[idx].eType) {
				case IT_WEAPON:
					eq = EQ_WEAPON;
					break;
				case IT_ARMOR:
					eq = EQ_ARMOR;
					break;
				}

				if (tPlayer.bEquip[eq] == true) {
					_tagItem tSwap = tPlayer.tEquip[eq];
					tPlayer.tEquip[eq] = tPlayer.tInventory.tItem[idx];
					tPlayer.tInventory.tItem[idx] = tSwap;
				}

				else {
					tPlayer.tEquip[eq] = tPlayer.tInventory.tItem[idx];

					for (int i = idx; i < tPlayer.tInventory.iItemCount - 1; i++) {
						tPlayer.tInventory.tItem[i] = tPlayer.tInventory.tItem[i + 1];
					}

					tPlayer.tInventory.iItemCount--;

					tPlayer.bEquip[eq] = true;
				}
				cout << tPlayer.tEquip[eq].strName << " 아이템을 장착하였습니다." << endl;

				system("pause");
			}
			break;
		default:
			cout << "잘못 선택하였습니다." << endl;
			break;
		}
	}
	return 0;
}