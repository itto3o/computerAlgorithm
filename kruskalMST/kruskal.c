#include <stdio.h>

//엣지와 노드 수를 결정
#define EDGES 10
#define NODES 6

//find함수에서 쓰일 cycle여부를 알 수 있는 배열(초기값은 자신이 대표(루트))
int cycle[NODES] = {0, 1, 2, 3, 4, 5};

//(v1, v2, weight) 구조체 선언
struct weights {
	int v1;	//점, a =0, b=1, c=2, d=3, e=4, f=5
	int v2;
	int weight; //엣지 가중치
};

//완성된 T(tree) 구조체 배열
struct weights T[EDGES];
int Edges_T = 0;

void heapSort(struct weights w[], int num) {
	//자식보다 부모가 크면 힙
	//     [0]
	//	[1]	  [2]
	//	이런식으로 indexing
	//	부모 = 자식-1 / 2

	//int i =1? 0? ==> 1이어야 /2했을 때 부모가 딱나옴
	for(int i = 1; i < num; i++) {
		int child = i;
		while(child > 0) {
			int parent = (child-1)/2;

			//만약 부모보다 자식이 크면 교환 (weight뿐만 아니라 v1, v2까지 교환해줄것)
			if(w[child].weight > w[parent].weight) {
				struct weights temp = w[child];
				w[child] = w[parent];
				w[parent] = temp;
			}
			//부모노드로 바꿔줘서 부모쪽으로(위로) 탐색
			child = parent;
		}
	}
}

//대표찾기
int find(int u) {
	//만약 본인이 대표가 아니라면 다시 재귀 호출로 find
	if(u != cycle[u])
		cycle[u] = find(cycle[u]);
	return cycle[u];
}

//find에서 root를 찾아서 root2에 root1을 연결
void Union(int u, int v) {
	int root1 = find(u);
	int root2 = find(v);
	cycle[root2] = root1;
}

void kruskalMST(struct weights w[]) {
	//트리 오름차순 정렬
	//일단 힙을 만들고
	heapSort(w, EDGES);

	//힙이 만들어진 상태에서(가장 큰 숫자가 맨 위로)
	//root와 맨 마지막 child를 바꾸고 그 맨 마지막 child를 제외한 나머지로 heap 구성
	//(마지막 child는 가장 큰 숫자가 됨) ==> 마지막 인덱스에 들어가고 그 인덱스 제외 heap구성
	for(int i = EDGES - 1; i >= 0; i--) {
		struct weights temp = w[i];
		w[i] = w[0];
		w[0] = temp;
		
		heapSort(w, i);
	}

	printf("정렬된 가중치\n");
	for(int i = 0; i < EDGES; i++)
		printf("(%d, %d, %d) ", w[i].v1, w[i].v2, w[i].weight);
	printf("\n");
	
	//힙정렬로 가중치를 모두 정렬했으면
	//kruskal에 따라 먼저 선택	
	for(int i = 0; i < EDGES; i++) {
		//가중치가 제일 작은 것부터 골라서
		struct weights e = w[i];

		//root가 다른 대표라면
		if(find(e.v1) != find(e.v2)) {
			//union
			Union(e.v1, e.v2);
			//union한 후 Tree(최종 트리)에 추가
			T[Edges_T++] = e;
		}
	}	
}

int main(int argc, char* argv[]) {
	struct weights w[EDGES] = {{0, 1, 8}, {0, 3, 2}, {0, 4, 4},
							   {1, 2, 1}, {1, 3, 4}, {1, 5, 2},
							   {2, 5, 1},
							   {3, 4, 3}, {3, 5, 7},
							   {4, 5, 9}};
	kruskalMST(w);

	int cost = 0;
	for(int i = 0; i < Edges_T; i++) {
		printf("(%d, %d), ", T[i].v1, T[i].v2);
		cost += T[i].weight;
	}
	printf("\ncost : %d\n", cost);

	return 0;
}
