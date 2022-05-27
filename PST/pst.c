#include <stdio.h>

//노드 수
#define NODES 6
#define EDGES 10

#define INF 10000

//find함수에서 쓰일 cycle여부를 알 수 있는 배열(초기값은 자신이 대표(루트))
int cycle[NODES] = {0, 1, 2, 3, 4, 5};

//(v1, v2, weight) 구조체 선언
struct weights {
	int v1;
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
//
//	printf("정렬된 가중치\n");
//	for(int i = 0; i < EDGES; i++)
//		printf("(%d, %d, %d) ", w[i].v1, w[i].v2, w[i].weight);
//	printf("\n");
	
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
	//가중치 입력
	int g[NODES][NODES] = {{0,3,INF,2,4,INF},
						   {3, 0, 1, 4, INF, 2},
						   {INF, 1, 0, INF, INF, 1},
						   {2, 4, INF, 0, 5, 7},
						   {4, INF, INF, 5, 0, 9},
						   {INF, 2, 1, 7, 9, 0}};

	//kruskal 알고리즘을 사용하기 위해
	//g의 노드들을 간선크기의 구조체 배열로 바꿔주기
	struct weights w[EDGES] = {{0,}};

	int count = 0;
	for(int i = 0; i < NODES; i++) {
		for(int j = i; j < NODES; j++) {
			//g에서 값이 무한대거나 0이면 입력x
			if(g[i][j] == INF || i == j)
				continue;
			struct weights temp = {i, j, g[i][j]};
			w[count] = temp;
			count++;
		}
	}		

	//간선별로 정리한 w를 kruskal 수행
	kruskalMST(w);

	//결과 T의 값을 출력
	printf("mst = ");
	for(int i = 0; i < Edges_T; i++) {
		printf("(%d, %d, %d), ", T[i].v1, T[i].v2, T[i].weight);
	}
	printf("\n");


	//start점에서 시작하고, start와 이어진 mst의 경로를 찾아서 start_path에 넣기
	struct weights start_path[NODES];
	int start_path_count = 0;
	int start = 0;

	for(int i = 0; i < Edges_T; i++) {
		if(T[i].v1 == start) 
			start_path[start_path_count++] = T[i];
	}

	//출발지에서 시작하여 처음으로 돌아올 때까지 거치는 경로를 저장
	int path[2*NODES];
	int path_count = 0;


	for(int i = 0; i < start_path_count; i++) {
		//위에서 구한 start_path중 하나에서 시작,
		//start와 이어진 vertex하나 선택
		int next = start_path[i].v2;
		int node_count = 1;

		//일단 시작점과 그 다음점을 path에 넣고
		path[path_count++] = start_path[i].v1;
		path[path_count++] = next;
		for(int j = 0; j < Edges_T; j++) {
			//만약 다음점으로 시작하는 MST경로가 있다면
			if(T[j].v1 == next) {
				//그 경로의 다음점을 next와 path에 저장
				next = T[j].v2;
				path[path_count++] = next;
				j = -1;
				node_count++;
			}
		}
		//만약 다음점으로 시작하는 경로를 찾지 못했다면
		//그 점에서 경로가 끝났으므로
		//다시 돌아가기
		for(int j = path_count; j >= path_count - node_count; j--) 
			path[path_count++] = path[j-2];
	}
	
	printf("모든 정점 방문 path = ");
	for(int i = 0; i < path_count; i++)
		printf("%d ", path[i]);
	printf("\n");

	//정점별 반복flag를 check
	int check_reputation[NODES][NODES] = {{0, 0}, {1, 0}, {2,0}, {3,0}, {4,0}, {5,0}};
	printf("중복 방문 제거 후 pst = ");
	for(int i = 0; i < path_count; i++) {
		int vertex = path[i];
		//path중 한 점을 찾아
		if(vertex == check_reputation[vertex][0]) {
			//반복 flag가 0이면(반복되지 않았다면)
			if(check_reputation[vertex][1] == 0) {
				//출력 후 flag = 1
				printf("%d ", vertex);
				check_reputation[vertex][1] = 1;
			}
		}
	}
	//마지막에 도착점(시작점) 출력
	printf("%d\n", start);
	return 0;
}
