#pragma once
#include "BasicCommand.h"
class DrawCubeCommand :
	public BasicCommand
{
public:
	DrawCubeCommand(shared_ptr<Model> pmodel = nullptr) :BasicCommand(pmodel) 
	{}
	~DrawCubeCommand() 
	{}
	void exec();
};

