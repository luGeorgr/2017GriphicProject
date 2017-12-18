#pragma once
#include"Observer.h"
class View : public Observer 
{
private:
	
public:
	View();
	~View();

	void Update(const Params& params);
	void SetCommands(vector<shared_ptr<BasicCommand>> commands) 
	{
		//ÃüÁîµÄ°ó¶¨
	}
};

