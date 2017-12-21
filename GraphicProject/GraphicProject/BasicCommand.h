#pragma once
#include<memory>
#include<vector>
#include<string>
#include"Data.h"
#include"Model.h"
using std::shared_ptr;
class BasicCommand {
protected:
	Params params;
	shared_ptr<Model> pmodel;
	Params resultParams;
public:
	BasicCommand(shared_ptr<Model> pmodel = nullptr) :pmodel(pmodel) {}

	void SetParams(const Params& params) {
		this->params = params;
	}

	const Params& GetResults() {
		return resultParams;
	}
	virtual void exec() = 0;
};