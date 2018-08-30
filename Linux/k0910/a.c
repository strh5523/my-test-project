#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<assert.h>
#include<string.h>
#include<signal.h>

void fun(int sig)
{
	printf("sig=%d\n",sig);
}
int main()
{
	signal(SIGPIPE,fun);
	int fdw = open("./fifo",O_WRONLY);
	assert(fdw != -1);
	printf("fdw =%d\n",fdw);
	int newfdw = dup(fdw);
	printf("newfdw=%d\n",newfdw);
	//dup2(fdw,1);
	//printf("hello");
	//char buff[128] = {0};
	//printf("input:\n");
	//fgets(buff,128,stdin);
	int a;
	while(1)
	{
		char buff[128] = {0};
		printf("input:");
		fgets(buff,128,stdin);
		write(fdw,buff,strlen(buff));
		if(strncmp(buff,"end",3) == 0)
		{
			break;
		}
	}
	close(newfdw);
	close(fdw);
}
