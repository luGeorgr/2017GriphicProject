#pragma once
#include"BasicCommand.h"
class DrawobjCommand :public BasicCommand {
public:
	DrawobjCommand(shared_ptr<Model> pmodel = nullptr) : BasicCommand(pmodel) {}
	~DrawobjCommand() {}
	void exec();
};
