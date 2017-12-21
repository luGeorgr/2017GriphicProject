#pragma once
#include "Data.h"
class Observer {
public:
	virtual void Update(const int state) = 0;
};