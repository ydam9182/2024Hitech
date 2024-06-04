//박예담

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "InsertLinkedList.h"

int main() {
	listNode* head = NULL;	// 노드의 헤드 선언: 공백리스트
	listNode* p;			// searchNode로 찾을 노드의 주소를 저장하는 공간

	printf("(1) 리스트에 [월],[수],[일] 노드 삽입하기! \n");
	head = insertLastNode(head, "월");
	head = insertLastNode(head, "수");
	head = insertLastNode(head, "일"); // 맨 마지막 노드에 삽입
	printList(head); //현재까지 값 출력

	printf("\n(2) 리스트에서 [수] 노드 탐색하기! \n");
	p = searchNode(head, "수");
	if (p == NULL)
		printf("찾는 데이터가 없습니다. \n");
	else
		printf("[%s]를 찾았습니다. \n", p->data);

	printf("\n(3) 리스트의 [수] 뒤에 [금] 노드 삽입하기! \n");
	head = insertMiddleNode(head, p, "금");
	printList(head); //현재까지 값 출력
	
	printf("\n(4) 리스트의 [일] 노드 삭제하기! \n");
	p = searchNode(head, "일");
	head = deleteNode(head, p);
	printList(head);

	printf("\n(5) 리스트 순서를 역순으로 바꾸기! \n");
	head = reverse(head);
	printList(head);

	freeLinkedList_h(head);

	getchar(); 
	// 임의의 버튼을 넣기 전까지 실행창 닫히지 않도록 유지하는거(사실상 의미 없는거)

	return 0;

} 
