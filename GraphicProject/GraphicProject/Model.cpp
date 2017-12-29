#include "Model.h"

void Model::AddObject(const vector<float>& floatParams, const vector<int>& intParams)
{
	shared_ptr<Object> pobject;
	if (intParams[0] == 0)
		pobject = shared_ptr<Object>(new Cube());
	else if (intParams[0] == 1) {
		pobject = shared_ptr<Object>(new ObjByRead());
	}
	pobject->setColor(floatParams[0], floatParams[1], floatParams[2]);
	pobject->setPosition(floatParams[3], floatParams[4], floatParams[5]);
	pobject->setScale(floatParams[6], floatParams[7], floatParams[8]);
	pobject->setRotate(floatParams[9], floatParams[10], floatParams[11]);
	ObjectList.push_back(pobject);
	this->notify(ADD_OBJECT);
}


void Model::DrawOneObjectWithOneMethod(const vector<int>& IntParams)
{
	shared_ptr<Object> pobject = ObjectList[IntParams[1]];
	shared_ptr<Params> t = shared_ptr<Params>(new Params());
	vector<int> intParams;
	intParams.push_back(IntParams[0]);//äÖÈ¾·½Ê½
	intParams.push_back(pobject->getDrawMethod());//gl_quad ...
	vector<vector<float>> vfloatParams;
	vfloatParams.push_back(pobject->getPoint());
	vfloatParams.push_back(pobject->getNormal());
	vfloatParams.push_back(pobject->gettexCoord());
	vector<float> floatParams;
	float* color = pobject->getColor();
	float* position = pobject->getPosition();
	float* scale = pobject->getScale();
	float* rotate = pobject->getRotate();
	for (int i = 0; i < 3; i++)
		floatParams.push_back(color[i]);
	for (int i = 0; i < 3; i++)
		floatParams.push_back(position[i]);
	for (int i = 0; i < 3; i++)
		floatParams.push_back(scale[i]);
	for (int i = 0; i < 3; i++)
		floatParams.push_back(rotate[i]);
	t->SetIntParams(intParams);
	t->SetVfloatParmas(vfloatParams);
	t->SetFloatParams(floatParams);
	this->notify(DRAW_ONE_OBJECT_WITH_ONE_METHOD, t);
}

shared_ptr<Object> Model::GetObject(const vector<int>& intParams)
{
	for (int i = 0; i < ObjectList.size(); i++)
	{
		if (ObjectList[i]->getID() == intParams[0])
			return ObjectList[i];
	}
	return nullptr;
}

shared_ptr<Object> Model::GetLastObject()
{
	if(ObjectList.size() != 0)
		return ObjectList.back();
	return nullptr;
}
