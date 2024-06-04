//박예담

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include "InsertLinkedList.h"


//연결 리스트의 전체 메모리를 해제하는 연산
listNode* freeLinkedList_h(listNode* head) {
	listNode* p;					// 노드 한개를 가르키는 포인터 변수 생성
	while(head != NULL){			// 전달받은 리스트가 공백이 아니면
		p = head;					// 새로 생성한 p의 주소를 head의 주소로 맞춰주고
		head = head->link;
		free(p);					// 삭제할 노드의 동적할당된 공간을 없애버림
		p = NULL;
	}

	return head;
}

//연결리스트를 순서대로 출력하는 연산
listNode* printList(listNode* head) {
	listNode* p;
	printf("L = (");
	p = head;
	while (p != NULL) {
		printf("%s", p->data);
		p = p->link;
		if (p != NULL) printf(", ");
	}
	printf(") \n");

	return head;
}

//첫번째 노드를 삽입하는 연산
listNode* insertFirstNode(listNode* head, char* x) {
	listNode* newNode;
	newNode = (listNode*)malloc(sizeof(listNode));
	strcpy(newNode->data, x);
	newNode->link = head;
	head = newNode;

	return head;
}

//노드를 pre 뒤에 삽입하는 연산
listNode* insertMiddleNode(listNode* head, listNode* pre, char* x) {
	listNode* newNode;
	newNode = (listNode*)malloc(sizeof(listNode));
	strcpy(newNode->data, x);
	if (head == NULL) {			// 공백리스트 일때
		newNode->link = NULL;		// 새노드의 링크를 널로 넣어서 맨 마지막 노드로 만들어버리고
		head = newNode;			// 새노드의 주소를 헤드에 줘서 헤드와 연결되도록만들기
	} 
	else if (pre == NULL) {			// pre(==찾는값)이 없을때
		newNode->link = head;	// 새노드의 링크에 헤드가 가진 값을 줘서 기존 1번노드를 2번째로 연결해주고
		head = newNode;			// 새노드를 헤드와 연결해서 새노드를 1번째 노드로 만들어버리기
	}
	else {							// pre(==찾는값)이 있을때
		newNode->link = pre->link;	// pre의 뒷 노드들을 새노드들의 뒤로 연결
		pre->link = newNode;		// pre의 다음으로 새노드를 연결
	}

	return head;
}

//마지막 노드를 삽입하는 연산
listNode* insertLastNode(listNode* head, char* x) {
	listNode* newNode;
	listNode* temp;
	newNode = (listNode*)malloc(sizeof(listNode));
	strcpy(newNode->data, x);
	newNode->link = NULL;				// 삽입할 노드는 마지막에 꼭 널값 => 여기까지가 기본세팅
	if (head == NULL) {				// 기존에 있던 리스트가 공백일때
		head = newNode;
		return;
	}
	temp = head;						// 리스트가 공백이 아닐 경우
	while (temp->link != NULL)			// 맨 마지막 노드를 찾을때까지 이동
		temp = temp->link;
	temp->link = newNode;

	return head;
}

//리스트에서 노드 p를 삭제하는 연산
listNode* deleteNode(listNode* head, listNode* p) {
	listNode* pre;
	if (head == NULL) return;
	if (head->link == NULL) {
		free(head);				//동적할당한 공간을 free로 날려버림
		head = NULL;
		return;
	}
	else if (p == NULL) return;
	else {
		pre = head;
		while (pre->link != p) {	//찾는노드(p)의 한칸 앞에있는 pre노드를 찾는 행위
			pre = pre->link;
		}
		pre->link = p->link;
		free(p);
	}
	return head;
}

//리스트에서 x 노드를 탐색하는 연산
listNode* searchNode(listNode* head, char* x) {
	listNode* temp;
	temp = head;
	while (temp != NULL) {
		if (strcmp(temp->data, x) == 0) return temp;		
		else temp = temp->link;
	}
	return temp;
}

//리스트의 노드 순서를 역순으로 바꾸는 연산
listNode* reverse(listNode* head) {
	listNode* p;
	listNode* q;
	listNode* r;

	p = head;
	q = NULL;
	r = NULL;

	while (p != NULL) {
		r = q;
		q = p;
		p = p->link;
		q->link = r;
	}
	head = q;

	return head;
}
