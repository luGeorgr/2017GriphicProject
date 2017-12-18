#pragma once
#include "BasicCommand.h"
class Observer {
public:
	virtual void Update(const Params& params) = 0;
};