#include <stdio.h>

//용량은 10, 물건 개수는 8로 고정
#define C 10
#define N 8

//firstfit 방법으로 넣을 곳 찾기
int FirstFit(int* remaining, int B, int item) {
	//item이 들어갈 공간이 있으면 return index,
	for(int i = 0; i < B; i++) {
		if(remaining[i] >= item)
			return i;
	}	
	//없으면 -1 리턴
	return -1;
}

//bestFit 방법으로 넣을 곳 찾기
int BestFit(int* remaining, int B, int item) {
	int min_index =	-1;
	int min = C;
	//for문을 돌면서 새 물건이 들어가면 남는 부분이 가장 작은 곳 찾기
	for(int i = 0; i < B; i++) {
		int remain = remaining[i] - item;
		if(remain >= 0 && remain < min) {
			min = remain;
			min_index = i;
		}
	}
	return min_index;
}

int main(int argc, char* argv[]) {
	//item reset
	int item[N] = {7, 5, 6, 4, 2, 3, 7, 5};
	//item이 어느 통에 들어가는 지 확인
	int record[N] = {0, };
	//채워질 곳
	int Bin[N] = {0, };
	//남아있는 곳
	int remaining[N] = {0, };
	//총 개수
	int B = 0;

	//남아있는 곳 초기화
	for(int i = 0; i < N; i++) 
		remaining[i] = C;

	for(int i = 0; i < N; i++) {
		//FirstFit으로 index를 골라서
		int index = FirstFit(remaining, B, item[i]);
		//만약 index가 -1이 아니라면
		//Bin에 기존에 있던 값과 합쳐서 넣고, record에 기록, remaining에 여유 공간 빼기
		if(index != -1) {
			Bin[index] = Bin[index] + item[i];
			record[i] = index;
			remaining[index] = remaining[index] - item[i];
		}

		//기존에 있는 공간에서 들어갈 공간이 없다면 새로운 곳 추가
		else {
			Bin[B] = item[i];
			record[i] = B;
			remaining[B] = C - item[i];
			B = B + 1;
		}
	}


	//firstfit 출력
	printf("First Fit : \n");
	for(int i = 0; i < N; i++) {
		printf("%d\t", item[i]);
	}
	printf("\n");

	//item마다 record먼저 출력
	for(int i = 0; i < N; i++)
		printf("Bin%d\t", record[i]);
	printf("\n\n");

	//최종 결과
	printf("result = ");
	for(int i = 0; i < B; i++) {
		printf("%d ", Bin[i]);
	}
	printf(", B = %d\n", B);


	////////////Best Fit 시작////////////
	//새롭게 초기화
	B = 0;
	for(int i = 0; i < N; i++) {
		Bin[i] = 0;
		remaining[i] = C;
		record[i] = 0;
	}


	for(int i = 0; i < N; i++) {
		//index를 BestFit으로 검색해서
		int index = BestFit(remaining, B, item[i]);
		//넣을 곳이 있다면 기존에 있던 곳에 추가
		if(index != -1) {
			Bin[index] = Bin[index] + item[i];
			remaining[index] = remaining[index] - item[i];
			record[i] = index;
		}
		//기존에 넣을 곳이 없다면 새롭게 추가
		else {
			Bin[B] = item[i];
			remaining[B] = C - item[i];
			record[i] = B;
			B = B + 1;
		}
	}

	//Best Fit 출력
	printf("\n\nBest Fit : \n");
	for(int i = 0; i < N; i++) {
		printf("%d\t", item[i]);
	}
	printf("\n");

	for(int i = 0; i < N; i++)
		printf("Bin%d\t", record[i]);
	printf("\n\n");

	printf("result = ");
	for(int i = 0; i < B; i++) {
		printf("%d ", Bin[i]);
	}
	printf(", B = %d\n", B);

	return 0;
}
