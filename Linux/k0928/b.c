#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<sys/shm.h>
int main()
{
	int shmid = shmget((key_t)1234,256,IPC_CREAT | 0600);
	assert(shmid != -1);
	printf("shmid=%d\n",shmid);
	int a[2] = {1,0};
	int n = 2;
	sem_init(a,n);
	char * s = (char*)shmat(shmid,NULL,0);//NULL不指定在进程中的地址位置，0标志为，默认
	assert( s != (char*)-1);

	//strcpy(s,"hello");
	while(1)
	{
		sem_p(0);
		if(strncmp(s,"end",3) == 0)
		{
			break;
		}
		printf("read:%s\n",s);
		sem_v(1);
		//sleep(1);
	}
	shmdt(s);
	sem_destroy();
	exit(0);
	}
