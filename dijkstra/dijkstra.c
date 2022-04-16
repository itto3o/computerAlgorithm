//dijkstra 알고리즘,
//서울 -0, 천안-1, 원주-2, 강릉-3, 논산-4, 대전-5, 대구-6, 포항-7, 광주-8, 부산-9
//시작점은 0(서울)


#include <stdio.h>

#define NODES 10
#define INF 10000

//D는 distance를 저장할 배열, T는 방문을 한(최단경로라고 확정지은 NODE들을 순서대로 저장하는 배열
int D[NODES];
int T[NODES] = { INF, INF, INF, INF, INF, INF, INF, INF, INF, INF };

//T에 최단경로로 확정지은(방문한) 점이 없는지 확인하는 함수,
//아직 확정짓지 않은 점이 있다면 1을 리턴
int Exist_INF(int T[NODES]) {
	for(int i = 0; i < NODES; i++) {
		if(T[i] == INF)
			return 1;
	}
	return 0;
}

//파라미터로 들어온 노드가 T에 이미 존재하는 노드라면(이미 방문한 노드라면) 1을 리턴
int FindInT(int i) {
	for(int j = 0; j < NODES; j++) {
		if(T[j] == i)
			return 1;
	}
	return 0;
}

//다익스트라 알고리즘을 적용하여 최단경로를 찾아낼 함수
void ShortestPath(int G[][NODES], int start) {
	int T_count = 0;

	//시작 전에 D의 요소들을 모두 INF로 초기화,
	for(int i = 0; i < NODES; i++)
		D[i] = INF;
	//start지점은 0으로 초기화
	D[start] = 0;

	//T에 INF가 없을 때까지 반복
	while(Exist_INF(T)) {
		int min = INF;
		int v;
		for(int i = 0; i < NODES; i++) {
			//T에 이미 존재하는 노드라면 continue
			if(FindInT(i))
				continue;
			//T에 없는 노드들중에서 min을 찾기
			if(D[i] < min) {
				min = D[i];
				v = i;
			}
		}
		//그 min을 D와 T에 넣음
		D[v] = min;
		T[T_count++] = v;

		//만약 start지점에서의 현재 경로보다
		//방금 T에 들어간 노드를 거쳐서 가는 경로가 더 짧다면 update
		for(int i = 0; i < NODES; i++) {
			if(D[v] + G[v][i] < D[i])
				D[i] = D[v] + G[v][i];
		}
	}
}

int main(int argc, char* argv[]) {
//서울 -0, 천안-1, 원주-2, 강릉-3, 논산-4, 대전-5, 대구-6, 포항-7, 광주-8, 부산-9
	//가중치 초기화
	int graph[NODES][NODES] = {{0, 12, 15, INF, INF, INF, INF, INF, INF, INF},
								{12, 0, INF, INF, 4, 10, INF, INF, INF, INF},
								{15, INF, 0, 21, INF, INF, 7, INF, INF, INF},
								{INF, INF, 21, 0, INF, INF, INF, 25, INF, INF},
								{INF, 4, INF, INF , 0, 3, INF, INF, 13, INF},
								{INF, 10, INF, INF, 3, 0, 10, INF, INF, INF},
								{INF, INF, 7, INF, INF, 10, 0, 19, INF, 9},
								{INF, INF, INF, 25, INF, INF, 19, 0, INF, 5},
								{INF, INF, INF, INF, 13, INF, INF, INF, 0, 15},
								{INF, INF, INF, INF, INF, INF, 9, 5, 15, 0}};
	ShortestPath(graph, 0);

	//경로 나타내기
	printf("경로 : \n");
	for(int i = 0; i < NODES; i++)
		printf("%d - ", T[i]);

	//노드 윗줄
	//dinstance 밑줄
	printf("\ncost :\n");
	for(int i = 0; i < NODES; i++)
		printf("%d\t", i);

	printf("\n");
	for(int i = 0; i < NODES; i++)
		printf("%d\t", D[i]);

	printf("\n");
	return 0;
}
