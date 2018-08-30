#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<string.h>
#include<event.h>
#include<signal.h>
#include<time.h>

void sig_fun(int fd,short ev,void* arg)
{
	printf("sig=%d\n",fd);
}
void time_fun(int fd,short ev,void*arg)
{
	printf("time out\n");
}
void io_cb(int fd,short ev,void* arg)
{
	if(ev & EV_READ)
	{
		char buff[128] = {0};
		if(recv(fd,buff,127,0)<=0)
		{
			//bug
			printf("client close\n");
			return;
		}
		printf("read(fd=%d)=%s\n",fd,buff);
		send(fd,"ok",2,0);
	}

}
void accept_cb(int fd,short ev,void*arg)
{
	if(ev & EV_READ)
	{
		struct sockaddr_in caddr;
		int len = sizeof(caddr);
		int c = accept(fd,(struct sockaddr*)&caddr,&len);
		if(c<0)
		{
			return ;
		}
		struct event_base *base = (struct event_base *)arg;
		printf("accept c=%d\n",c);

		struct event *ev_io = event_new(base,c,EV_READ|EV_PERSIST,io_cb,NULL);
		event_add(ev_io,NULL);
	}
}
int create_sock()
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
int main()
{
	int sockfd = create_sock();
	struct event_base * base = event_init();
	assert(base != NULL);

	struct event* ev_sock = event_new(base,sockfd,EV_READ|EV_PERSIST,accept_cb,(void*)base);
	assert(ev_sock != NULL);

	event_add(ev_sock,NULL);
	//struct event * ev_sig = evsignal_new(base,SIGINT,sig_fun,NULL);
	//event_add(ev_sig,NULL);

//	struct timeval tv = {5,0};
//	struct event* ev_time = evtimer_new(base,time_fun,NULL);
//	event_add(ev_time,&tv);

	event_base_dispatch(base);
	event_free(ev_sock);
//	event_free(ev_time);
	event_base_free(base);
}
