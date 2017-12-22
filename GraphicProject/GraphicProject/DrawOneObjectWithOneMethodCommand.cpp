#include "DrawOneObjectWithOneMethodCommand.h"

void DrawOneObjectWithOneMethodCommand::exec()
{
	pmodel->DrawOneObjectWithOneMethod(this->params.GetIntParams());
}
