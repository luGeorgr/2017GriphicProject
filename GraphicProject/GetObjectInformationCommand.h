#pragma once

#include "BasicCommand.h"

class GetObjectInformationCommand : public BasicCommand {
public:
	GetObjectInformationCommand(shared_ptr<Model> pmodel = nullptr) : BasicCommand(pmodel) {}
	void exec();
};
