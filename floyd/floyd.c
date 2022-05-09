//dijkstra 알고리즘의 실행 시간,
//플로이드 워셜 알고리즘의 실행시간 비교
//
//1, 2, 3, 4, 5의 노드
//
#include <stdio.h>
#include <time.h>

#define NODES 10 //(1~5)
//서울 -0, 천안-1, 원주-2, 강릉-3, 논산-4, 대전-5, 대구-6, 포항-7, 광주-8, 부산-9

#define INF 10000

//dijkstra에는 while 종료를 위해 방문한 정점을 저장,
int dijkstra[NODES][NODES];

//dijkstra에서 dinstance를 저장할 배열
int D[NODES] = {0,};

//floyd에는 floyd 결과를 저장,
int floyd[NODES][NODES] = {0,};

//start point를 바꾸는 걸 n번 반복하기 때문에
//start를 파라미터로 받아와
//dijkstra에 방문한 정점이 남아있는지 확인,
int CheckVisit(int start) {
	for(int i = 0; i < NODES; i++) {
		if(dijkstra[start][i] == INF)
			return 1;
	}
	return 0;
}

//i번째 정점이 인덱스와 일치하는지 확인
//(위에꺼랑 합칠 수 있었을텐데;
int FindInDijkstra(int start, int i) {
	for(int j = 0; j < NODES; j++) {
		if(dijkstra[start][j] == i)
			return 1;
	}
	return 0;
}

//all vertex visit
void ExecDijkstra(int G[][NODES]) {
	//CheckVisit을 위해 모든 점들을 INF로 초기화
	for(int i = 0; i < NODES; i++) {
		for(int j = 0; j < NODES; j++)
			dijkstra[i][j] = INF;
	}

	//시작 정점은 0(서울)
	int start = 0;
	while(start < NODES) {
		int dijkstra_count = 0;
		for(int i = 0; i < NODES; i++) 
			D[i] = INF;
		D[start] = 0;

		//방문하지 않은 정점이 남아있을 때
		while(CheckVisit(start)) {
			int min = INF;
			int v;

			for(int i = 0; i < NODES; i++) {
				//이미 방문한 정점이면 continue
				if(FindInDijkstra(start, i))
					continue;
				if(D[i] < min) {
					min = D[i];
					v = i;
				}
			}
			//min값 찾아서 D에 저장하고 dijkstra에 방문한 정점으로 표시
			D[v] = min;
			dijkstra[start][dijkstra_count++] = v;

			//경유해서 더 작으면 update
			for(int i = 0; i < NODES; i++) {
				if(D[v] + G[v][i] < D[i])
					D[i] = D[v] + G[v][i];
			}
		}

		//start 점 표시하고 과정이 끝난 후 결과 출력
		printf("start = %d\n", start);
		for(int	i = 0; i < NODES; i++) 
			printf("%d\t", D[i]);
		printf("\n\n");

		//start++한 후 반복
		start++;
	}
}

//floyd warshall 알고리즘으로 모든 점 최단 경로 구하기
void ExecFloyd(int G[][NODES]) {
	//가중치를 update도 시켜야 하니까
	//결과를 담을 floyd에 파라미터로 받아온 가중치그래프를 복사
	for(int i = 0; i < NODES; i++) {
		for(int j = 0; j < NODES; j++)
			floyd[i][j] = G[i][j];
	}

	//for문을 3번 돌면서 경유한 가중치와 비교해서 작은 걸로 update
	for(int k = 0; k < NODES; k++) {
		for(int i = 0; i < NODES; i++) {
			for(int j = 0; j < NODES; j++) {
				if(floyd[i][k] + floyd[k][j] > floyd[i][j])
					floyd[i][j] = floyd[i][j];
				else
					floyd[i][j] = floyd[i][k] + floyd[k][j];
			}
		}
	}

	//결과 출력, 맨 윗 행은 노드 번호
	printf("D\t");
	for(int i = 0; i < NODES; i++)
		printf("%d\t", i);
	printf("\n");

	for(int i = 0; i < NODES; i++) {
		printf("%d\t", i);
		for(int j = 0; j < NODES; j++)
			printf("%d\t", floyd[i][j]);
		printf("\n");
	}
	printf("\n");
}


int main(int argc, char* argv[]) {
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
//	int graph[NODES][NODES] = {{0, 0, 0, 0, 0, 0},
//							   {0, 0, 4, 2, 5, INF},
//							   {0, INF, 0, 1, INF, 4},
//							   {0, 1, 3, 0, 1, 2},
//							   {0, -2, INF, INF, 0, 2},
//							   {0, INF, -3, 3, 1, 0}};

	printf("dijkstra 알고리즘을 start를 바꿔가며 n번 수행\n");
	
	//시간 측정
	clock_t start_dijkstra = clock();
	ExecDijkstra(graph);
	clock_t end_dijkstra = clock();

	printf("dijkstra 알고리즘 수행 시간 : %lf\n", (double)(end_dijkstra - start_dijkstra)); //CLOCKS_PER_SEC);
	printf("\n\n");


	printf("floyd warshall 알고리즘 수행\n");

	clock_t start_floyd = clock();
	ExecFloyd(graph);
	clock_t end_floyd = clock();

	printf("floyd warshall 알고리즘 수행 시간 : %lf\n", (double)(end_floyd - start_floyd)); //CLOCKS_PER_SEC);
	
	return 0;
}
