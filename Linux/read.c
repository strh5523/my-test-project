#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<fcntl.h>
#include"sem.h"
int main()
{
	init();
	int fdr = open("hello",O_RDONLY);
	sem_p();
	assert(fdr != -1);
	char buff[256] = {0};
	read(fdr,buff,256);
	printf("%s\n",buff);
	close(fdr);
	sem_v();
	sem_destory();
	exit(0);
}
