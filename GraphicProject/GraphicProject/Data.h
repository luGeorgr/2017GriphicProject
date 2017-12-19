#pragma once
#include<vector>
#include<gl\glut.h>
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

	const vector<int>& GetIntParams() const {
		return intParams;
	}

	const vector<float>& GetFloatParams() const {
		return floatParams;
	}

	const vector<string>& GetStringParams() const {
		return stringParams;
	}
};