#pragma once
#include "BasicCommand.h"
class AddObjectCommand :
	public BasicCommand
{
public:
	AddObjectCommand(shared_ptr<Model> pmodel = nullptr) :BasicCommand(pmodel)
	{}
	~AddObjectCommand()
	{}
	void exec();
};

