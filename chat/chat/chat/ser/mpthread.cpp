#include<iostream>
#include"mpthread.h"
#include<pthread.h>
#include"contral.h"
#include<sys/types.h>
#include<pthread.h>
#include<string.h>
using namespace std;
#define BUFF_SIZE 256

void *pth_run(void *arg);
Mpthread::mpthread(int sock_1)
{
	_sock_1 = sock_1;
	pthread_t id;
	pthread_create(&id,NULL,pth_run,(void*)this);
	_Mcontral  = new contral;
	//启动子线程
	//->pth_run(this)
}

void cli_cb(int fd,short event,void* arg)
{
	Pmpthread mthis = (Pmpthread)arg;
	//recv   ->buff
	char buff[BUFF_SIZE] = {0};
	int c = recv(fd,buff,sizeof(buff)-1,0);
	if(c <= 0 || strncmp(buff,"end",3) == 0)
	{
		//不许要删除事件，epoll会自动删除
		//event_del(mthis->_event_map[fd]);
		map<int,struct event*>::iterator it;
		it = mthis->_event_map.begin();
		for(;it != mthis->_event_map.end();++it)
		{
			if(it->first == fd)
			{
				mthis->_event_map.erase(it);
			}
		}
		cout<<fd<<" client close"<<endl;
		close(fd);
		//event_del(mthis->_event_map[fd]);
	}
	else
	{
		//buff->contral 
		mthis->_Mcontral->process(buff,fd);
	}
}



void sock_1_cb(int fd,short event,void *arg)
{
	//强转
	Pmpthread mthis = (Pmpthread)arg;
	//recv   cli_fd
	int cli_fd;
	if(recv(fd,&cli_fd,sizeof(cli_fd),0) <= 0)
	{
		cout<<"cli_fd recv fail"<<endl;
		return;
	}
	//将cli_fd加入libevent  -》cli_cb()
	struct event* listen_fd = event_new(mthis->_base,cli_fd,EV_READ|EV_PERSIST,cli_cb,mthis);

	event_add(listen_fd,NULL);

	//将事件加入到_event_map

	mthis->_event_map[fd] = listen_fd;
	int size = mthis->_event_map.size();
	send(fd,&size,sizeof(size),0);
}


void *pth_run(void *arg)
{
	Pmpthread mthis = (Pmpthread)arg;

	mthis->_base = event_base_new();
	
	//将sock_1 加入到libevnet  ->sock_1_cb(  ,mthis, )
	struct event* listen_fd = event_new(mthis->_base,mthis->_sock_1,EV_READ|EV_PERSIST,sock_1_cb,mthis);

	event_add(listen_fd,NULL);

	event_base_dispatch(mthis->_base);
}
