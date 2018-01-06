#include "DrawObjectCommand.h"

void DrawObjectCommand::exec()
{
	for (int i = 0; this->params.GetIntParams()[i] != -1 && i<5; i++)
	{
		for (int j = 5; j < this->params.GetIntParams().size(); j+=3)
		{
			Params t;
			t.SetIntParams(vector<int>{params.GetIntParams()[i], params.GetIntParams()[j], params.GetIntParams()[j + 1], params.GetIntParams()[j + 2]});
			drawOneObjectWithOneMethodCommand->SetParams(t);
			drawOneObjectWithOneMethodCommand->exec();//the first is drawmethod , the second is object
		}
	}
}
