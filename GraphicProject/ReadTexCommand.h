#include "BasicCommand.h"

class ReadTexCommand :public BasicCommand {


public:
	ReadTexCommand(shared_ptr<Model> pmodel = nullptr) :BasicCommand(pmodel) {
		
	}

	~ReadTexCommand() {}
	void exec();
};