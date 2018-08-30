#include<stdio.h>
#include<unistd.h>
#include<assert.h>
#include<signal.h>
#include<stdlib.h>
#include<string.h>
#include<pwd.h>
#define PATH /mybin
void printfinfo()
{
	int id;
	id = getuid();
	char * s = "$";
	if(id == 0)
	{
		s = "#";
	}

	struct passwd *p = getpwuid(id);
	if(p == NULL)
	{
		printf("mybash>>$");
		return;
	}
	char hostname[128] = {0};
	gethostname(hostname,128);

	char buff[256] = {0};
	getcwd(buff,256);


	char *sq = "/";
	char* q = strtok(buff,"/");
	while(q != NULL)
	{
		q = sq;
		sq = strtok(NULL,"/");
	}
	// printf("[%s@%s %s]%s",p->pw_name,hostname,q,s);
	if(q == NULL)
	{
		printf("[%s@mylocalhost ~]%s",p->pw_name,s);

	}
	else	
		printf("[%s@mylocalhost%s ~]%s",p->pw_name,q,s);

		fflush(stdout);
}

int main()
{


	while(1)
	{
		printfinfo();
		//printf("[rh@localhost~]$ ");
		//fflush(stdout);

		char argv[32];
		fgets(argv,32,stdin);
		argv[strlen(argv)-1] = 0;

		char* myargv[10] = {0};
		char* s = strtok(argv," ");
		if(s == NULL)
		{
			continue;	
		}
		myargv[0] = s;

		int i = 1;
		for(;(s = strtok(NULL," ")) != NULL;i++)
		{
			myargv[i] = s;
		}
		if(strcmp(argv,"exit") == 0)
		{	
			exit(0);
		}
		else if(strcmp(myargv[0],"cd") == 0)
		{
			if(chdir(myargv[1]) == -1)
			{
				perror("cd error");
			}              
		}
		else
		{

			pid_t pid = fork();
			assert(pid != -1);

			if(pid == 0)
			{
				char path[256] = {0};
				if((strncmp(myargv[0],"./",2) != 0) && (strncmp(myargv[0],"/",1)!=0))
				{
					strcat(path,"/mybin");
				}
				strcat(path,myargv[0]);


				execv(path,myargv);
				perror("execlp error");
				exit(0);
			}

			wait(NULL);
		}

	}
}
