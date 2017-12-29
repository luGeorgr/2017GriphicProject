#pragma once
#include<vector>
#include<gl/glut.h>


using std::vector;
using std::string;
class Params {
private:
	vector<int> intParams;
	vector<float> floatParams;
	vector<string> stringParams;
	vector<vector<float>> vfloatParams;
public:
	void SetIntParams(const vector<int>& intParams){
		this->intParams = intParams;
	}

	void SetFloatParams(const vector<float>& floatParams) {
		this->floatParams = floatParams;
	}

	void SetStringParams(const vector<string>& stringParams) {
		this->stringParams = stringParams;
	}


	void SetVfloatParmas(const vector<vector<float>>& vfloatParams) {
		this->vfloatParams = vfloatParams;
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


	const vector<vector<float>>& GetVfloatParams() const {
		return vfloatParams;
	}
};