#include "View.h"






View::View()
{
}


View::~View()
{
}

void View::Update(const int state)
{
	switch (state)
	{
	case ADD_OBJECT:break;
	case DRAW_OBJECT_BASIC:
		{
			this->getLastObjectInformationCommand->exec();
			const Params& temp = getLastObjectInformationCommand->GetResults();
			const vector<float>& floatResult = temp.GetFloatParams();
			const vector<vector<float>>& vfloatResult = temp.GetVfloatParams();
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
			Draw draw;
			draw.Set(temp.GetIntParams()[0], color, position, scale, rotate, vfloatResult[0], vfloatResult[1], vfloatResult[2]);
			DrawList.push_back(draw);
			break;
		}
	}
}
