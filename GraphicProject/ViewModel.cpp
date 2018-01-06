#include "ViewModel.h"

void ViewModel::Update(const int state, shared_ptr<Params> params = shared_ptr<Params>())
{
	notify(state, params);
}
