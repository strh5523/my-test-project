#ifndef VIEW_TALK_ONE
#define VIEW_TALK_ONE
#include"view.h"
class view_talk_one :public view
{
	public:
		void process(Json::Value val,int cli_fd);
		void responce();
	private:
		//string reason;
		int _cli_fd;
};
#endif
