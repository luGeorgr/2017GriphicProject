#pragma once
#include"BasicCommand.h"
class SetObjectAttributeCommand :public BasicCommand
{
public:
	SetObjectAttributeCommand(shared_ptr<Model> pmodel = nullptr) : BasicCommand(pmodel) {}
	void exec();
};

