#ifndef VIEW_REGISTER
#define VIEW_REGISTER
#include"view.h"
class view_register :public view
{
	public:
		void process(Json::Value val,int cli_fd);
		//void responce();
	private:
		//string reason;
		int _cli_fd;
};
#endif
