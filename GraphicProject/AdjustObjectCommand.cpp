#include "AdjustObjectCommand.h"

void AdjustObjectCommand::exec()
{
	pmodel->AdjustObject(this->params.GetFloatParams(), this->params.GetIntParams());
}
