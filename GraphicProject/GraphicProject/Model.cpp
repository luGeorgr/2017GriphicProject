#include "Model.h"

void Model::DrawCube(const vector<float>& floatParams)
{
	shared_ptr<Cube> pcube(new Cube());
	pcube->setColor(floatParams[0], floatParams[1], floatParams[2]);
	pcube->setPosition(floatParams[3], floatParams[4], floatParams[5]);
	pcube->setScale(floatParams[6], floatParams[7], floatParams[8]);
	pcube->setRotate(floatParams[9], floatParams[10], floatParams[11]);
	ObjectList.push_back(pcube);
	this->notify(ADD_OBJECT);
}

shared_ptr<Object> Model::GetLastObject()
{
	if(ObjectList.size() != 0)
		return ObjectList.back();
	return nullptr;
}
