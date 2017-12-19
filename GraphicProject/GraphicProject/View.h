#pragma once
#include"Observer.h"
#include"BasicCommand.h"
#include"Draw.h"
class View : public Observer 
{
private:
	vector<Draw>DrawList;
public:
	View();
	~View();

	void Update(const Params& params);
	void SetCommands(vector<shared_ptr<BasicCommand>> commands) 
	{
		//ÃüÁîµÄ°ó¶¨
	}
};

