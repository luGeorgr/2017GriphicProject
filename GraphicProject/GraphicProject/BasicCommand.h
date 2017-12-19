#pragma once
#include<memory>
#include<vector>
#include<string>
#include"Data.h"
using std::shared_ptr;
class Model;
class BasicCommand {
protected:
	Params params;
	shared_ptr<Model> pmodel;
	Params resultParams;
public:
	BasicCommand(shared_ptr<Model> pmodel = nullptr) :pmodel(pmodel) {}

	void SetParams(const Params& params) {
		this->params.SetParams(params.GetIntParams(), params.GetFloatParams(), params.GetStringParams());
	}
	virtual void exec() = 0;
};