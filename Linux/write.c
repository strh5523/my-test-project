#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<fcntl.h>
#include"sem.h"
int main()
{
	init();
	int fdw = open("hello",O_WRONLY | O_CREAT,0600);
	sem_p();
	assert(fdw != -1);
	char buff[256] = {0};
	fgets(buff,256,stdin);
	//char buff[256] = "helloworld";
	write(fdw,buff,256);
	close(fdw);
	sem_v();
	sem_destory();
	exit(0);
}
