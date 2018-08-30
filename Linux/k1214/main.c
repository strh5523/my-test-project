#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<assert.h>

int main()
{
	printf("main pid=%d\n",getpid());
	pid_t pid = fork();
	assert( pid != -1);

	if( pid ==0 )
	{
		//execl("/bin/bash","bash","a.sh",(char*)0);//不用加#!/bin/bash
		execl("./a.sh","a.sh",(char*)0);//a.sh要加#!/bin/bash
		perror("execl error");
		exit(0);
	}
	wait(NULL);
}
