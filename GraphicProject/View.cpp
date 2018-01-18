#include "View.h"

View::View()
{
}

View::~View()
{
}

void View::Update(const int state, shared_ptr<Params> params = shared_ptr<Params>())
{
	switch (state)
	{
	case COMMAND_ERROR:
	{
		cout << "command error!" << endl;
		break;
	}
	case ADD_OBJECT: break;
	case DRAW_ONE_OBJECT_WITH_ONE_METHOD:
	{
		const vector<float>& floatResult = params->GetFloatParams();
		const vector<vector<float> >& vfloatResult = params->GetVfloatParams();
		float color[3], position[3], scale[3], rotate[3];
		int index = 0;
		for (int i = 0; i < 3; i++)
			color[i] = floatResult[index++];
		for (int i = 0; i < 3; i++)
			position[i] = floatResult[index++];
		for (int i = 0; i < 3; i++)
			scale[i] = floatResult[index++];
		for (int i = 0; i < 3; i++)
			rotate[i] = floatResult[index++];

		if (params->GetIntParams()[0] == 0) {  // no texture
			shared_ptr<BasicDraw> draw;
			draw = shared_ptr<BasicDraw>(new BasicDraw());
			draw->Set(params->GetIntParams()[1], color, position, scale, rotate, vfloatResult[0], vfloatResult[1], vfloatResult[2], params->GetIntParams()[2],(vector<shared_ptr<Light>>*)params->pointerList[0]);
			DrawList.push_back(draw);
		}
		else if (params->GetIntParams()[0] == 1) {  // texture used
			shared_ptr<TextureDraw> draw;
			draw = shared_ptr<TextureDraw>(new TextureDraw());
			vector<int>::const_iterator i = params->GetIntParams().begin();
			bool flag = false;
			for (; i != params->GetIntParams().end(); i++) {
				if (*i == -1) flag = true;
				if (flag && *i == -1) break;
			}
			draw->addTex(params->getTexParams()[0]);
			draw->addTex(params->getTexParams()[1]);
			draw->Set(params->GetIntParams()[1], color, position, scale, rotate, vfloatResult[0], vfloatResult[1], vfloatResult[2], params->GetIntParams()[2], (vector<shared_ptr<Light>>*)params->pointerList[0]);
			DrawList.push_back(draw);
		}
		break;
	}
	case DRAW_obj:
	{
		const vector<shared_ptr<Texture>>& texResult = params->getTexParams();
		const vector<int>& intResult = params->GetIntParams();
		const vector<float>& floatResult = params->GetFloatParams();
		const vector<vector<float> >& vfloatResult = params->GetVfloatParams();
		float color[3], position[3], scale[3], rotate[3];
		int index = 0;
		for (int i = 0; i < 3; i++)
			color[i] = floatResult[index++];
		for (int i = 0; i < 3; i++)
			position[i] = floatResult[index++];
		for (int i = 0; i < 3; i++)
			scale[i] = floatResult[index++];
		for (int i = 0; i < 3; i++)
			rotate[i] = floatResult[index++];
		shared_ptr<ObjDraw> draw;
		draw = shared_ptr<ObjDraw>(new ObjDraw());
		draw->Set(params->GetIntParams()[1], color, position, scale, rotate, vfloatResult[0], vfloatResult[1], vfloatResult[2], params->smallIntParams[1], (vector<shared_ptr<Light>>*)params->pointerList[0]);
		draw->setKdsize(params->smallIntParams[0]);
		draw->setIndexandFace(intResult);
		draw->setTextures(texResult);
		DrawList.push_back(draw);
		break;
	}
	case UPDATE_OBJECT:
	{
		shared_ptr<BasicDraw> draw = findDrawFromID(params->GetIntParams()[0]);
		if (draw == nullptr) return;
		draw->setColor(params->GetFloatParams()[0], params->GetFloatParams()[1],
			params->GetFloatParams()[2]);
		draw->setPosition(params->GetFloatParams()[3], params->GetFloatParams()[4],
			params->GetFloatParams()[5]);
		draw->setScale(params->GetFloatParams()[6], params->GetFloatParams()[7],
			params->GetFloatParams()[8]);
		draw->setRotate(params->GetFloatParams()[9], params->GetFloatParams()[10],
			params->GetFloatParams()[11]);
		break;
	}
	case ADJUST_OBJECT:
	{
		shared_ptr<BasicDraw> draw = findDrawFromID(params->GetIntParams()[0]);
		if (draw == nullptr) return;
		if (params->GetIntParams()[1] == 0)
			draw->setColor(params->GetFloatParams()[0], params->GetFloatParams()[1], params->GetFloatParams()[2]);
		else if (params->GetIntParams()[1] == 1)
			draw->setPosition(params->GetFloatParams()[0], params->GetFloatParams()[1], params->GetFloatParams()[2]);
		else if (params->GetIntParams()[1] == 2)
			draw->setScale(params->GetFloatParams()[0], params->GetFloatParams()[1], params->GetFloatParams()[2]);
		else if (params->GetIntParams()[1] == 3)
			draw->setRotate(params->GetFloatParams()[0], params->GetFloatParams()[1], params->GetFloatParams()[2]);
		break;
	}
	}
}

