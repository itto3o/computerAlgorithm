#include <stdio.h>

#define EDGES 10
#define NODES 6
#define INF 10000
//a - 0, b-1, c-2, d-3, e-4, f-5

//weight를 담을 struct
struct weights {
	int v1;
	int v2;
	int weight;
};

//결과를 담을 T(Tree)
struct weights T[NODES];

//value가 현재 T에 담겨 있는지 확인하는 함수
int contain(int value, struct weights *T, int T_count) {
	for(int i = 0; i < T_count; i++) {
		if(T[i].v1 == value)
			return 1;
	}
	return 0;
}

void Prim(struct weights w[]) {
	//p를 시작점으로 지정
	int p = 2;// 예시에서 c(2) 시작이길래
	//현재 Distance는 모두 무한으로 초기화
	int D[NODES] = { INF, INF, INF, INF, INF, INF };

	//초기 설정, 시작 점을 T에 넣고, D[p] = 0으로 초기화 시킨다.
	struct weights temp = {p, p, 0};
	D[p] = 0;
	int T_count = 0;
	T[T_count++] = temp;

	//시작점에 따라 시작점과 연결된 노드의 가중치를 update 시킨다.
	for(int i = 0; i < EDGES; i++) {
		if(w[i].v1 == p)
			D[(w[i].v2)] = w[i].weight;
		else if(w[i].v2 == p)
			D[(w[i].v1)] = w[i].weight;
	}

	//T에 담으면서 NODES -1 만큼 반복
	while(T_count < NODES) {
		//min은 비교를 위해 INF로 초기화
		int min = INF;
		int Vmin = p;
		for(int j = 0; j < NODES; j++) {
			//만약 현재 T에 담겨 있는 node라면(이미 방문한 노드라면) continue
			if(contain(j, T, T_count))
				continue;
			//min값을 저장
			else if(D[j] < min) {
				min = D[j];
				Vmin = j;
			}
		}
		//min값을 T에 저장(방문)
		T[T_count].v1 = Vmin;
		T[T_count].v2 = Vmin;
		T[T_count++].weight = min;

		//방문한 T를 기점으로 가중치가 적은 게 있으면 update
		for(int i = 0; i < EDGES; i++) {
			//만약 v1이 현재 방문한 node이고, 그곳과 연결된 v2의 가중치가 현재 기록된 v2의 가중치보다 작다면 update
			if(w[i].v1 == Vmin && w[i].weight < D[(w[i].v2)])
				D[(w[i].v2)] = w[i].weight;
			//만약 v2가 현재 방문한 node이고, 그곳과 연결된 v1의 가중치가 현재 기록된 v1의 가중치보다 작다면 update
			else if(w[i].v2 == Vmin && w[i].weight < D[(w[i].v1)])
				D[(w[i].v1)] = w[i].weight;
		}
	}
}

int main(int argc, char* argv[]) {
	//초기 가중치
	struct weights w[EDGES] = {{0,1,3}, {0,3,2}, {0,4,4}, {1,2,1}, {1,3,4}, {1,5,2}, {2,5,1}, {3,4,5}, {3,5,7}, {4,5,9}};

	//prin 수행
	Prim(w);

	int cost = 0;
	for(int i = 0; i < NODES; i++) {
		//방문한 곳 출력 a-0, b-1, c-2, d-3, e-4, f-5
		printf("%d ", T[i].v1);
		cost += T[i].weight;
	}

	printf("\ncost : %d\n", cost);
	return 0;
}
