//�ڿ���

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include "InsertLinkedList.h"


//���� ����Ʈ�� ��ü �޸𸮸� �����ϴ� ����
listNode* freeLinkedList_h(listNode* head) {
	listNode* p;					// ��� �Ѱ��� ����Ű�� ������ ���� ����
	while(head != NULL){			// ���޹��� ����Ʈ�� ������ �ƴϸ�
		p = head;					// ���� ������ p�� �ּҸ� head�� �ּҷ� �����ְ�
		head = head->link;
		free(p);					// ������ ����� �����Ҵ�� ������ ���ֹ���
		p = NULL;
	}

	return head;
}

//���Ḯ��Ʈ�� ������� ����ϴ� ����
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

//ù��° ��带 �����ϴ� ����
listNode* insertFirstNode(listNode* head, char* x) {
	listNode* newNode;
	newNode = (listNode*)malloc(sizeof(listNode));
	strcpy(newNode->data, x);
	newNode->link = head;
	head = newNode;

	return head;
}

//��带 pre �ڿ� �����ϴ� ����
listNode* insertMiddleNode(listNode* head, listNode* pre, char* x) {
	listNode* newNode;
	newNode = (listNode*)malloc(sizeof(listNode));
	strcpy(newNode->data, x);
	if (head == NULL) {			// ���鸮��Ʈ �϶�
		newNode->link = NULL;		// ������� ��ũ�� �η� �־ �� ������ ���� ����������
		head = newNode;			// ������� �ּҸ� ��忡 �༭ ���� ����ǵ��ϸ����
	} 
	else if (pre == NULL) {			// pre(==ã�°�)�� ������
		newNode->link = head;	// ������� ��ũ�� ��尡 ���� ���� �༭ ���� 1����带 2��°�� �������ְ�
		head = newNode;			// ����带 ���� �����ؼ� ����带 1��° ���� ����������
	}
	else {							// pre(==ã�°�)�� ������
		newNode->link = pre->link;	// pre�� �� ������ �������� �ڷ� ����
		pre->link = newNode;		// pre�� �������� ����带 ����
	}

	return head;
}

//������ ��带 �����ϴ� ����
listNode* insertLastNode(listNode* head, char* x) {
	listNode* newNode;
	listNode* temp;
	newNode = (listNode*)malloc(sizeof(listNode));
	strcpy(newNode->data, x);
	newNode->link = NULL;				// ������ ���� �������� �� �ΰ� => ��������� �⺻����
	if (head == NULL) {				// ������ �ִ� ����Ʈ�� �����϶�
		head = newNode;
		return;
	}
	temp = head;						// ����Ʈ�� ������ �ƴ� ���
	while (temp->link != NULL)			// �� ������ ��带 ã�������� �̵�
		temp = temp->link;
	temp->link = newNode;

	return head;
}

//����Ʈ���� ��� p�� �����ϴ� ����
listNode* deleteNode(listNode* head, listNode* p) {
	listNode* pre;
	if (head == NULL) return;
	if (head->link == NULL) {
		free(head);				//�����Ҵ��� ������ free�� ��������
		head = NULL;
		return;
	}
	else if (p == NULL) return;
	else {
		pre = head;
		while (pre->link != p) {	//ã�³��(p)�� ��ĭ �տ��ִ� pre��带 ã�� ����
			pre = pre->link;
		}
		pre->link = p->link;
		free(p);
	}
	return head;
}

//����Ʈ���� x ��带 Ž���ϴ� ����
listNode* searchNode(listNode* head, char* x) {
	listNode* temp;
	temp = head;
	while (temp != NULL) {
		if (strcmp(temp->data, x) == 0) return temp;		
		else temp = temp->link;
	}
	return temp;
}

//����Ʈ�� ��� ������ �������� �ٲٴ� ����
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
