#pragma once

#include "Data.h"
#include <memory>
using std::shared_ptr;

class Observer {
public:
	virtual void Update(const int state, shared_ptr<Params> params) = 0;
};