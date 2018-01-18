#pragma once
#include"BasicCommand.h"
class AdjustObjectCommand :public BasicCommand {
public:
	AdjustObjectCommand(shared_ptr<Model> pmodel = nullptr) : BasicCommand(pmodel) {}
	void exec();
};