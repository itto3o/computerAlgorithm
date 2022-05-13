#include <stdio.h>


#define MATRIX_NUM 5 //(0번째는 비워두기)
#define INF 10000

int main(int argc, char* argv[]) {
	//distance 배열
	int d[MATRIX_NUM] = {10, 20, 5, 15, 30};

	//결과를 담을 2차원 배열, 편의상 0으로 모두 초기화
	int C[MATRIX_NUM][MATRIX_NUM] = {0, };

	//C[i, i] 초기화
	for(int i = 0; i < MATRIX_NUM; i++)
		C[i][i] = 0;
	
	//fin은 최종적으로 배열이 갈리는 부분 기록해두는 변수
	int fin = 0;
	//책의 알고리즘과 동일, 1부터 증가하면서 행렬 곱셈이 작은 값으로 update	
	for(int L = 1; L < MATRIX_NUM-1; L++) {
		for(int i = 1; i < MATRIX_NUM - L; i++) {
			int j = i + L;
			C[i][j] = INF;

			for(int k = i; k <= j - 1; k++) {
				int temp = C[i][k] + C[k+1][j] + d[i-1]*d[k]*d[j];

				//현재 C[i, j]보다 새롭게 계산한 값이 더 작으면 update
				//그 때의 k(행렬이 분할되는 숫자)를 fin에 기록
				if(temp < C[i][j]) {
					C[i][j] = temp;
					fin = k;
				}
			}
		}
	}

	//result 출력
	printf("result : \n");
	//맨 윗부분의 header (C 1 2 3 4)
	printf("C\t");
	for(int i = 1; i < MATRIX_NUM; i++)
		printf("%d\t", i);
	printf("\n");

	//1부터 C의 값들을 출력
	for(int i = 1; i < MATRIX_NUM; i++) {
		//맨 왼쪽 열은 행렬 번호
		printf("%d\t", i);
		for(int j = 1; j < MATRIX_NUM; j++)
			printf("%d\t", C[i][j]);
		printf("\n");
	}

	//최종 결과
	printf("minimun element multiplication : %d\n", C[1][MATRIX_NUM-1]);
	//기록해둔 k(fin)을 기점으로 나뉘는 부분까지 for문으로 출력
	printf("final implicit order : \n(");
	for(int i = 1; i <= fin; i++)
		printf("A%d ", i);
	printf(") (");

	//괄호 닫고 fin +!부터 끝까지 출력
	for(int i = fin + 1; i < MATRIX_NUM; i++)
		printf("A%d ", i);
	printf(")\n");

	return 0;
}		
