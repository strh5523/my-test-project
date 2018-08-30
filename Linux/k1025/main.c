#include<stdio.h>

struct Node
{

}Node;
int main()
{
	struct Node node;
	printf("node size:%d\n",sizeof(node));

	char ch1 = 'a';
	struct Node node2;
	char ch2 = 'b';
	printf("ch1 add:   %x\n",&ch1);
	printf("node2 add: %x\n",&node2);
	printf("ch2 add:   %x\n",&ch2);

	return 0;

}
