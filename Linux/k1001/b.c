#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<string.h>
#include<sys/msg.h>
struct mess
{
	long type;
	char buff[128];
};

int main()
{
	int msgid = msgget((key_t)1234,IPC_CREAT|0600);
	assert( msgid != -1);
	
	struct mess dt;




	msgrcv(msgid,&dt,128,0,0);//0是不区分，1是第一个消息

	printf("buff=%s\n",dt.buff);
	
	}
