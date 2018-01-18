#pragma once

#include "BasicCommand.h"
#include "DrawOneObjectWithOneMethodCommand.h"

class DrawObjectCommand :public BasicCommand {
// intParams the first inputs are drawmethods(-1 stop), then objects follows, -1, texindex1 texindex2 
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
