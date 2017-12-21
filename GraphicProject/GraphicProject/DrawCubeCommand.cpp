#include "DrawCubeCommand.h"

void DrawCubeCommand::exec()
{
	pmodel->DrawCube(this->params.GetFloatParams());
}
