#pragma once

#include "Model.h"
#include "Observer.h"
#include "Observable.h"
#include "Changes.h"
#include "Commands.h"

class ViewModel: public Observer, public Observable {
private:
	shared_ptr<Model> pmodel;
	shared_ptr<AddObjectCommand> addObjectCommand;
	shared_ptr<BasicCommand> drawObjectCommand;
	shared_ptr<BasicCommand> getLastObjectInformationCommand;
	shared_ptr<BasicCommand> getObjectInformationCommand;
	shared_ptr<BasicCommand> readTexCommand;
	shared_ptr<BasicCommand> drawobjCommand;
	shared_ptr<BasicCommand> adjustobjectCommand;
	shared_ptr<BasicCommand> addOrDeleteLightCommand;
	shared_ptr<BasicCommand> setObjectAttributeCommand;
public:
	ViewModel(shared_ptr<Model> pmodel) : pmodel(pmodel) {}
	~ViewModel() {}
	void Update(const int state, shared_ptr<Params> params);

	vector<shared_ptr<BasicCommand> > GetCommands() {
		vector<shared_ptr<BasicCommand> > commands;
		addObjectCommand = shared_ptr<AddObjectCommand>(new AddObjectCommand(pmodel));
		drawObjectCommand = shared_ptr<DrawObjectCommand>(new DrawObjectCommand(pmodel));
		getLastObjectInformationCommand = shared_ptr<GetLastObjectInformationCommand>(new GetLastObjectInformationCommand(pmodel));
		getObjectInformationCommand = shared_ptr<GetObjectInformationCommand>(new GetObjectInformationCommand(pmodel));
		readTexCommand = shared_ptr<ReadTexCommand>(new ReadTexCommand(pmodel));
		drawobjCommand = shared_ptr<DrawobjCommand>(new DrawobjCommand(pmodel));
		adjustobjectCommand= shared_ptr<AdjustObjectCommand>(new AdjustObjectCommand(pmodel));
		addOrDeleteLightCommand = shared_ptr<AddOrDeleteLightCommand>(new AddOrDeleteLightCommand(pmodel));
		setObjectAttributeCommand = shared_ptr<SetObjectAttributeCommand>(new SetObjectAttributeCommand(pmodel));
		commands.push_back(addObjectCommand);
		commands.push_back(drawObjectCommand);
		commands.push_back(getLastObjectInformationCommand);
		commands.push_back(getObjectInformationCommand);
		commands.push_back(readTexCommand);
		commands.push_back(drawobjCommand);
		commands.push_back(adjustobjectCommand);
		commands.push_back(addOrDeleteLightCommand);
		commands.push_back(setObjectAttributeCommand);
		return commands;
	}
};

