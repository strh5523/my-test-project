#include<arpa/inet.h>
#include"view_login.h"
#include<iostream>
#include<mysql/mysql.h>
#include<json/json.h>
#include<string>
#include<stdio.h>
#include<string.h>
using namespace std;

void view_login::process(Json::Value val,int cli_fd)
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
	if(0 == mysql_real_query(mpcon,cmd,strlen(cmd)))//查询成功
	{
		//接收返回的指令
		mp_res = mysql_store_result(mpcon);
		//返回1行
		mp_row = mysql_fetch_row(mp_res);
		if(mp_row == 0)            //usr表中没有该用户
		{
			Json::Value val;
			val["RESPOND"] = 0;
			val["BUFF"] = "user name error";
			send(_cli_fd,val.toStyledString().c_str(),strlen(val.toStyledString().c_str()),0);
		}
		else
		{

			char usrpw[20] = {0};
			string s2 = val["PW"].asString();
			strcpy(usrpw,s2.c_str());
			if(strcmp(usrpw,mp_row[1]) != 0)
			{
				//密码不正确
				Json::Value val;
				val["RESPOND"] = 0;
				val["BUFF"] = "user passworld error";
				send(_cli_fd,val.toStyledString().c_str(),strlen(val.toStyledString().c_str()),0);
			}
			else
			{

				//如果密码正确就访问online
				char cmd1[100] = "select * from online where name ='";
				strcat(cmd1,name);
				strcat(cmd1,"';");
				//查询该用户是否在online表中
				if(mysql_real_query(mpcon,cmd1,strlen(cmd1)) == 0)
				{
					mp_res = mysql_store_result(mpcon);
					mp_row = mysql_fetch_row(mp_res);

					char cmd3[100] = "insert into online values('";
					char ch[20] = {0};
					sprintf(ch,"%d",cli_fd);
					strcat(cmd3,ch);
					strcat(cmd3,"','");
					strcat(cmd3,name);
					strcat(cmd3,"');");
					//如果不在表中，就将该用户添加在online表中
					if(mp_row == 0)
					{
						if(mysql_real_query(mpcon,cmd3,strlen(cmd3)) == 0)
						{
							//访问offline
							char cmd4[100] = "select * from offline where name ='";
							strcat(cmd4,name);
							strcat(cmd4,"';");
							//如果有离线消息，就发送给客户端
							if(0 == mysql_real_query(mpcon,cmd4,strlen(cmd4)))
							{

								mp_res = mysql_store_result(mpcon);
								mp_row = mysql_fetch_row(mp_res);
								if(mp_row != 0)//json包
								{
									//发送离线消息
									Json::Value val;
									val["RESPOND"] = 3;
									val["BUFF"] = mp_row[1];
									send(_cli_fd,val.toStyledString().c_str(),strlen(val.toStyledString().c_str()),0);
									//发送完之后删除离线消息
									char cmd4[100] = "delete from offline where name='";
									strcat(cmd4,name);
									strcat(cmd4,"';");
									mysql_real_query(mpcon,cmd4,strlen(cmd4));
								}
								else
								{
									//通知客户端登录成功
									Json::Value val;
									val["RESPOND"] = 1;
									val["BUFF"] = "login sucess";
									send(_cli_fd,val.toStyledString().c_str(),strlen(val.toStyledString().c_str()),0);
								}
							}
						}
					}
						else
						{
							//online表中有数据
							Json::Value val;
							val["RESPOND"] = 0;
							val["BUFF"] = "login again";
							send(_cli_fd,val.toStyledString().c_str(),strlen(val.toStyledString().c_str()),0);
						}
					
				}
			}




		}
	}
}
