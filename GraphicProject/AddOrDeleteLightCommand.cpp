#include "AddOrDeleteLightCommand.h"

void AddOrDeleteLightCommand::exec()
{
	pmodel->AddOrDeleteLight(this->params.GetFloatParams(), this->params.GetIntParams());
}
