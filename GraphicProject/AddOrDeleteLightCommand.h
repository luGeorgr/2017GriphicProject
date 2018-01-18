#pragma once
#include"BasicCommand.h"
class AddOrDeleteLightCommand :public BasicCommand {
public:
	AddOrDeleteLightCommand(shared_ptr<Model> pmodel = nullptr) : BasicCommand(pmodel) {}
	~AddOrDeleteLightCommand() {}
	void exec();
};