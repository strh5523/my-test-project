#include<arpa/inet.h>
#include"view_register.h"
#include<iostream>
#include<mysql/mysql.h>
#include<json/json.h>
#include<string>
#include<string.h>
using namespace std;

void view_register::process(Json::Value val,int cli_fd)
{
	_cli_fd = cli_fd;
	MYSQL *mpcon = mysql_init((MYSQL *)0);
	MYSQL_RES *mp_res;
	MYSQL_ROW mp_row;
	//链接mysql
	if(!mysql_real_connect(mpcon,"127.0.0.1","root","123456",NULL,3306,NULL,0))
	{
		cout<<"sql connect fail"<<endl;
		return;
	}
	//连接chat数据库
	if(mysql_select_db(mpcon,"chat"))
	{
		cout<<"use chat fail"<<endl;
		return;
	}
	//访问usr表    
	char name[20] = {0};
	string s1 = val["NAME"].asString();
	strcpy(name,s1.c_str());
	char cmd[100] = "select * from usr where name='";	
	strcat(cmd,name);
	strcat(cmd,"';");
	//如果usr表中有该用户名  mp_row ==0 没找到
	if(0 == mysql_real_query(mpcon,cmd,strlen(cmd)))
	{
		mp_res = mysql_store_result(mpcon);
		mp_row =  mysql_fetch_row(mp_res);
		if(mp_row == 0)
		{
			char cmd3[100] = "insert into usr values('";
			strcat(cmd3,name);
			strcat(cmd3,"','");
			char pw2[20] = {0};
			string s3 = val["PW"].asString();
			strcpy(pw2,s3.c_str());
			strcat(cmd3,pw2);
			strcat(cmd3,"');");
			//将该用户添加在usr表中
			if(0 == mysql_real_query(mpcon,cmd3,strlen(cmd3)))
			{
				//通知客户端注册成功
				Json::Value val;
				val["RESPOND"] = 1;
				val["BUFF"] = "register sucess";
				send(_cli_fd,val.toStyledString().c_str(),strlen(val.toStyledString().c_str()),0);
			}
		}
		else
		{
				Json::Value val;
				val["RESPOND"] = 0;
				val["BUFF"] = "user name repeat";
				send(_cli_fd,val.toStyledString().c_str(),strlen(val.toStyledString().c_str()),0);
		}
	}
}
