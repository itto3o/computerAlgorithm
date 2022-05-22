#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//insert, delete, substitute 중에 제일 작은 값을 return
int min(int insert, int delete, int substitute) {
	int min = insert;

	if(min > delete)
		min = delete;
	if(min > substitute)
		min = substitute;

	return min;
}

int main(int argc, char* argv[]) {
	//명령어에 3개의 인자가 아니면 usage출력 후 종료
	if(argc != 3) {
		printf("Usage : %s str1 str2", argv[0]);
		exit(1);
	}

	//m은 S의 길이, n은 T의 길이(C는 \0도 함께 저장된다.)
	int m = strlen(argv[1]);
	int n = strlen(argv[2]);

	char S[m];
	char T[n];
	strcpy(S, argv[1]);
	strcpy(T, argv[2]);

	//결과 저장할 E 배열 선언
	int E[m][n];

	//초기화
	for(int i = 0; i < m; i++)
		E[i][0] = i;
	for(int j = 0; j < n; j++)
		E[0][j] = j;

	//알고리즘 시작
	for(int i = 1; i < m; i++) {
		for(int j = 1; j < n; j++) {
			int a;
			if(S[i] != T[j])
				a = 1;
			else
				a = 0;

			int insert = E[i][j-1] +1;
			int delete = E[i-1][j] + 1;
			int substitute = E[i-1][j-1] + a;

			//insert, delete, substitute 중 min값을
			int edit = min(insert, delete, substitute);
			//E에 입력
			E[i][j] = edit;
		}
	
	}
//이 밑으로는
//	어디서 어떤 연산이 이뤄지는지 출력하려고 했다.
//	각 행의 min값을 찾아서 이전 행의 min보다 크다면 연산이 이뤄진 것으로 봤는데,
//	이럴 경우 str st에서 delete인지, str sto에서 substitute인지 알 수 있는 방법이 떠오르지 않아서
//	성공하지는 못했다.
//
//	교수님의 순회방법을 위해선 E(결과를 저장할 배열)를 전역변수로? 사용해야할 것 같은데
//	E의 배열 사이즈가 정해져있는 게 아니라서(argv로 str을 받아온 사이즈라서) 전역변수로 선언하진 못했다.
//	생각해보니까 함수 인자나 파라미터로 보냈어야 했을까?
//
//
//	int min_before = 0;
//	int min_j = 0;
//	char oper[20];
//
//	for(int i = 1; i < m; i++) {
//		int min_column = E[i][1];
//		min_j = 1;
//		for(int j = 1; j < n; j++) {
//			int insert = E[i][j-1] +1;
//			int delete = E[i-1][j] + 1;
//			int substitute = E[i-1][j-1] + 1; //다를 때, a = 1일 때가정
//
//			int edit = min(insert, delete, substitute);
//
//			//어디서 edit이 일어났는지 확인하는 방법
//			//1. 그 행의 min과 좌표값을 찾고
//			//그 min값을 저장해두고 다음 행의 min을 찾음
//			//==> min이 더 커졌다면 insert, delete, substitute와 min이 같은 것을 출력
//
//			if(min_column > E[i][j]) {
//				min_column = E[i][j];
//				min_j = j;
//				if(edit == insert)
//					strcpy(oper, "insert\0");
//				else if(edit == delete)
//					strcpy(oper, "delete\0");
//				else if(edit == substitute)
//					strcpy(oper, "substitute\0");
//			}
//		}
//		if(min_before < min_column) {
//			printf("%s : (S[%d], %c), (T[%d], %c)\n", oper, i, S[i], min_j, T[min_j]);
//
//			min_before = min_column;
//		}
//
//	}


//결과 출력
	printf("S(row) : %s, T(column) : %s\n", S, T);

	printf("\nE\t0\t");
	for(int j = 0; j <= n; j++)
		printf("%c\t", T[j]);
	printf("\n");
	//입실론?은 0으로 표시
	printf("0\t");
	for(int j = 0; j <= n; j++)
		printf("%d\t", j);
	printf("\n");
	
	for(int i = 0; i < m; i++) {
		printf("%c\t%d\t", S[i], i+1);
		for(int j = 0; j < n; j++) {
			printf("%d\t", E[i][j]);
		}
		printf("\n");
	}

	//m과 n에는 \0까지 들어가있는 길이라서 -1씩 해줘야 한다.
	printf("\nedit distance : %d\n", E[m-1][n-1]);

	return 0;
}
