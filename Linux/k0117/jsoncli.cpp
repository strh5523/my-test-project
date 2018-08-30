#include<iostream>
#include<string.h>
#include<string>
#include<json/json.h>
#include<errno.h>
#include<arpa/inet.h>
using namespace std;

int main()
{
	int fd = socket(AF_INET,SOCK_STREAM,0);
	if(-1 == fd)
	{
		cerr<<"clifd creat fail;errnoz:"<<errno<<endl;
		return 0;
	}

	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(5000);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(-1 == connect(fd,(struct sockaddr*)&saddr,sizeof(saddr)))
	{
		cerr<<"clifd connect fail;errno:"<<errno<<endl;
		return 0;
	}

	//创建json包
	Json::Value val;
	val["name"] = "zhangsan";
	val["pw"] = "123456";

	//发送数据
	if(-1 == send(fd,val.toStyledString().c_str(),strlen(val.toStyledString().c_str()),0))
	{
		cerr<<"send reason fail;errno:"<<errno<<endl;
		return 0;
	}

	char buff[100] = {0};
	//接收数据
	if(0 < recv(fd,buff,99,0))
	{
		//解析json包
		Json::Value root;
		Json::Reader read;

		if(-1 == read.parse(buff,root))
		{
			cerr<<"json prase fail;errno:"<<errno<<endl;
			return 0;
		}

		//输出json
	//	cout<<root.asString()<<endl;
		cout<<"reason:"<<root["reason"].asString()<<endl;
	}
	return 0;
}
