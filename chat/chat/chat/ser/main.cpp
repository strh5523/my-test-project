#include<iostream>
#include<errno.h>
#include"tcpsever.h"
#include"contral.h"
#include"public.h"
#include"view_exit.h"
#include"view.h"
#include"view_login.h"
#include"view_register.h"
#include"view_talk_one.h"
using namespace std;
#define IP_SIZE 30
#define PTH_NUM_SIZE 4

int main(int argc,char **argv)
{
	if(argc < 4)
	{
		cerr<<"arg not enough;errno:"<<errno<<endl;
		return 0;
	}

	//解析参数   ip   port   pth_num
	int num;
	sscanf(argv[1],"%d",&num);
	int pth_num = num;
	unsigned short port;
	sscanf(argv[2],"%d",&port);
	
	//构造服务器对象
	tcpsever ser(argv[3],port,pth_num);

	//运行服务器
	ser.run();

	return 0;
}
