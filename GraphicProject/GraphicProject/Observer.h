#pragma once
#include "Data.h"
class Observer {
public:
	virtual void Update(const Params& params) = 0;
};