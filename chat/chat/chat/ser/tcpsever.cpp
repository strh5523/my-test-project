#include"tcpsever.h"
#include"mpthread.h"
tcpsever::tcpsever(char *ip,unsigned short port,int pth_num)
{
	//创建服务器
	
		int listenfd = socket(AF_INET,SOCK_STREAM,0);
		if(listenfd == -1)
		{
			cout<<"socket creat fail"<<endl;
		}


		struct sockaddr_in saddr;
		saddr.sin_family = AF_INET;
		saddr.sin_port = htons(port);
		saddr.sin_addr.s_addr = inet_addr(ip);

		if(bind(listenfd,(struct sockaddr*)&saddr,sizeof(saddr)) == -1)
		{
			cout<<"bind failed"<<endl;
		}
		
		listen(listenfd,5);
	

	_listen_fd = listenfd;
	_pth_num = pth_num;

	//初始化libevent
	_base = event_base_new();

}

void listen_cb(int fd,short event,void *arg)
{

	//accept;
	tcpsever *mthis = (tcpsever*)arg;
	struct sockaddr_in caddr;
	socklen_t len = sizeof(caddr);
	int cli_fd = accept(fd,(struct sockaddr*)&caddr,&len);
	if(-1 == cli_fd)
	{
		cout<<"accept faile"<<endl;
		return;
	}
	cout<<cli_fd<<" client connect"<<endl;
	//map.find
	map<int,int>::iterator it;
	map<int,int>::iterator it2;
	it = mthis->_pth_num_map.begin();
	it2 = it;
	int min = it->second;
	for(;it != mthis->_pth_num_map.end();++it)
	{
		if(it->second < min)
		{
			it2 = it;
			min = it->second;
			
		}
	}
	//发送给子线程
	send(it2->first,&cli_fd,sizeof(cli_fd),0);

}

void tcpsever::run()
{
	//创建socketpair
	create_socket_pair();

	//启动线程
	create_pth();

	//将监听套接子libevent
	
	struct event * listen_event = event_new(_base,_listen_fd,EV_READ|EV_PERSIST,listen_cb,this);
		if(NULL == listen_event)
		{
			cout<<"event listenfd  new fail"<<endl;
		}

	event_add(listen_event,NULL);
	//循环监听
	
	event_base_dispatch(_base);
}

void tcpsever::create_pth()
{	
	//vector<Myint2>::iterator it;
	//it = _sockpair_base.begin();
	for(int i=0;i<_pth_num;i++)
	{
		//Mpthread pth(it->_ar1);
		Pmpthread p = new Mpthread(_sockpair_base[i]._ar1);
	}
}

void sock_0_cb(int fd,short event,void* arg)
{

	//强转参数
	tcpsever *mthis = (tcpsever*)arg;
	//recv   当前对应线程的监听量num
	int num = 0;
	if(recv(fd,&num,4,0) > 0)
	{
		//更新到map表
		mthis->_pth_num_map[fd] =  num;
	}
}

void tcpsever::create_socket_pair()
{

		

	//申请
	for(int i = 0; i < _pth_num;i++)
	{
		int socket_pair[2];
		if(socketpair(AF_UNIX,SOCK_STREAM,0,socket_pair) == -1)
		{
			cout<<"socketpair failed"<<endl;
		}
		Myint2 myint(socket_pair[0],socket_pair[1]);

		_sockpair_base.push_back(myint);

		_pth_num_map.insert(make_pair(socket_pair[0],0));


		//将socketpair0端加入到libevent
	

		struct event * listen_event = event_new(_base,socket_pair[0],EV_READ|EV_PERSIST,sock_0_cb,this);
		if(NULL == listen_event)
		{
			cout<<"event sockpair0 new fail"<<endl;
		}

		event_add(listen_event,NULL);
		
	}
}

 
tcpsever::~tcpsever()
{
	
}
