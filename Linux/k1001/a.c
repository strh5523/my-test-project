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
	dt.type = 1;
	printf("input:\n");
	fgets(dt.buff,128,stdin);

	msgsnd(msgid,&dt,128,0);



	}
