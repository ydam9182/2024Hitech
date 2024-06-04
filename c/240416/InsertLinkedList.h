//�ڿ���

#pragma once

//�ܼ����� ����Ʈ�� ��� ������ ����ü�� ����
typedef struct ListNode { 
	char data[4]; //������ ����
	struct ListNode* link; // ��ũ����
}listNode;

listNode* haed;
//// ����Ʈ�� ������ ��Ÿ���� head ��带 ����ü�� ����
//typedef struct { 
//	listNode* head; // ù��° ��带 ����ų ���
//}linkedList_h; 

listNode* createLinkedList_h(void); // ��带 ���� ����� �ּҸ� ��ȯ
listNode* freeLinkedList_h(listNode*);
listNode* printList(listNode*);
listNode* insertFirstNode(listNode* head, char* x); // �Ű����� : ����� �ּ�, �� ���� �ּ�
listNode* insertMiddleNode(listNode* head, listNode* pre, char* x);
listNode* insertLastNode(listNode* head, char* x);
listNode* deleteNode(listNode* head, listNode* P); // �Ű����� : ����� �ּ�, ����� �ּ�
listNode* searchNode(listNode* head, char*); // ����� �ּҸ� ��ȯ
listNode* reverse(listNode* head);