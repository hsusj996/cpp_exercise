#include <iostream>
using namespace std;

enum MAIN_MENU {
	MM_NONE,
	MM_ADD,
	MM_LOAD,
	MM_SAVE,
	MM_OUTPUT,
	MM_EXIT
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

#define NAME_SIZE 32
#define ITEM_DESC_LENGTH 512
#define STORE_WEAPON_MAX 3
#define STORE_ARMOR_MAX 3

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

void AddItem(_tagItem* pWeaponStore, _tagItem* pArmorStore) {
	int iStore = 0;
	while (true) {
		system("cls");
		cout << "1. 무기상점" << endl;
		cout << "2. 방어구상점" << endl;
		cout << "3. 취소" << endl;
		cout << "추가할 상점을 선택하세요. : ";

		iStore = InputInt();

		if (iStore == 3)
			return;
		else if (iStore < 1 || iStore > 3)
			continue;
		else
			break;
	}
	int iItemLevel = 0;
	while (true) {
		system("cls");
		cout << "1. 초급" << endl;
		cout << "2. 중급" << endl;
		cout << "3. 고급" << endl;
		cout << "4. 끝" << endl;
		cout << "추가할 아이템 난이도를 선택하세요. : ";

		iItemLevel = InputInt();

		if (iItemLevel == 4)
			return;
		else if (iItemLevel < 1 || iItemLevel > 4)
			continue;

		--iItemLevel;
		break;
	}
	cin.clear();
	cin.ignore(1024, '\n');

	_tagItem* pItem = NULL;

	if (iStore == SM_WEAPON) {
		pItem = &pWeaponStore[iItemLevel];
		pItem->eType = IT_WEAPON;
	}
	else {
		pItem = &pArmorStore[iItemLevel];
		pItem->eType = IT_ARMOR;
	}
	cout << "이름 : ";
	cin.getline(pItem->strName, NAME_SIZE);
	cin.clear();
	cin.ignore(1024, '\n');
	cout << "종류 : ";
	cin.getline(pItem->strTypeName, NAME_SIZE);
	cin.clear();
	cin.ignore(1024, '\n');
	//스탯을 입력받는다.
	cout << "최소능력치 :";
	pItem->iMin = InputInt();
	cout << "최대능력치 :";
	pItem->iMax = InputInt();
	cout << "구매가격 :";
	pItem->iPrice = InputInt();
	cout << "판매가격 :";
	pItem->iSell = InputInt();
	cout << "설명 :";
	cin.getline(pItem->strDesc, ITEM_DESC_LENGTH);
	cin.clear();
	cin.ignore(1024, '\n');
}

bool SaveItem(_tagItem *WeaponStore,_tagItem *ArmorStore) {
	FILE* pFile = NULL;

	fopen_s(&pFile, "Item.list", "wb");
	if (pFile) {
		fwrite(WeaponStore, sizeof(_tagItem), STORE_WEAPON_MAX, pFile);
		fwrite(ArmorStore, sizeof(_tagItem), STORE_ARMOR_MAX, pFile);
		fclose(pFile);
		return true;
	}
	return false;
}

bool LoadItem(_tagItem* WeaponStore, _tagItem* ArmorStore) {
	FILE* pFile = NULL;

	fopen_s(&pFile, "Item.list", "rb");
	if (pFile) {
		fread(WeaponStore, sizeof(_tagItem), STORE_WEAPON_MAX, pFile);
		fread(ArmorStore, sizeof(_tagItem), STORE_ARMOR_MAX, pFile);
		fclose(pFile);
		return true;
	}
	return false;
}

void OutputItem(_tagItem* WeaponStore, _tagItem* ArmorStore) {
	system("cls");
	cout << "====================무기상점=====================" << endl;
	for (int i = 0; i < STORE_WEAPON_MAX; i++) {
		cout << i + 1 << ". " << WeaponStore[i].strName << endl;
		cout << "사용가능 직업 : " << WeaponStore[i].strTypeName << endl;
		cout << "공격력 : " << WeaponStore[i].iMin << " - " << WeaponStore[i].iMax << endl;
		cout << "설명 : " << WeaponStore[i].strDesc << endl;
		cout << "가격 : " << WeaponStore[i].iPrice << endl;
		cout << "==================================================" << endl;
	}

	cout << "====================방어구상점=====================" << endl;
	for (int i = 0; i < STORE_ARMOR_MAX; i++) {
		cout << i + 1 << ". " << ArmorStore[i].strName << endl;
		cout << "사용가능 직업 : " << ArmorStore[i].strTypeName << endl;
		cout << "공격력 : " << ArmorStore[i].iMin << " - " << ArmorStore[i].iMax << endl;
		cout << "설명 : " << ArmorStore[i].strDesc << endl;
		cout << "가격 : " << ArmorStore[i].iPrice << endl;
		cout << "==================================================" << endl;
	}
	system("pause");
}

int main() {
	_tagItem tWeaponStore[STORE_WEAPON_MAX] = {};
	_tagItem tArmorStore[STORE_ARMOR_MAX] = {};

	while (true) {
		system("cls");
		cout << "1. 아이템 추가" << endl;
		cout << "2. 읽어오기" << endl;
		cout << "3. 저장" << endl;
		cout << "4. 아이템 출력" << endl;
		cout << "5. 종료" << endl;
		cout << "메뉴를 선택하세요. " << endl;
		int iMenu = InputInt();

		if (iMenu == MM_EXIT)
			break;

		switch (iMenu) {
		case MM_ADD:
			AddItem(tWeaponStore, tArmorStore);
			break;
		case MM_LOAD:
			LoadItem(tWeaponStore, tArmorStore);
			break;
		case MM_SAVE:
			SaveItem(tWeaponStore, tArmorStore);
			break;
		case MM_OUTPUT:
			OutputItem(tWeaponStore, tArmorStore);
			break;
		}
	}
	//자동저장기능
	SaveItem(tWeaponStore, tArmorStore);
	return 0;
}