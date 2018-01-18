#include "AddObjectCommand.h"

void AddObjectCommand::exec()
{
	pmodel->AddObject(this->params.GetFloatParams(), this->params.GetIntParams(),this->params.GetStringParams());
}
