#include <stdio.h>

#define ARRAY_SIZE 12

int MedianPivot(int* array, int left, int right) {
	int p;

	int l = array[left];
	int r = array[right];
	int k = (left+right)/2;
	int m = array[k];

	if(l < m) {
		//l < m < r
		if(m < r)
			p = k;

		//l < m && r < m && l < r : m이 젤 크고 그 둘중에 비교
		else if(l < r)
			p = right;
		//l<m && r<m && l>r
		else
			p = left;
	
	}
	//l > m
	else { 
		//m < l < r
		if(l < r)
			p = left;
		//l > m, l > r, r > m : l이 젤 크고 남은 둘 중에 비교
		else if(m < r)
			p = right;
		//l > m, l > r, r < m
		else
			p = k;
	}
	return p;

}
void QuickSort(int* array, int left, int right) {
	if(left < right) {
	int pivot;
		//pivot 결정 
		pivot = MedianPivot(array, left, right);

		//pivot값 맨 왼쪽으로 넣기
		int tmp = array[left];
		array[left] = array[pivot];
		array[pivot] = tmp;

		pivot = left;
		int l = left + 1;
		int r = right;
		int temp;

		while(l <= r) {
			while((array[pivot] >= array[l]) && l <= right)
				l++;

			while((array[pivot] <= array[r]) && r > left)
				r--;


			if(l > r) {
				//엇갈렸으니까 pivot을 l자리에 pivot 넣기
				temp = array[r];
				array[r] = array[pivot];
				array[pivot] = temp;
			}
			else {
				//두 개의 자리를 옮기기
				temp = array[l];
				array[l] = array[r];
				array[r] = temp;
			}
		}	
		QuickSort(array, left, r-1);
		QuickSort(array, r+1, right);
	}
}

int main(int argc, char* argv[]) {
	int array[ARRAY_SIZE] = {6, 3, 11, 9, 12, 2, 8, 15, 18, 10, 7, 14};

	printf("정렬 전 \n");
	for(int i = 0; i < ARRAY_SIZE; i++)
		printf("%d ", array[i]);
	printf("\n");

	QuickSort(array, 0, ARRAY_SIZE -1);

	printf("정렬 후 \n");
	for(int i = 0; i < ARRAY_SIZE; i++)
		printf("%d ", array[i]);

	printf("\n");

	return 0;
}
