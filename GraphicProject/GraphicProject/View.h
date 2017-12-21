#pragma once
#include"Observer.h"
#include"Commands.h"
#include"Changes.h"
#include"Draw.h"

class View : public Observer 
{
//public for test
public:
	shared_ptr<BasicCommand> drawCubeCommand, getLastObjectInformationCommand;

public:
	vector<Draw>DrawList;
	View();
	~View();
	
	void Update(const int state);
	void SetCommands(vector<shared_ptr<BasicCommand>> commands) 
	{
		int index = 0;
		drawCubeCommand = commands[index++];
		getLastObjectInformationCommand = commands[index++];
		//ÃüÁîµÄ°ó¶¨
	}
};
