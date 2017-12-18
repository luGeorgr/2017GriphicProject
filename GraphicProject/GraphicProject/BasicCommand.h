#pragma once
#include<memory>
#include<vector>
#include<string>
using std::shared_ptr;
using std::vector;
using std::string;
class Params {
private:
	vector<int> intParams;
	vector<float> floatParams;
	vector<string> stringParams;
public:
	void SetParams(const vector<int>& intParams, const vector<float>& floatParams, const vector<string>& stringParams)
	{
		this->intParams = intParams;
		this->floatParams = floatParams;
		this->stringParams = stringParams;
	}

	const vector<int>& GetIntParams() const{
		return intParams;
	}

	const vector<float>& GetFloatParams() const{
		return floatParams;
	}

	const vector<string>& GetStringParams() const{
		return stringParams;
	}
};
class Model;
class BasicCommand {
protected:
	Params params;
	shared_ptr<Model> pmodel;
public:
	BasicCommand(shared_ptr<Model> pmodel = nullptr) :pmodel(pmodel) {}

	void SetParams(const Params& params) {
		this->params.SetParams(params.GetIntParams(), params.GetFloatParams(), params.GetStringParams());
	}
	virtual void exec() = 0;
};