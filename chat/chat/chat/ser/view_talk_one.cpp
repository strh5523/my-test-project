#include<json/json.h>
#include"view_talk_one.h"
#include<iostream>
#include<arpa/inet.h>
#include<mysql/mysql.h>
#include<string>
#include<string.h>
#include<stdio.h>
using namespace std;

void view_talk_one::process(Json::Value val,int cli_fd)
{
	_cli_fd = cli_fd;
	MYSQL *mpcon = mysql_init((MYSQL *)0);
	MYSQL_RES *mp_res;
	MYSQL_ROW mp_row;
	//链接数据库
	if(!mysql_real_connect(mpcon,"127.0.0.1","root","123456",NULL,3306,NULL,0))
	{
		cout<<"mysql connect fail"<<endl;
		return;
	}
	if(mysql_select_db(mpcon,"chat"))
	{
		cout<<"use chat fail"<<endl;
		return;
	}
	//访问usr表    
	char name[20] = {0};
	string s1 = val["RNAME"].asString();
	strcpy(name,s1.c_str());
	char cmd[100] = "select * from usr where name='";	
	strcat(cmd,name);
	strcat(cmd,"';");
	if(0 == mysql_real_query(mpcon,cmd,strlen(cmd)))
	{
		mp_res = mysql_store_result(mpcon);
		mp_row = mysql_fetch_row(mp_res);
		if(mp_row == 0)//usr表中没有此人
		{
			Json:: Value val1;
			val1["TYPE"] = 0;
			val1["BUFF"] = "receiver name not exist";
			send(cli_fd,val1.toStyledString().c_str(),strlen(val1.toStyledString().c_str()),0);	
		}
		else
		{
			//访问在线表
			char cmd1[100] = "select * from online where name='";
			strcat(cmd1,name);
			strcat(cmd1,"';");
			if(0 == mysql_real_query(mpcon,cmd1,strlen(cmd1)))
			{
				mp_res = mysql_store_result(mpcon);
				mp_row = mysql_fetch_row(mp_res);
				//如果不在online表就将消息添加到离线表
				if(mp_row == 0)
				{
					char cmd2[100] = "insert into offline values('";
					strcat(cmd2,name);
					strcat(cmd2,"','");
					string s2 = val["REASON"].asString();
					strcat(cmd2,s2.c_str());
					strcat(cmd2,"');");
					if(0 == mysql_real_query(mpcon,cmd2,strlen(cmd2)))
					{
						Json:: Value val1;
						val1["TYPE"] = 1;
						val1["BUFF"] = "receiver not online";
						send(cli_fd,val1.toStyledString().c_str(),strlen(val1.toStyledString().c_str()),0);	
					}
				}
				else
				{
					int r_fd;//receiver fd
					sscanf(mp_row[0],"%d",&r_fd);
					Json:: Value val1;
					val1["TYPE"] = 2;
					val1["SNAME"] = val["NAME"].asString();
					val1["BUFF"] = val["REASON"].asString();
					send(r_fd,val1.toStyledString().c_str(),strlen(val1.toStyledString().c_str()),0);	
					/*Json::Value val2;//通知客户端发送成功
					val2["TYPE"] = 3;
					val2["BUFF"] = "send sucess";
					send(cli_fd,val2.toStyledString().c_str(),strlen(val2.toStyledString().c_str()),0);	*/
				}

			}
		}
	}
}
