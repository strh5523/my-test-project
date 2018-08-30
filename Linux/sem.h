#include<stdio.h>
#include<stdlib.h>
#include<sys/sem.h>
union semun
{
	int val;
};
void init();

void sem_p();

void sem_v();

void sem_deatory();

