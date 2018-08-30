#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<assert.h>
#include<fcntl.h>
#include<math.h>
#include<sys/shm.h>
#include<stdlib.h>

int g = 10;
int main()
{
	int a= 0;
	char *s = (char*)malloc(128);
	assert(s != NULL);

	int shmid = shmget((key_t)1234,256,IPC_CREAT|0600);
	void *p = shmat(shmid,NULL,0);
}
