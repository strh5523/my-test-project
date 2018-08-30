#include"sem.h"
int static semid = -1;

void sem_init(int a[],int n)
{
	semid = semget((key_t)1234,n,IPC_CREAT | IPC_EXCL|0600);
	if(semid == -1)
	{
		semid = semget((key_t)1234,n,0600);
		if(semid == -1)
		{
			perror("semget error");

		}
	}
	else
	{
		union semun b;
		int i = 0;
		for(;i<n;i++)
		{
			b.val = a[i];
			if(semctl(semid,i,SETVAL,b) == -1)
			{
				perror("semctl error setval");

			}

		}
	}
}
void sem_p(int index)
{
	struct sembuf buf;
	buf.sem_num = index;
	buf.sem_op = -1;
	buf.sem_flg = SEM_UNDO;
	if(semop(semid,&buf,1) == -1)
	{
		perror("semop error");
	}
}

void sem_v(int index)
{
	struct sembuf buf;
	buf.sem_num = index;
	buf.sem_op = 1;
	buf.sem_flg = SEM_UNDO;
	if(semop(semid,&buf,1) == -1)
	{
		perror("semop error");
	}
}

void sem_destroy()
{
	if(semctl(semid,0,IPC_RMID) == -1)
	{
		perror("semctl error");
	}
}
