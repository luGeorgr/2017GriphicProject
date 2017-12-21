#pragma once
#include"Model.h"
#include"Observer.h"
#include"Observable.h"
#include"Changes.h"
#include"Commands.h"
class ViewModel: public Observer, public Observable
{
private:
	shared_ptr<Model> pmodel;
	shared_ptr<AddObjectCommand> addObjectCommand;
	shared_ptr<GetLastObjectInformationCommand> getLastObjectInformationCommand;
public:
	ViewModel(shared_ptr<Model> pmodel) : pmodel(pmodel)
	{
	}
	~ViewModel()
	{}
	void Update(const int state);

	vector<shared_ptr<BasicCommand>> GetCommands() {
		vector<shared_ptr<BasicCommand>> commands;
		addObjectCommand = shared_ptr<AddObjectCommand>(new AddObjectCommand(pmodel));
		getLastObjectInformationCommand = shared_ptr<GetLastObjectInformationCommand>(new GetLastObjectInformationCommand(pmodel));

		commands.push_back(addObjectCommand);
		commands.push_back(getLastObjectInformationCommand);
		return commands;
	}
};

