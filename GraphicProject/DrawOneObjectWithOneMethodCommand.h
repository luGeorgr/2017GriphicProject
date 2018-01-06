#pragma once

#include "BasicCommand.h"

class DrawOneObjectWithOneMethodCommand :public BasicCommand {
public:
	DrawOneObjectWithOneMethodCommand(shared_ptr<Model> pmodel = nullptr) : BasicCommand(pmodel){}
	void exec();
};
