#pragma once
#include"Observer.h"
#include"Commands.h"
#include"Changes.h"
#include"BasicDraw.h"

class View : public Observer 
{
//public for test
public:
	shared_ptr<BasicCommand> addObjectCommand, getLastObjectInformationCommand, drawObjectCommand, getObjectInformationCommand;

public:
	vector<shared_ptr<BasicDraw>>DrawList;
	View();
	~View();
	
	void Update(const int state,shared_ptr<Params> params);
	void SetCommands(vector<shared_ptr<BasicCommand>> commands) 
	{
		int index = 0;
		addObjectCommand = commands[index++];
		drawObjectCommand = commands[index++];
		getLastObjectInformationCommand = commands[index++];
		getObjectInformationCommand = commands[index++];
		//ÃüÁîµÄ°ó¶¨
	}
};
