#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<string.h>
#include"sem.h"

int main()
{
	init();
	int i = 0;
	for(;i<10;i++)
	{
		sem_p();
		write(1,"A",1);
		int n = rand()%3;
		sleep(n);
		write(1,"A",1);
		sem_v();
		n = rand()%3;
		sleep(n);
		

	}
	sem_destory();
	exit(0);
}
