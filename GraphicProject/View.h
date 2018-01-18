#pragma once

#include "Observer.h"
#include "Commands.h"
#include "Changes.h"
#include "BasicDraw.h"
#include "TextureDraw.h"
#include "ObjDraw.h"
#include"SkyDraw.h"
class View : public Observer {
// public for test
public:
	shared_ptr<BasicCommand> addObjectCommand, getLastObjectInformationCommand,
		drawObjectCommand, getObjectInformationCommand, readTexCommand, drawobjCommand, adjustobjectCommand, addOrDeleteLightCommand,
		setObjectAttributeCommand;
private:
	shared_ptr<BasicDraw> findDrawFromID(const int id)
	{
		if (id < 0)return nullptr;
		for (auto i : DrawList)
			if (i->getID() == id)
				return i;
		return nullptr;
	}
public:
	vector<shared_ptr<BasicDraw> > DrawList;
	View();
	~View();
	
	void Update(const int state, shared_ptr<Params> params);

	void SetCommands(vector<shared_ptr<BasicCommand> > commands) 
	{
		int index = 0;
		addObjectCommand = commands[index++];
		drawObjectCommand = commands[index++];
		getLastObjectInformationCommand = commands[index++];
		getObjectInformationCommand = commands[index++];
		readTexCommand = commands[index++];
		drawobjCommand = commands[index++];
		adjustobjectCommand = commands[index++];
		addOrDeleteLightCommand = commands[index++];
		setObjectAttributeCommand = commands[index++];
		// ÃüÁîµÄ°ó¶¨
	}
};
