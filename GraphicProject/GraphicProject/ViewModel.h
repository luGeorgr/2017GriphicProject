#pragma once
#include"Observer.h"
#include"Observable.h"
class ViewModel: public Observer, public Observable
{
public:
	ViewModel();
	~ViewModel();
	void Update(const Params& params);

	vector<shared_ptr<BasicCommand>> GetCommands() {
		vector<shared_ptr<BasicCommand>> commands;
		return commands;
	}
};

