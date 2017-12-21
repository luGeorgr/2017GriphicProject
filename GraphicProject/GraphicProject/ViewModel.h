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
	shared_ptr<DrawCubeCommand> drawCubeCommand;
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
		drawCubeCommand = shared_ptr<DrawCubeCommand>(new DrawCubeCommand(pmodel));
		getLastObjectInformationCommand = shared_ptr<GetLastObjectInformationCommand>(new GetLastObjectInformationCommand(pmodel));

		commands.push_back(drawCubeCommand);
		commands.push_back(getLastObjectInformationCommand);
		return commands;
	}
};

