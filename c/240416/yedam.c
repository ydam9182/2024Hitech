//�ڿ���

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "InsertLinkedList.h"

int main() {
	listNode* head = NULL;	// ����� ��� ����: ���鸮��Ʈ
	listNode* p;			// searchNode�� ã�� ����� �ּҸ� �����ϴ� ����

	printf("(1) ����Ʈ�� [��],[��],[��] ��� �����ϱ�! \n");
	head = insertLastNode(head, "��");
	head = insertLastNode(head, "��");
	head = insertLastNode(head, "��"); // �� ������ ��忡 ����
	printList(head); //������� �� ���

	printf("\n(2) ����Ʈ���� [��] ��� Ž���ϱ�! \n");
	p = searchNode(head, "��");
	if (p == NULL)
		printf("ã�� �����Ͱ� �����ϴ�. \n");
	else
		printf("[%s]�� ã�ҽ��ϴ�. \n", p->data);

	printf("\n(3) ����Ʈ�� [��] �ڿ� [��] ��� �����ϱ�! \n");
	head = insertMiddleNode(head, p, "��");
	printList(head); //������� �� ���
	
	printf("\n(4) ����Ʈ�� [��] ��� �����ϱ�! \n");
	p = searchNode(head, "��");
	head = deleteNode(head, p);
	printList(head);

	printf("\n(5) ����Ʈ ������ �������� �ٲٱ�! \n");
	head = reverse(head);
	printList(head);

	freeLinkedList_h(head);

	getchar(); 
	// ������ ��ư�� �ֱ� ������ ����â ������ �ʵ��� �����ϴ°�(��ǻ� �ǹ� ���°�)

	return 0;

} 
