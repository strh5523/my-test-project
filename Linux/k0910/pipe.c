#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<unistd.h>

int main()
{
	int fd[2];
	pipe(fd);

	pid_t pid = fork();
	assert(pid != -1);

	if(pid == 0)
	{
		close(fd[0]);
		while(1)
		{
		char buf[128] = {0};
		fgets(buf,128,stdin);

		write(fd[1],buf,strlen(buf));
		if(strncmp(buf,"end",3) == 0)
		{
			break;
		}
		}
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		while(1)
		{
		char buf[128] = {0};
		int a = read(fd[0],buf,127);
		printf("parent:%s\n",buf);
		if(a == 0)
		{
			break;
		}
		}
		close(fd[0]);
	}

	
	}
