#include"list.h"
#include<assert.h>
void list_init(list head)
{
	assert(head != NULL);
	head->next = NULL;
}

void list_insert(list head,int val)
{
	assert(head != NULL);
	node* p = (node*)malloc(sizeof(node));
	p->data = val;
	p->next = NULL;
	node* q = head;
	while(q->next)
	{
		q = q->next;
	}
	q->next = p;

}

int list_getelem(list head)
{
	assert(head != NULL);
	node*p = head->next;

	if(p == NULL)
	{
		return -1;
	}
	head->next = p->next;
	int tmp = p->data;
	free(p);
	return tmp;
}

