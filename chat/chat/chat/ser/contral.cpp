#include<iostream>
#include<json/json.h>
#include"contral.h"
#include"public.h"
#include"view_register.h"
#include"view_login.h"
#include"view_exit.h"
#include"view_talk_one.h"
#include"view.h"
using namespace std;
contral::contral()
{
	_map.insert(make_pair(MSG_TYPE_REGISTER,new view_register()));
	_map.insert(make_pair(MSG_TYPE_LOGIN,new view_login()));
	_map.insert(make_pair(MSG_TYPE_EXIT,new view_exit()));
	_map.insert(make_pair(MSG_TYPE_TALK_ONE,new view_talk_one()));
}
contral::~contral()
{
	map<int,view*>::iterator it;
	it = _map.begin();
	for(;it != _map.end();++it)
	{
		delete (it->second);
	}
}
void contral::process(char *buff,int cli_fd)
{
	//Json解析    -》TYPE
	Json::Value val;
	Json::Reader read;
	if(read.parse(buff,val) == -1)
	{
		cout<<"read fail"<<endl;
		return;
	}
	_map[val["TYPE"].asInt()]->process(val,cli_fd);
	//_map[val["TYPE"].asInt()]->responce();

}
