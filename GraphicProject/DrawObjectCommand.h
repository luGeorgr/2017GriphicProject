#pragma once

#include "BasicCommand.h"
#include "DrawOneObjectWithOneMethodCommand.h"

class DrawObjectCommand :public BasicCommand {
// intParams the first 5 number are drawmethods(-1 stop), then objects followed, -1, tex index1 index2 
private:
	shared_ptr<DrawOneObjectWithOneMethodCommand> drawOneObjectWithOneMethodCommand;

public:
	DrawObjectCommand(shared_ptr<Model> pmodel = nullptr) :BasicCommand(pmodel) {
		drawOneObjectWithOneMethodCommand = 
			shared_ptr<DrawOneObjectWithOneMethodCommand>(new DrawOneObjectWithOneMethodCommand(pmodel));
	}

	~DrawObjectCommand() {}
	void exec();
};
