//허프만 트리 출력
//빈도수에 대해 min priority queue로 구현

#include <stdio.h>
#include <stdlib.h>

//A : 450, T : 90, G : 120, C : 270
#define NODES 4

//노드의 character, 빈도수, tree형태에서 왼쪽 노드의 빈도수, 오른쪽 노드의 빈도수를 저장할 구조체를 선언한다.
struct minQueue{
	char character;
	int frequency;
	int left;
	int right;
};

//list에는 각 노드의 정보를 담아서
//pop된 뒤에도 그 정보를 잃지 않도록,
//FindNode 함수에서 사용된다
struct minQueue list[NODES*2];

//현재 우선순위 큐의 size와 list의 size를 저장할 전역변수를 선언한다.
int nodesCount = NODES;
int listCount = 0;

//min heap을 이용해서 우선순위 큐를 만든다.
void makeMinHeap(struct minQueue nodes[], int size) {
	for(int i = 1; i < size; i++) {
		int child = i;
		while(child > 0) {
			int parent = (child-1)/2;

			//min heap이므로 자식이 더 작으면 교환
			if(nodes[child].frequency < nodes[parent].frequency) {
				struct minQueue temp = nodes[child];
				nodes[child] = nodes[parent];
				nodes[parent] = temp;
			}
			child = parent;
		}
	}
}

//우선순위 큐에서 pop하는 함수이다.
struct minQueue popMin(struct minQueue nodes[]) {
	//최상단에 min이 들어가 있으므로 그것을 저장,
	struct minQueue min = nodes[0];
	//list에 추가한다.
	list[listCount++] = min;

	//최상단에 마지막 원소를 넣고 --
	nodes[0] = nodes[--nodesCount];

	//다시 minheap 만들기
	makeMinHeap(nodes, nodesCount);

	return min;
}

//list에서 빈도수에 맞는 node 정보를 return하는 함수이다.
struct minQueue FindNode(int frequency) {
	struct minQueue find;

	//파라미터와 list의 빈도수가 똑같으면 그것을 리턴
	for(int i = 0; i < listCount; i++) {
		if(list[i].frequency == frequency)
			find = list[i];
	}
	return find;
}

//트리를 전위순회한다.
//파라미터로 빈도수를 받아 FindNode함수로 그 node 정보를 담아온다.
void pre(int rootFrequency) {
	if(rootFrequency == 0)
		return;
	struct minQueue root = FindNode(rootFrequency);
	
	//출력한 후 순회
	printf("(%c %d) ", root.character, root.frequency);
	pre(root.left);
	pre(root.right);
}

//허프만 코딩 함수
void HuffmanCoding(struct minQueue nodes[]) {
	//우선 mean heap(우선순위 큐)를 만들고 출력
	makeMinHeap(nodes, NODES);
	
	printf("min priority Queue : \n");
	for(int i = 0; i < NODES; i++)
		printf("(%c %d) ", nodes[i].character, nodes[i].frequency);
	printf("\n");

	//큐에 남은 수가 2 이상일 때 반복
	while(nodesCount >= 2) {
		//가장 작은 수 두개를 출력
		struct minQueue first = popMin(nodes);
		struct minQueue second = popMin(nodes);
		
		printf("\nselect&pop : \nfirst : (%c %d), second : (%c %d)\n", first.character, first.frequency, second.character, second.frequency);

		struct minQueue temp;
		//left에 가장 작은 수의 빈도수를,
		temp.left = first.frequency;
		//right에 그 다음으로 작은 수의 빈도수를 저장
		temp.right = second.frequency;

		//자신의 노드는 그의 합과 char은 빈칸으로 저장
		temp.frequency = first.frequency + second.frequency;
		temp.character = ' ';

		//temp를 큐와 list에 추가 및 저장
		nodes[nodesCount++] = temp;
		list[listCount++] = temp;

		//새 노드, 현재 큐  상태, 현재 허프만 트리의 상태 등의 과정을 출력
		printf("new Node : %d\n", temp.frequency);
		printf("left : (%c %d), right : (%c %d)\n", FindNode(temp.left).character, temp.left, FindNode(temp.right).character, temp.right);
		
		printf("current Queue : \n");
		for(int i = 0; i < nodesCount; i++)
			printf("(%c %d) ", nodes[i].character, nodes[i].frequency);
		printf("\n");

		printf("current huffman tree (전위 순회):\n");
		pre(temp.frequency);
		printf("\n\n");

		//새롭게 추가된 큐를 다시 min heap으로 정리
		makeMinHeap(nodes, nodesCount);
	}
}

int main(int argc, char* argv[]) {
	struct minQueue nodes[NODES] = {{'A', 450, 0, 0}, {'T', 90, 0, 0}, {'G',120, 0, 0}, {'C',270, 0, 0}};

	HuffmanCoding(nodes);
	
	printf("\n최종 허프만트리 (전위순회)\n");
	pre(nodes[0].frequency);

	printf("\n");
	return 0;
}
