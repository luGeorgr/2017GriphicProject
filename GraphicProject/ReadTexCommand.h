#include "BasicCommand.h"

class ReadTexCommand :public BasicCommand {
	// intParams the first 5 number are drawmethods(-1 stop), then objects followed 

public:
	ReadTexCommand(shared_ptr<Model> pmodel = nullptr) :BasicCommand(pmodel) {
		
	}

	~ReadTexCommand() {}
	void exec();
};