#include <iostream>
using namespace std;

void Test(int** pp) {
	  
}

int main() {
	FILE* pFile = NULL;

	//1�� ���� : ������ ����������
	//2�� ���� : ���ϰ��, �������Ϸ� �����ϸ� exe������ �ִ� ���
	// 	   �� �������� ����
	//3�� ���� : �б�, ����, ����| �������� : �ؽ�Ʈ , ���̳ʸ�
	//r : �ϱ� w : ���� a : ����		t : �ؽ�Ʈ b : ���̳ʸ�
	//fopen_s(&pFile, "hot.txt", "wt");

	//if (pFile != NULL) {
	//	// fwrite, fread 2���� �Լ��� ����
	//	// fputs, fgets �� ����
	//	const char* pText = "abcd";

	//	fwrite(pText, 1, 4, pFile); 

	//	//���ڿ��� ������ �ݾƾ���
	//	fclose(pFile);

	//	cout << "����" << endl;
	//}

	fopen_s(&pFile, "hot.txt", "rt");
	if (pFile) {
		char strText[5] = {};

		fread(strText, 1, 4, pFile);
		
		cout << strText << endl;
		
		fclose(pFile);
		cout << "���� �б� ����" << endl;
	}
	return 0;
}