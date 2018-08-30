#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<string.h>
#include<sys/msg.h>
struct mess
{
	long type;
	int data;
};

int main()
{
	int msgid = msgget((key_t)1234,IPC_CREAT|0600);
	assert( msgid != -1);
	
	struct mess dt;
	dt.type = 1;
	while(1)
	{
		printf("input:\n");
		scanf("%d",&dt.data);
		msgsnd(msgid,&dt,4,0);
	}


	}
