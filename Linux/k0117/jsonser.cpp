//服务器端程序
#include<iostream>
#include<string.h>
#include<string>
#include<arpa/inet.h>
#include<errno.h>
#include<json/json.h>
#include<sys/socket.h>
using namespace std;
int main()
{
	//创建服务器
	int fd = socket(AF_INET,SOCK_STREAM,0);
	if(-1 == fd)
	{
		cerr<<"fd creat fail;errno:"<<endl;
		return 0;
	}

	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(5000);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	//绑定
	if(-1 == bind(fd,(struct sockaddr*)&saddr,sizeof(saddr)))
	{
		cerr<<"fd bind fail;errno:"<<errno<<endl;
		return 0;
	}

	//监听
	if(- 1 == listen(fd,20))
	{
		cerr<<"fd listen fail;errno:"<<endl;
		return 0;
	}

	//连接客户端
	struct sockaddr_in caddr;
	socklen_t len = sizeof(caddr);
	int clifd = accept(fd,(struct sockaddr*)&caddr,&len);
	if(-1 == clifd)
	{
		cerr<<"accept client fail;errno:"<<errno<<endl;
		return 0;
	}

	//接收消息
	char buff[100] = {0};
	if(0 < recv(clifd,buff,99,0))
	{
	//	cout<<buff<<endl;

		//解析json
		Json::Value val;
		Json::Reader read;
		if(-1 == read.parse(buff,val))
		{
			cerr<<"read fail;errno:"<<errno<<endl;
			return 0;
		}
		//cout<<val.asString()<<endl;
		cout<<"name:"<<val["name"].asString()<<endl;
		cout<<"pw:"<<val["pw"].asString()<<endl;

		//发送消息
		Json::Value root;
		root["reason"] = "ok";
		if(-1 == send(clifd,root.toStyledString().c_str(),strlen(root.toStyledString().c_str()),0))
		{
			cerr<<"send reason fail;errno:"<<errno<<endl;
			return 0;
		}
	}
	return 0;
}
