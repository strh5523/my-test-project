#ifndef VIEW_LOGIN
#define VIEW_LOGIN
#include"view.h"
class view_login :public view
{
	public:
		void process(Json::Value val,int cli_fd);
		//void responce();
	private:
		//string reason;
		int _cli_fd;
};
#endif
