//박예담

#pragma once

//단순연결 리스트의 노드 구조를 구조체로 정의
typedef struct ListNode { 
	char data[4]; //데이터 영역
	struct ListNode* link; // 링크영역
}listNode;

listNode* haed;
//// 리스트의 시작을 나타내는 head 노드를 구조체로 정의
//typedef struct { 
//	listNode* head; // 첫번째 노드를 가르킬 헤드
//}linkedList_h; 

listNode* createLinkedList_h(void); // 헤드를 만들어서 헤드의 주소를 반환
listNode* freeLinkedList_h(listNode*);
listNode* printList(listNode*);
listNode* insertFirstNode(listNode* head, char* x); // 매개변수 : 헤드의 주소, 들어갈 값의 주소
listNode* insertMiddleNode(listNode* head, listNode* pre, char* x);
listNode* insertLastNode(listNode* head, char* x);
listNode* deleteNode(listNode* head, listNode* P); // 매개변수 : 헤드의 주소, 노드의 주소
listNode* searchNode(listNode* head, char*); // 노드의 주소를 반환
listNode* reverse(listNode* head);