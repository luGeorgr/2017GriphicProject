#include "GetLastObjectInformationCommand.h"

void GetLastObjectInformationCommand::exec()
{
	shared_ptr<Object> pobject = pmodel->GetLastObject();
	vector<int> intParams;
	intParams.push_back(pobject->getDrawMethod());
	vector<vector<float> > vfloatParams;
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
	this->resultParams.SetIntParams(intParams);
	this->resultParams.SetVfloatParmas(vfloatParams);
	this->resultParams.SetFloatParams(floatParams);
}
