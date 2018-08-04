//client
#include<iostream>
#include<string.h>
#include<string>
#include<json/json.h>
#include<errno.h>
#include<arpa/inet.h>
#include<signal.h>
#include<event.h>
#include<pthread.h>
using namespace std;
#define NAME_SIZE 20
#define PW_SIZE 20
#define BUFF_SIZE 256
#define M_SIZE 256  //message size





void menu(int fd, int i)
{
			char name[20] = "stu";
			char pw[20] = "123456";
			char ch[10] = {0};
			sprintf(ch,"%d",i);
			cout<<ch<<endl;
			strcat(name,ch);
			cout<<name;
			//create json package
			Json::Value val;
			val["NAME"] = name;
			val["PW"] = pw;
			val["TYPE"] = 0;
//reguister
			send(fd,val.toStyledString().c_str(),strlen(val.toStyledString().c_str()),0);

			char buff[100] = {0};

			if(0 < recv(fd,buff,99,0))
			{
				Json::Value val2;
				Json::Reader read;
				if(read.parse(buff,val2) == -1)
				{
					cout<<"json read fail"<<endl;
				}
				cout<<endl<<endl;
				cout<<"——————————————————>"<<i<<val2["BUFF"].asString()<<endl<<endl;
			}
}
int main()
{
	int i=0;
	for(;i < 10000;i++)
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

		cout << i << endl;
		menu(fd,i);
	}
	return 0;
}
