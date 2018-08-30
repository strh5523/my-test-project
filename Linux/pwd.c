#include<stdio.h>
#include<unistd.h>
int main()
{
	char buf[128];
	getcwd(buf,128);
	printf("pwd:%s\n",buf);
	fflush(stdout);
	exit(0);
	}
