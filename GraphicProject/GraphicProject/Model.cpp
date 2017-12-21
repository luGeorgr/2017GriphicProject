#include "Model.h"

void Model::AddObject(const vector<float>& floatParams, const vector<int>& intParams)
{
	shared_ptr<Object> pobject;
	if (intParams[0] == 0)
		pobject = shared_ptr<Object>(new Cube());
	pobject->setColor(floatParams[0], floatParams[1], floatParams[2]);
	pobject->setPosition(floatParams[3], floatParams[4], floatParams[5]);
	pobject->setScale(floatParams[6], floatParams[7], floatParams[8]);
	pobject->setRotate(floatParams[9], floatParams[10], floatParams[11]);
	ObjectList.push_back(pobject);
	this->notify(ADD_OBJECT);
}

shared_ptr<Object> Model::GetLastObject()
{
	if(ObjectList.size() != 0)
		return ObjectList.back();
	return nullptr;
}
