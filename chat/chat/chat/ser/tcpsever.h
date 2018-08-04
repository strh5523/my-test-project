#ifndef TCPSEVER_H
#define TCPSEVER_H
#include<iostream>
#include<vector>
#include<map>
#include<arpa/inet.h>
#include<event.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<pthread.h>
using namespace std;

class Myint2
{
public:
		Myint2(int ar0=0,int ar1=0)
		:_ar0(ar0),_ar1(ar1){}
		~Myint2(){}

		int _ar0;
		int _ar1;

};
class tcpsever
{
	public:
		tcpsever(char *ip,unsigned short port,int pth_num);
		~tcpsever();
		void run();
		void create_socket_pair();
		void create_pth();

	private:
		struct event_base* _base;//libevent
		int _listen_fd;//listenfd
		int _pth_num;//线程个数
		vector<Myint2> _sockpair_base;//socketpair
		map<int,int> _pth_num_map;//线程监听数量的map表
		friend void listen_cb(int fd,short event,void *arg);
		friend void sock_0_cb(int fd,short event,void *arg);
}/*Tcpsever,*Ptcpsever*/;
#endif
