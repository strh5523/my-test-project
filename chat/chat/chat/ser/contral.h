#ifndef CONTRAL_H
#define CONTRAL_H
#include"view.h"
#include<iostream>
#include<map>
using namespace std;
typedef class contral
{
	public:
		contral();
		~contral();

		void process(char *buff,int cli_fd);
		void responce();
	private:
		map<int,view*> _map;//model

}Contral,*Pcontral;
#endif
