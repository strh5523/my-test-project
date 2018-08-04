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





const int fd = socket(AF_INET,SOCK_STREAM,0);
char name[NAME_SIZE] = {0};
char pw[PW_SIZE] = {0};

void view_exit()
{
	//told tcp
	Json::Value val;
	val["TYPE"] = 2;
	val["NAME"] = name;
	send(fd,val.toStyledString().c_str(),strlen(val.toStyledString().c_str()),0);
}
void cli_exit()
{
	char buff[10] = "end";
	send(fd,buff,strlen(buff),0);
	close(fd);
}
void view_talk_one(int fd)
{
	char rname[20] = {0};
	cout<<"input receiver name:";
	cin>>rname;
	char message[M_SIZE] = {0};
	cout<<"message:";
	cin>>message;
	Json::Value val;
	val["TYPE"] = 3;
	val["NAME"] = name;
	val["RNAME"] = rname;
	val["REASON"] = message;
	send(fd,val.toStyledString().c_str(),strlen(val.toStyledString().c_str()),0);
}
void *pth_run(void *arg)
{
	while(1)
	{
	char buff[BUFF_SIZE] = {0};
	if(recv(fd,buff,BUFF_SIZE - 1,0) <= 0)
	{
		cout<<"recv error"<<endl;
	}
	Json::Value val;
	Json::Reader read;
	if(read.parse(buff,val) == -1)
	{
		cout<<"json read fail"<<endl;
	}
	if(val["TYPE"].asInt() == 0)
	{
		cout<<"send fail"<<endl;
		cout<<val["BUFF"].asString()<<endl;
	}
	else if(val["TYPE"].asInt() == 1)
	{
		cout<<"send sucess,but"<<endl;
		cout<<val["BUFF"].asString()<<endl;
	}
	else if(val["type"].asInt() == 3)
	{
		cout<<val<<endl;
		cout<<val["BUFF"].asString()<<endl;
	}
	else //someone talk you  
	{
		cout<<"your message from ["<<val["SNAME"].asString()<<"]"<<endl;
		cout<<val["BUFF"].asString()<<endl;

		//reply?
	}
	}
}
void menu()
{
	while(1)
	{
		char choose[10] = {0};
		cout<<"****************welcome to chat********************"<<endl;
		cout<<"****************make your choose in number********"<<endl;
		cout<<"****************1.register************************"<<endl;
		cout<<"****************2.login***************************"<<endl;
		cout<<"****************3.exit****************************"<<endl;
		cin>>choose;

		if(strcmp(choose,"1") == 0)//register
		{
			cout<<"name:";
			cin>>name;
			cout<<"passworld:";
			cin>>pw;
			//create json package
			Json::Value val;
			val["NAME"] = name;
			val["PW"] = pw;
			val["TYPE"] = 0;

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
				cout<<"——————————————————>"<<val2["BUFF"].asString()<<endl<<endl;
			}
		}
		if(strcmp(choose,"2") == 0)//login
		{
			cout<<"name:";
			cin>>name;
			cout<<"passworld:";
			cin>>pw;
			//create json package
			Json::Value val;
			val["NAME"] = name;
			val["PW"] = pw;
			val["TYPE"] = 1;

		   if(-1 == send(fd,val.toStyledString().c_str(),strlen(val.toStyledString().c_str()),0))//send error
		   {
			   cout<<"send error"<<endl;
			   break;
			  }

			char buff[100] = {0};

			if(0 < recv(fd,buff,99,0))
			{
				Json::Value val2;
				Json::Reader read;
				if(read.parse(buff,val2) == -1)
				{
					cout<<"json read fail"<<endl;
				}
				pthread_t id;//libevent fd if someone talk you
				int pth_fd = fd;
				pthread_create(&id,NULL,pth_run,&pth_fd);
				if(val2["RESPOND"].asInt() != 0)
				{
					if(val2["RESPOND"].asInt() == 1)
					{
						cout<<endl<<endl;
						cout<<"——————————————————>"<<val2["BUFF"].asString()<<endl<<endl;
					}
					if(val2["RESPOND"].asInt() == 3)
					{
						cout<<"——————————————————>login sucess"<<endl;
						cout<<"——————————————————>that's your offline respond"<<endl;
						cout<<val2["BUFF"].asString()<<endl<<endl;
					}
					//login sucess
					while(1)
					{
						char ch[10] = {0};
						cout<<"~~~~~~~~~~~~~~~~~~1.talk_one~~~~~~~~~~~~"<<endl;
						cout<<"~~~~~~~~~~~~~~~~~~2.offline~~~~~~~~~~~~~"<<endl;
						cin>>ch;

						if(strcmp(ch,"1") == 0)//talk_one
						{
							view_talk_one(fd);
						}
						if(strcmp(ch,"2") == 0)//exit
						{
							view_exit();
							break;
						}
					}
				}
				else
				{
						cout<<endl<<endl;
						cout<<"——————————————————>"<<val2["BUFF"].asString()<<endl<<endl;
						continue;
				}

			}
		}
		if(strcmp(choose,"3") == 0)
		{
			cli_exit();
			break;
		}
	}
}
void fun(int sig)
{
	view_exit();
	cli_exit();
	signal(SIGINT,SIG_DFL);
}
int main()
{
	//int fd = socket(AF_INET,SOCK_STREAM,0);
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


	signal(SIGINT,fun);
	menu();
	return 0;
}
