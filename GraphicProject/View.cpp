#include "View.h"
#include "TextureDraw.h"
#define MONET_PATH string("D://from_ImageNet/CGTexture/Monet.bmp")
#define CRACK_PATH string("D://from_ImageNet/CGTexture/Crack.bmp")
#define SPOT_PATH string("D://from_ImageNet/CGTexture/Spot.bmp")

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
				draw = shared_ptr<BasicDraw>(new BasicDraw());
				draw->Set(params->GetIntParams()[1], color, position, scale, rotate, vfloatResult[0], vfloatResult[1], vfloatResult[2]);
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
				draw->Set(params->GetIntParams()[1], color, position, scale, rotate, vfloatResult[0], vfloatResult[1], vfloatResult[2]);
				DrawList.push_back(draw);
			}
			/*
			shared_ptr<TextureDraw> draw1;
			shared_ptr<BasicDraw> draw2;
			if (params->GetIntParams()[0] == 0) {
				draw1 = shared_ptr<TextureDraw>(new TextureDraw());
				shared_ptr<Texture> tex1, tex2;
				tex1 = params->getTexParams()[0];
				tex1->bindTex();
				tex2 = params->getTexParams()[1];
				tex2->bindTex();
				draw1->addTex(tex1);
				draw1->addTex(tex2);
				draw1->setTexMethod(0);
				draw1->Set(params->GetIntParams()[1], color, position, scale, rotate, vfloatResult[0], vfloatResult[1], vfloatResult[2]);
				DrawList.push_back(draw1);
			}
			else {
				draw2 = shared_ptr<BasicDraw>(new BasicDraw());
				draw2->Set(params->GetIntParams()[1], color, position, scale, rotate, vfloatResult[0], vfloatResult[1], vfloatResult[2]);
				DrawList.push_back(draw2);
			}
			printf("666\n");
			*/
			break;
		}
	}
}
