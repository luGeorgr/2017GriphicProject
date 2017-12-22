#include "View.h"






View::View()
{
}


View::~View()
{
}

void View::Update(const int state,shared_ptr<Params> params = shared_ptr<Params>())
{
	switch (state)
	{
	case ADD_OBJECT:break;
	case DRAW_ONE_OBJECT_WITH_ONE_METHOD:
		{
			const vector<float>& floatResult = params->GetFloatParams();
			const vector<vector<float>>& vfloatResult = params->GetVfloatParams();
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
			shared_ptr<BasicDraw> draw;
			if (params->GetIntParams()[0] == 0)
				draw = shared_ptr<BasicDraw>(new BasicDraw());
			draw->Set(params->GetIntParams()[1], color, position, scale, rotate, vfloatResult[0], vfloatResult[1], vfloatResult[2]);
			DrawList.push_back(draw);
			break;
		}
	}
}
