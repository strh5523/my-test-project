#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<string.h>
#include<sys/select.h>
#include<sys/time.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<sys/stat.h>
#include<fcntl.h>

void *fun(void *arg)
{
	int c = (int)arg;
	while(1)
	{
		char buff[128] = {0};
		if(recv(c,buff,127,0)<=0)
		{
			break;
		}


		char * myargv[10] = {0};
		char * s = strtok(buff," ");
		if(s == NULL)
		{
			continue;
		}
		myargv[0] = s;
		int i = 1;
		for(;(s=strtok(NULL," "))!=NULL;i++)
		{
			myargv[i] = s;
		}



		if(strcmp(myargv[0],"get") == 0)
		{

			int fdr = open(myargv[1],O_RDONLY);
			assert(fdr != -1);
			int n = 1;
			int num = 0;
			while(n)
			{
				char buff1[256] = {0};
				n = read(fdr,buff1,256);
				num += n;
			}
			close(fdr);
			int size[1] = {num};
			send(c,size,sizeof(size),0);	//获得文件大小

			int fdr1 = open(myargv[1],O_RDONLY);
			assert(fdr1 != -1);

			int m = 1;
			while(m)
			{	
			
				char buff2[256] = {0};
				m = read(fdr1,buff2,256);
				send(c,buff2,m,0);
			}
		
			close(fdr1);
			continue;

		}
		else if(strcmp(myargv[0],"put") == 0)
		{
			int fdw = open(myargv[1],O_WRONLY | O_CREAT,0600);
			assert(fdw != -1);
			int size[1] = {0};
			recv(c,size,sizeof(size),0);
			while(size[0])
			{
				char tmpbuff[256] = {0};
				recv(c,tmpbuff,256,0);
				int n = write(fdw,tmpbuff,strlen(tmpbuff));
				size[0] -=n;
			}
			close(fdw);
			send(c,"put success",11,0);
			continue;
		}
		else
		{
		
			char argv[] = {0};

			int pipefd[2];
			pipe(pipefd);

			pid_t pid = fork();
			assert(pid != -1);
			//close(pipefd[1]);
			if(pid == 0)
			{
				close(pipefd[0]);
				dup2(pipefd[1],1);		
				dup2(pipefd[1],2);

				if((strncmp(buff,"./",2)!=0)&&(strncmp(buff,"/",1)!=0))
				{	
					strcat(argv,"/bin/");
				}
				strcat(argv,buff);
				execv(argv,myargv);
				perror("execv");
				exit(0);
			
			close(pipefd[1]);
			}
			else
			{
				close(pipefd[1]);
				
			char read_buff[512] = {0};
			read(pipefd[0],read_buff,500);
			if(strlen(read_buff) == 0)
			{
				send(c,"$error$",7,0);
				close(pipefd[0]);
				continue;
			}
			close(pipefd[0]);
			send(c,read_buff,strlen(read_buff),0);
			}
		}
		
	}
		close(c);
		printf("one client close %d\n",c);

}
int socket_create();
int main()
{
	int sockfd = socket_create();
	struct sockaddr_in caddr;
	while(1)
	{
		int len = sizeof(caddr);
		int c = accept(sockfd,(struct sockaddr*)&caddr,&len);
		if(c<0)
		{
			continue;
		}
		printf("accept c=%d,ip=%s,port=%d,\n",c,inet_ntoa(caddr.sin_addr),ntohs(caddr.sin_port));
		pthread_t id;
		pthread_create(&id,NULL,fun,(void*)c);

	}

}
int socket_create()
{
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	assert(sockfd != -1);

	struct sockaddr_in saddr;
	memset(&saddr,0,sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(6000);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int res = bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
	assert(res != -1);

	listen(sockfd,5);

	return sockfd;
}
