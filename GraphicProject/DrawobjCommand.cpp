#include "DrawobjCommand.h"

void DrawobjCommand::exec()
{
	pmodel->DrawOneobj(this->params.GetIntParams());
}
