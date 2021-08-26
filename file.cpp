#include <iostream>
using namespace std;

void Test(int** pp) {
	  
}

int main() {
	FILE* pFile = NULL;

	//1번 인자 : 파일의 이중포인터
	//2번 인자 : 파일경로, 실행파일로 실행하면 exe파일이 있는 경로
	// 	   를 기준으로 생성
	//3번 인자 : 읽기, 쓰기, 접근| 파일형태 : 텍스트 , 바이너리
	//r : 일기 w : 쓰기 a : 접근		t : 텍스트 b : 바이너리
	//fopen_s(&pFile, "hot.txt", "wt");

	//if (pFile != NULL) {
	//	// fwrite, fread 2개의 함수가 제공
	//	// fputs, fgets 도 제공
	//	const char* pText = "abcd";

	//	fwrite(pText, 1, 4, pFile); 

	//	//사용뒤에는 파일을 닫아야함
	//	fclose(pFile);

	//	cout << "성공" << endl;
	//}

	fopen_s(&pFile, "hot.txt", "rt");
	if (pFile) {
		char strText[5] = {};

		fread(strText, 1, 4, pFile);
		
		cout << strText << endl;
		
		fclose(pFile);
		cout << "파일 읽기 성공" << endl;
	}
	return 0;
}