#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX_SIZE 60000

void SelectionSort(int* array) {
	//최솟값을 탐색하고
	//최솟값을 왼쪽에 놓고, 나머지 애들 중에서 최솟값을 찾기 반복
	
	int min;
	int count = 0;

	while(count < MAX_SIZE-1) {
		//일단 min값을 맨 첫번째로 놓고
		min = array[count];
		int index = 0;

		//i를 시작 인덱스부터 max_size만큼 반복
		for(int i = count; i < MAX_SIZE; i++) {
			if(min >= array[i]) {
				//만약 min값보다 더 작은 값이 나오면 그 값을 min으로 변경,
				//그때의 index를 기록
				min = array[i];
				index = i;
			}
		}

		//원래 맨 왼쪽 값을 temp에 넣고, 그 공간에 min값을 넣고, 원래 있던 값은 min이 있던 자리에 => 교환
		int temp = array[count];
		array[count] = min;
		array[index] = temp;
		
		//count++해줘서 다음 인덱스부터 반복
		count++;
	}
}

void MergeSort(int* array, int p, int q) {
	if(p < q) {
		int k = (p+q)/2;

		MergeSort(array, p, k);
		MergeSort(array, k+1, q);

		//생각을 해보자.
		//array가 두개 있을때, 왼쪽 (p) 0번째부터 오른쪽 배열 0번째(k+1)끼리 비교를 해
		//그래서 a[0] b[0]을 비교해서 a가 더작으면 temp에 넣고, p++을 해.
		//b[0]이 더 작으면 temp에 넣고 q++을 하고 다시 비교해
		
		//위에서 mergesort에는 array와 p~k, k+1~q가 들어왔어


		//합병 과정
		int temp[MAX_SIZE];
		//p를 직접 옮기지 않고 복사해서 사용
		int i = p;
		int t = p;
		int j = k+1;
		while(i <= k && j <= q) {
			//두 배열 중 작은 값을 temp에 넣고 ++
			if(array[i] <= array[j]) {
				temp[t] = array[i];
				i++;
				t++;
			}
			else {
				temp[t] = array[j];
				j++;
				t++;
			}
		}
		
		//남는 값이 있다면(두 배열의 크기가 2로 나눴을 때 동일한 크기가 아니라면)
		//temp에 빈 공간을 채워주기
		while(i <= k) {
			temp[t] = array[i];
			i++;
			t++;
		}

		while(j <= q) {
			temp[t] = array[j];
			t++;
			j++;
		}

		//완성된 temp를 array로 옮기기
		for(int init = p; init <= q; init++)
			array[init] = temp[init];
	}
}

int main(int argc, char* argv[]) {
	//int data[MAX_SIZE] = {37, 10, 22, 30, 35, 13, 25, 24};
	int data[MAX_SIZE];
//	printf("sort 전\n");
//
//	for(int i = 0; i < MAX_SIZE; i++)
//		printf("%d ", data[i]);
//
//	printf("\n");
	

	srand(time(NULL));

	for(int i = 0; i < MAX_SIZE; i++)
		data[i] = rand()%100;


	clock_t startMerge = clock();
	//sort방식
	MergeSort(data, 0, MAX_SIZE-1);
	clock_t endMerge = clock();

	double MergeTime = (double)(endMerge - startMerge) / CLOCKS_PER_SEC;
	printf("Merge Sort elapsed time : %lfs\n", MergeTime);


	clock_t startSelection = clock();
	SelectionSort(data);
	clock_t endSelection = clock();

	double SelectionTime = (double)(endSelection - startSelection) / CLOCKS_PER_SEC;
	printf("Selection Sort elapsed time : %lfs\n", SelectionTime);


//	printf("sort 후\n");
//
//	for(int i = 0; i < MAX_SIZE; i++)
//		printf("%d ", data[i]);
//
//	printf("\n");
//	return 0;
}
