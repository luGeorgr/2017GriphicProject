#include "Model.h"

void Model::AdjustObject(const vector<float>& floatParams, const vector<int>& intParams)
{
	shared_ptr<Object> pobject = findObjectFromID(intParams[0]);
	if (pobject == nullptr) return;
	if(intParams[1]==0)
		pobject->setColor(floatParams[0], floatParams[1], floatParams[2]);
	else if (intParams[1] == 1)
		pobject->setPosition(floatParams[0], floatParams[1], floatParams[2]);
	else if(intParams[1] == 2)
		pobject->setScale(floatParams[0], floatParams[1], floatParams[2]);
	else if(intParams[1] == 3)
		pobject->setRotate(floatParams[0], floatParams[1], floatParams[2]);
	shared_ptr<Params> t = shared_ptr<Params>(new Params());
	t->SetIntParams(intParams);
	t->SetFloatParams(floatParams);
	notify(ADJUST_OBJECT, t);
}



void Model::AddObject(const vector<float>& floatParams, const vector<int>& intParams, const vector<string>& stringParams)
{
	shared_ptr<Object> pobject;
	if (intParams[0] == 0)  // 0: cube
		pobject = shared_ptr<Object>(new Cube());
	else if (intParams[0] == 1)
		pobject = shared_ptr<Object>(new Cylinder(0.5,1));
	else if (intParams[0] == 2)
		pobject = shared_ptr<Object>(new Cone(1,1));
	else if (intParams[0] == 3)
		pobject = shared_ptr<Object>(new Sphere(1));
	else if (intParams[0] == 4)
	pobject = shared_ptr<Object>(new Prism(7,0.5,1));
	else if (intParams[0] == 10)
		pobject = shared_ptr<Object>(new ObjByRead(stringParams[0]));
	pobject->setColor(floatParams[0], floatParams[1], floatParams[2]);
	pobject->setPosition(floatParams[3], floatParams[4], floatParams[5]);
	pobject->setScale(floatParams[6], floatParams[7], floatParams[8]);
	pobject->setRotate(floatParams[9], floatParams[10], floatParams[11]);
	ObjectList.push_back(pobject);
	this->notify(ADD_OBJECT);
}

void Model::DrawOneObjectWithOneMethod(const vector<int>& IntParams)
{
	shared_ptr<Object> pobject = findObjectFromID(IntParams[1]);
	if (pobject == nullptr)return;
	shared_ptr<Params> t = shared_ptr<Params>(new Params());
	vector<int> intParams;
	intParams.push_back(IntParams[0]);
	intParams.push_back(pobject->getDrawMethod());  // gl_quad ...
	intParams.push_back(pobject->getID());
	if (IntParams[0] == 1)
		t->setTexParam(vector<shared_ptr<Texture>>{findTexFromID(IntParams[2]), findTexFromID(IntParams[3])});
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
	t->SetIntParams(intParams);
	t->SetVfloatParmas(vfloatParams);
	t->SetFloatParams(floatParams);
	t->pointerList.push_back(&LightList);
	this->notify(DRAW_ONE_OBJECT_WITH_ONE_METHOD, t);
}

void Model::DrawOneobj(const vector<int>& intParams)
{
	int id = intParams[0];
	shared_ptr<Object> pobject = ObjectList[id];
	if(pobject->getType()!=10)
		this->notify(COMMAND_ERROR);
	else
	{
		ObjByRead* pobj = static_cast<ObjByRead*>(pobject.get());
		shared_ptr<Params> t = shared_ptr<Params>(new Params());
		vector<vector<float> > vfloatParams;
		vfloatParams.push_back(pobj->getPoint());
		vfloatParams.push_back(pobj->getNormal());
		vfloatParams.push_back(pobj->gettexCoord());
		t->SetVfloatParmas(vfloatParams);
		float* color = pobj->getColor();
		float* position = pobj->getPosition();
		float* scale = pobj->getScale();
		float* rotate = pobj->getRotate();
		vector<float> floatParams;
		for (int i = 0; i < 3; i++)
			floatParams.push_back(color[i]);
		for (int i = 0; i < 3; i++)
			floatParams.push_back(position[i]);
		for (int i = 0; i < 3; i++)
			floatParams.push_back(scale[i]);
		for (int i = 0; i < 3; i++)
			floatParams.push_back(rotate[i]);
		t->SetFloatParams(floatParams);
		vector<int> intParams;
		for (int i = 0; i < pobj->getIndex().size(); i++) {
			intParams.push_back(pobj->getIndex()[i]);
			intParams.push_back(pobj->getFace()[i]);
		}
		t->SetIntParams(intParams);
		t->smallIntParams.push_back(pobj->getKdTexList().size());
		t->smallIntParams.push_back(pobj->getID());
		vector<shared_ptr<Texture>> textureParams;
		textureParams.insert(textureParams.end(), pobj->getKdTexList().begin(), pobj->getKdTexList().end());
		textureParams.insert(textureParams.end(), pobj->getKaTexList().begin(), pobj->getKaTexList().end());
		t->setTexParam(textureParams);
		t->pointerList.push_back(&LightList);
		this->notify(DRAW_obj, t);
	}
}

shared_ptr<Object> Model::GetObject(const vector<int>& intParams)
{
	for (int i = 0; i < ObjectList.size(); i++) {
		if (ObjectList[i]->getID() == intParams[0])
			return ObjectList[i];
	}
	return nullptr;
}

shared_ptr<Object> Model::GetLastObject()
{
	if (ObjectList.size() != 0)
		return ObjectList.back();
	return nullptr;
}

void Model::ReadTex(const vector<string>& files, const vector<int>& types)
{
	vector<int>::const_iterator j = types.begin();
	for (vector<string>::const_iterator i = files.begin(); i != files.end(); i++, j++) {
		shared_ptr<Texture> Tex_ptr = shared_ptr<Texture>(new Texture(*i, *j));
		Tex_ptr->bindTex();
		TexList.push_back(Tex_ptr);
	}
}

void Model::ObjectMove()
{
	//printf("hello world\n");
	float time = 0.1;
	vector<pair<int, int>> v;
	for (int i = 0; i < ObjectList.size(); i++) {
		ObjectList[i]->PreMove(time);
		float* iOffset = ObjectList[i]->getNextPosition();
		printf("%f %f %f\n", iOffset[0], iOffset[1], iOffset[2]);
		printf("%f %f %f\n", ObjectList[i]->vx, ObjectList[i]->vy, ObjectList[i]->vz);
	}
	for (int i = 0; i < ObjectList.size(); i++) {
		if (ObjectList[i]->MoveAbility() == false)
			continue;
		for (int j = 0; j < ObjectList.size(); j++) {
			if (j == i)
				continue;
			float* iOffset = ObjectList[i]->getNextPosition();
			float* iScale = ObjectList[i]->getScale();
			float* jOffset = ObjectList[j]->getNextPosition();
			float* jScale = ObjectList[j]->getScale();
			for (int k = 0; k < ObjectList[i]->hitCubes.size(); k++) {
				ObjectList[i]->hitCubes[k].Transformation(iScale[0], iScale[1], iScale[2], iOffset[0], iOffset[1], iOffset[2]);
				for (int l = 0; l < ObjectList[j]->hitCubes.size(); l++) {
					ObjectList[j]->hitCubes[l].Transformation(jScale[0], jScale[1], jScale[2], jOffset[0], jOffset[1], jOffset[2]);
					if (HitCubeCheck(ObjectList[i]->hitCubes[k], ObjectList[j]->hitCubes[l]) == true)
						v.push_back(pair<int,int>(i, j));
				}
			}
		}
	}
	for (auto it : v) {
		ObjectList[it.first]->SetV(0, 0, 0);
		ObjectList[it.second]->SetV(0, 0, 0);
	}
	for (int i = 0; i < ObjectList.size(); i++) {
		shared_ptr<Params> params(new Params());
		vector<int> intParams;
		vector<float> floatParam;
		if (ObjectList[i]->CanMove() == true) {
			//printf("%d", i);
			ObjectList[i]->Confirm();
			float* color = ObjectList[i]->getColor();
			float* position = ObjectList[i]->getPosition();
			float* scale = ObjectList[i]->getScale();
			float* rotate = ObjectList[i]->getRotate();
			intParams.push_back(ObjectList[i]->getID());
			floatParam.push_back(color[0]); floatParam.push_back(color[1]); floatParam.push_back(color[2]);
			floatParam.push_back(position[0]); floatParam.push_back(position[1]); floatParam.push_back(position[2]);
			floatParam.push_back(scale[0]); floatParam.push_back(scale[1]); floatParam.push_back(scale[2]);
			floatParam.push_back(rotate[0]); floatParam.push_back(rotate[1]); floatParam.push_back(rotate[2]);
			params->SetFloatParams(floatParam);
			params->SetIntParams(intParams);
			this->notify(UPDATE_OBJECT, params);
		}
	}
}

void Model::AddOrDeleteLight(const vector<float>& floatParams, const vector<int>& intParams)
{
	if (intParams[0] == 0)//add
	{
		int type = intParams[1];
		if (type == 2)
			LightList.push_back(shared_ptr<Light>(new Light(type, &floatParams[0], &floatParams[3], &floatParams[6], &floatParams[9], &floatParams[12], floatParams[15])));
		else
			LightList.push_back(shared_ptr<Light>(new Light(type, &floatParams[0], &floatParams[3], &floatParams[6], &floatParams[9])));
	}
	else if (intParams[0] == 1)
	{
		int ID = intParams[0];
		vector<shared_ptr<Light>>::iterator iter = find(LightList.begin(), LightList.end(), findLightFromID(ID));
		if (iter != LightList.end())LightList.erase(iter);
	}
}

void Model::SetObjectAttribute(const vector<float>& floatParams, const vector<int>& intParams)
{
	shared_ptr<Object> pobject = findObjectFromID(intParams[0]);
	if (intParams[1] == 1) {
		pobject->setObjectAttribute(true, floatParams[0], floatParams[1], floatParams[2], floatParams[3], floatParams[4], floatParams[5], floatParams[6], floatParams[7], floatParams[8]);
	}
	else pobject->setObjectAttribute(false);
}
