#pragma once

#include <vector>
#include <gl/glut.h>
#include <memory>
#include "Texture.h"

using std::vector;
using std::string;
using std::shared_ptr;

class Params {
private:
	vector<int> intParams;
	vector<float> floatParams;
	vector<string> stringParams;
	vector<vector<float> > vfloatParams;
	vector<shared_ptr<Texture>> textureParams;
public:
	vector<void *>pointerList;
	vector<int> smallIntParams;
	void setTexParam(const vector<shared_ptr<Texture>>& texs) {
		textureParams = texs;
	}

	vector<shared_ptr<Texture>>& getTexParams() {
		return textureParams;
	}

	void SetIntParams(const vector<int>& intParams){
		this->intParams = intParams;
	}

	void SetFloatParams(const vector<float>& floatParams) {
		this->floatParams = floatParams;
	}

	void SetStringParams(const vector<string>& stringParams) {
		this->stringParams = stringParams;
	}

	void SetVfloatParmas(const vector<vector<float> >& vfloatParams) {
		this->vfloatParams = vfloatParams;
	}

	void SetVfloatParmas(const vector<vector<float> >&& vfloatParams) {
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

	const vector<vector<float> >& GetVfloatParams() const {
		return vfloatParams;
	}
};
