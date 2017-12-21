#pragma once
#include "BasicCommand.h"
class DrawObjectCommand :public BasicCommand {
	DrawObjectCommand(shared_ptr<Model> pmodel = nullptr) :BasicCommand(pmodel)
	{}
	~DrawObjectCommand()
	{}
	void exec();
};