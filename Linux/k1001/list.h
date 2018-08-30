#include<stdio.h>
#include<stdlib.h>


typedef struct node
{
	int data;
	struct node* next;
}node,*list;

void list_init(list head);

void list_insert(list head,int val);

int list_getelem(list head);//从头删除并且返回该节点数字

