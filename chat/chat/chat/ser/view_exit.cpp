#include<string.h>
#include<string>
#include<arpa/inet.h>
#include"view_exit.h"
#include<iostream>
#include<mysql/mysql.h>
#include<json/json.h>
using namespace std;

void view_exit::process(Json::Value val,int cli_fd)
{
	_cli_fd = cli_fd;
	MYSQL *mpcon = mysql_init((MYSQL *)0);
	MYSQL_RES *mp_res;
	MYSQL_ROW mp_row;
	
	if(!mysql_real_connect(mpcon,"127.0.0.1","root","123456",NULL,3306,NULL,0))
	{
		cout<<"sql connect fail"<<endl;
		return;
	}
	if(mysql_select_db(mpcon,"chat"))
	{
		cout<<"use chat fail"<<endl;
		return;
	}
	//访问online
	char cmd1[100] = "select * from online where name ='";
	char name[20] = {0};
	string s1 = val["NAME"].asString();
	strcpy(name,s1.c_str());
	strcat(cmd1,name);
	strcat(cmd1,"';");
	//查询该用户是否在online表中,如果在就将他从在线表移除
	if(0 == mysql_real_query(mpcon,cmd1,strlen(cmd1)))
	{
		mp_res = mysql_store_result(mpcon);
		mp_row = mysql_fetch_row(mp_res);
		if(mp_row != 0)
		{
			char cmd3[100] = "delete from online where name ='";
			strcat(cmd3,name);
			strcat(cmd3,"';");
			if(mysql_real_query(mpcon,cmd3,strlen(cmd3)))
			{
				cout<<"delete query fail"<<endl;
			}
			/*Json::Value val;
			val["BUFF"] = "offline sucess";
			//通知客户端exit成功
			send(_cli_fd,val.toStyledString().c_str(),strlen(val.toStyledString().c_str()),0);
*/
		}
		
	}
	else
	{
		return;
		}
}
