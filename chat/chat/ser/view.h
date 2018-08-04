#ifndef VIEW_H
#define VIEW_H
#include<json/json.h>
class view
{
	public:
		virtual void process(Json::Value val,int cli_fd)=0;
	//	virtual void responce() = 0;
};
#endif
