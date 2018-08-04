#ifndef VIEW_EXIT
#define VIEW_EXIT
#include"view.h"
class view_exit :public view
{
	public:
		void process(Json::Value val,int cli_fd);
		void responce();
	private:
	//	string reason;
		int _cli_fd;
};
#endif
