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

#define MAXFD 10
void fds_init(int fds[])
{
	int i = 0;
	for(;i<MAXFD;i++)
	{
		fds[i] = -1;
	}
}
void fds_add(int fds[],int fd)
{
	int i = 0;
	for(;i<MAXFD;i++)
	{
		if(fds[i] == -1)
		{
			fds[i] = fd;
			break;
		}
	}
}

void fds_del(int fds[],int fd)
{
	int i = 0;
	for(;i<MAXFD;i++)
	{
		if(fds[i] = fd)
		{
			fds[i] = -1;
		}
	}
}
int socket_create();
int main()
{
	int sockfd = socket_create();
	int fds[MAXFD];


	fd_set fdset;

	fds_init(fds);
	fds_add(fds,sockfd);
	while(1)
	{
		FD_ZERO(&fdset);
		int maxfd = -1;

		int i = 0;
		for(;i<MAXFD;i++)
		{
			if(fds[i] != -1)
			{
				FD_SET(fds[i],&fdset);
				if(maxfd<fds[i])
				{
					maxfd = fds[i];
				}
			}
		}
		struct timeval tv = {5,0};

		int n = select(maxfd+1,&fdset,NULL,NULL,&tv);
		if(n == -1)
		{
			perror("select error");
			continue;
		}
		else if(n == 0)
		{
			printf("time out\n");
			continue;
		}
		else
		{
			int i = 0;
			for(;i<MAXFD;i++)
			{
				if(fds[i] == -1)
				{
					continue;
				}
				if(FD_ISSET(fds[i],&fdset))
				{

					if(fds[i] == sockfd)
					{
						struct sockaddr_in caddr;
						int len = sizeof(caddr);
						int c = accept(sockfd,(struct sockaddr*)&caddr,&len);
						fds_add(fds,c);

					}
					else
					{
						char buff[128] = {0};
						if(recv(fds[i],buff,1,0)<=0)
						{
							
							printf("cli close\n");
							fds_del(fds,fds[i]);
							close(fds[i]);
						}
						else
						{
							printf("%s\n",buff);
							send(fds[i],"ok",2,0);
						}
						
					}
				}
				}
		}
			
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
	saddr.sin_addr.s_addr = inet_addr("192.168.31.63");

	int res = bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
	assert(res != -1);

	listen(sockfd,5);

	return sockfd;
}
