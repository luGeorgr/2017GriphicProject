#include "SetObjectAttributeCommand.h"

void SetObjectAttributeCommand::exec()
{
	this->pmodel->SetObjectAttribute(params.GetFloatParams(), params.GetIntParams());
}
