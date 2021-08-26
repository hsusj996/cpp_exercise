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
		return INT_MAX; //������ ��ȯ
	}
	return iInput;
}

void AddMonster(_tagMonster* pMonsterArr) {
	int iMap = 0;
	system("cls");
	while (true) {
		system("cls");
		cout << "1. ����" << endl;
		cout << "2. ����" << endl;
		cout << "3. �����" << endl;
		cout << "�߰��� ���̵��� �����ϼ���. : ";
		iMap = InputInt();

		if (iMap == 4)
			return;
		else if (iMap < 1 || iMap > 4)
			continue;

		//1���� �����̱� ������ 1�� ���ҽ��Ѿ� ����� �ε�����
		// �ȴ�.
		--iMap;
		break;
	}

	cin.clear();
	cin.ignore(1024, '\n');

	//���� �̸��� �Է¹޴´�.
	cout << "�̸� : ";
	cin.getline(pMonsterArr[iMap].strName, NAME_SIZE);
	//������ �Է¹޴´�.
	cout << "�ּҰ��ݷ� :";
	pMonsterArr[iMap].iAttackMin = InputInt();
	cout << "�ִ���ݷ� :";
	pMonsterArr[iMap].iAttackMax = InputInt();
	cout << "�ּҹ��� :";
	pMonsterArr[iMap].iArmorMin = InputInt();
	cout << "�ִ���� :";
	pMonsterArr[iMap].iArmorMax = InputInt();
	cout << "�ִ� ü�� :";
	pMonsterArr[iMap].iHPMax = InputInt();
	pMonsterArr[iMap].iHP = pMonsterArr[iMap].iHPMax;
	cout << "�ִ� ���� :";
	pMonsterArr[iMap].iMPMax = InputInt();
	pMonsterArr[iMap].iMP = pMonsterArr[iMap].iMPMax;
	cout << "���� :";
	pMonsterArr[iMap].iLevel = InputInt();
	cout << "ȹ�� ����ġ :";
	pMonsterArr[iMap].iExp = InputInt();
	cout << "�ּ� ��� :";
	pMonsterArr[iMap].iGoldMin = InputInt();
	cout << "�ִ� ��� :";
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
	_tagMonster tMonster[MT_END] = {};

	while (true) {
		system("cls");
		cout << "1. ���� �߰�" << endl;
		cout << "2. �о����" << endl;
		cout << "3. ����" << endl;
		cout << "4. ���� ���" << endl;
		cout << "5. ����" << endl;
		cout << "�޴��� �����ϼ���. " << endl;
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

	//�ڵ�������
	SaveMonster(tMonster);
	return 0;
}