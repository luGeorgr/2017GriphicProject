#include"Model.h"
#include"ViewModel.h"
#include"View.h"

#include<memory>
using std::shared_ptr;
int main(void) {
	shared_ptr<Model> pmodel(new Model());
	shared_ptr<ViewModel> pviewModel(new ViewModel());
	shared_ptr<View> pview(new View());

	pmodel->AddObserver(pviewModel);
	pviewModel->AddObserver(pview);

	pview->SetCommands(pviewModel->GetCommands());
	return 0;
}