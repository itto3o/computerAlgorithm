//selection(ex.7번째로 작은 숫자는?) 문제 해결하는 알고리즘
//quick sort에서 피봇을 기준으로 작은 그룹을 왼쪽, 큰 그룹을 오른쪽에 놓고 위치를 찾는다는 발상
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Selection(int* array, int left, int right, int k) {
	srand(time(NULL));

	//배열에서 pivot을 랜덤으로 뽑기
	//left~ right 사이의 숫자 랜덤하게 뽑기
	int p = rand() % (right - left + 1) + left; 		

	//pivot과 맨 왼쪽 값을 바꾸기
	int temp = array[p];
	array[p] = array[left];
	array[left] = temp;

	int l = left + 1;
	int r = right;
	int tmp;

	while(l <= r) {
		//pivot값 보다 큰 값이 있으면 stop
		while(array[l] <= array[left] && l <= right)
			l++;

		while(array[r] >= array[left] && r > left)
			r--;

		if(l > r) {
			//엇갈렸을 때 pivot이랑 자리 바꾸기
			tmp = array[r];
			array[r] = array[left];
			array[left] = tmp;
		}
		else {
			//그게 아니라면 그냥 교환
			tmp = array[r];
			array[r] = array[l];
			array[l] = tmp;
		}	
	}
	//현재 pivot은 r에 위치하고 있고, 피봇보다 작은 그룹의 사이즈를 구한다.
	int groupSize = (r - 1) - left + 1;

	//k가 왼쪽 그룹에 있다면 왼쪽 그룹에서 다시 selection,
	if( k <= groupSize )
		Selection(array, left, r-1, k);

	//피봇이 k번째 작은 수라면 그대로 return
	else if(k == groupSize + 1)
		return array[r];

	//오른쪽 그룹에 있다면 k를 왼쪽그룹 크기만큼 빼고(피봇 인덱스도 빼고) 다시 selection
	else
		Selection(array, r+1, right, k-groupSize-1);
}

int main(int argc, char* argv[]) {
	int array[12] = {6, 3, 11, 9, 12, 2, 8, 15, 18, 10, 7, 14};

	int key = Selection(array, 0, 11, 7);
	printf("7번째로 작은 숫자는 %d입니다.\n", key);

	return 0;
}
