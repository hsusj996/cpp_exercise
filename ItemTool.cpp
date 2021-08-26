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
		return INT_MAX; //������ ��ȯ
	}
	return iInput;
}

void AddItem(_tagItem* pWeaponStore, _tagItem* pArmorStore) {
	int iStore = 0;
	while (true) {
		system("cls");
		cout << "1. �������" << endl;
		cout << "2. ������" << endl;
		cout << "3. ���" << endl;
		cout << "�߰��� ������ �����ϼ���. : ";

		iStore = InputInt();

		if (iStore == 3)
			return;
		else if (iStore < 1 || iStore > 3)
			continue;

		--iStore;
		break;
	}
	int iItemLevel = 0;
	while (true) {
		system("cls");
		cout << "1. �ʱ�" << endl;
		cout << "2. �߱�" << endl;
		cout << "3. ���" << endl;
		cout << "4. ��" << endl;
		cout << "�߰��� ������ ���̵��� �����ϼ���. : ";

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
	cout << "�̸� : ";
	cin.getline(pItem->strName, NAME_SIZE);
	cout << "���� : ";
	cin.getline(pItem->strTypeName, NAME_SIZE);
	//������ �Է¹޴´�.
	cout << "�ּҴɷ�ġ :";
	pItem->iMin = InputInt();
	cout << "�ִ�ɷ�ġ :";
	pItem->iMax = InputInt();
	cout << "���Ű��� :";
	pItem->iPrice = InputInt();
	cout << "�ǸŰ��� :";
	pItem->iSell = InputInt();
	cout << "���� :";
	cin.getline(pItem->strDesc, ITEM_DESC_LENGTH);
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

void OutputMonster(_tagMonster* pMonsterArr) {
	system("cls");
	cout << "======================Monster======================" << endl;
	for (int i = 0; i < MT_END; i++) {

		cout << "�̸� : " << pMonsterArr[i].strName << "\t����  " <<
			pMonsterArr[i].iLevel << endl;
		cout << "���ݷ� : " << pMonsterArr[i].iAttackMin << " - " <<
			pMonsterArr[i].iAttackMax << "\t���� : " << pMonsterArr[i].iArmorMin <<
			" - " << pMonsterArr[i].iArmorMax << endl;
		cout << "ü�� : " << pMonsterArr[i].iHP << " / " << pMonsterArr[i].iHPMax <<
			"\t����" << pMonsterArr[i].iMP << " / " << pMonsterArr[i].iMPMax << endl;
		cout << "ȹ�� ����ġ : " << pMonsterArr[i].iExp << "\tȹ�� ��� : " <<
			pMonsterArr[i].iGoldMin << " - " << pMonsterArr[i].iGoldMax << endl << endl;
	}
	system("pause");
}

int main() {
	_tagItem tWeaponStore[STORE_WEAPON_MAX] = {};
	_tagItem tArmorStore[STORE_ARMOR_MAX] = {};

	while (true) {
		system("cls");
		cout << "1. ������ �߰�" << endl;
		cout << "2. �о����" << endl;
		cout << "3. ����" << endl;
		cout << "4. ������ ���" << endl;
		cout << "5. ����" << endl;
		cout << "�޴��� �����ϼ���. " << endl;
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
			SaveMonster(tMonster);
			break;
		case MM_OUTPUT:
			OutputMonster(tMonster);
			break;

		}
	}

	//�ڵ�������
	SaveMonster(tMonster);
	return 0;
}