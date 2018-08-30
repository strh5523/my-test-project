#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<sys/shm.h>
#include"sem.h"
int main()
{
	int shmid = shmget((key_t)1234,256,IPC_CREAT | 0600);
	assert(shmid != -1);
	int a[2] = {1,0};
	int n = 2;
	sem_init(a,n);
	printf("shmid=%d\n",shmid);

	char * s = (char*)shmat(shmid,NULL,0);//NULL不指定在进程中的地址位置，0标志为，默认
	assert( s != (char*)-1);
	while(1)
	{
		sem_p(1);
		char buff[128] = {0};
		printf("input:\n");
		fgets(buff,128,stdin);
		strcpy(s,buff);
		sem_v(0);
		if(strncmp(buff,"end",3) == 0)
		{
			break;
		}
	}	
	shmdt(s);
	exit(0);
}
