#include"ReadTexCommand.h"

void ReadTexCommand::exec()
{
	pmodel->ReadTex(this->params.GetStringParams(), this->params.GetIntParams());
}
