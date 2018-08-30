#include"sem.h"
static int semid = -1;
void init()
{
	semid = semget((key_t)1234,1,IPC_CREAT | IPC_EXCL | 0600);
	if(semid == -1)
	{
		semid = semget((key_t)1234,1,0600);
		if(semid == -1)
		{
			perror("semget error");
		}
	}

	else
	{
		union semun a;
		a.val = 1;
		if(semctl(semid,0,SETVAL,a) == -1)
		{
			perror("semctl error");
		}
	}
}

void sem_p()
{
//	semid = semget((key_t)1234,1,0600);
	struct sembuf sem_p;
	sem_p.sem_num = 0;
	sem_p.sem_op = -1;
	sem_p.sem_flg = SEM_UNDO;
	if(semop(semid,&sem_p,1) == -1)
	{
		perror("semop error");
		exit(0);
	}

}
void sem_v()
{
//	semid = semget((key_t)1234,1,0600);
	struct sembuf sem_v;
	sem_v.sem_num = 0;
	sem_v.sem_op = 1;
	sem_v.sem_flg = SEM_UNDO;
	if(semop(semid,&sem_v,1) == -1)
	{
		perror("semop error");
	}
}
void sem_destory()
{
	//union semun b;
	if(semctl(semid,0,IPC_RMID) == -1)
	{
		perror("semctl error");
	}
}




