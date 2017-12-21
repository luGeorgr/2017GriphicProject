#pragma once
#include"BasicCommand.h"
class GetLastObjectInformationCommand : public BasicCommand
{
public:
	GetLastObjectInformationCommand(shared_ptr<Model> pmodel = nullptr) :BasicCommand(pmodel)
	{}
	void exec();
};