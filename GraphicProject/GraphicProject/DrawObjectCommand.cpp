#include "DrawObjectCommand.h"

void DrawObjectCommand::exec()
{
	for (int i = 0; this->params.GetIntParams()[i] != -1&&i<5; i++)
	{
		for (int j = 5; j < this->params.GetIntParams().size(); j++)
		{
			Params t;
			t.SetIntParams(vector<int>{params.GetIntParams()[i], params.GetIntParams()[j]});
			drawOneObjectWithOneMethodCommand->SetParams(t);
			drawOneObjectWithOneMethodCommand->exec();//the first is drawmethod , the second is object
		}
	}
}
