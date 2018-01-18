#include "Model.h"
#include "ViewModel.h"
#include "View.h"
#include <memory>
#include "HighGUI.h"

#define MONET_PATH string("C:\\Users\\txt\\Desktop\\Texture\\flatroof2.png")

using std::shared_ptr;
shared_ptr<Model> pmodel(new Model());
shared_ptr<ViewModel> pviewModel(new ViewModel(pmodel));
shared_ptr<View> pview(new View());

void display()
{  // it's just a test. We may create light class and eye class.
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, WIN_WID, WIN_LEN);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0f, 600 / 400, 0.1f, 10000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(C.position[0], C.position[1], C.position[2], C.front[0], C.front[1], C.front[2],
		C.getUpVec()[0], C.getUpVec()[1], C.getUpVec()[2]);
	for (auto it : pview->DrawList) {
		it->DrawObject();
	}
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	pmodel->AddObserver(pviewModel);
	pviewModel->AddObserver(pview);

	pview->SetCommands(pviewModel->GetCommands());
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(600, 400);
	mainWindow = glutCreateWindow("Simple GLUT App");

	/*Params test;

	test.SetFloatParams(vector<float>{1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0});//location,color...
	test.SetIntParams(vector<int>{0});//object type
	pview->addObjectCommand->SetParams(test);//one object once
	pview->addObjectCommand->exec();

	test.SetFloatParams(vector<float>{1, 1, 1, 0, 0, (float)1.2, 1, 1, 1, 0, 0, 0});
	test.SetIntParams(vector<int>{3});
	pview->addObjectCommand->SetParams(test);
	pview->addObjectCommand->exec();

	vector<string> paths = { MONET_PATH };
	test.SetStringParams(paths);//tex filename
	test.SetIntParams(vector<int>({1}));//tex type
	pview->readTexCommand->SetParams(test);//one to one
	pview->readTexCommand->exec();
	test.SetIntParams(vector<int>{0, -1, 1,0,0});//drawmethods -1 object1 tex11 tex12 object2 tex21 tex22...
	pview->drawObjectCommand->SetParams(test);
	pview->drawObjectCommand->exec();*/


	// ==============================
	//========================
	/*test.SetFloatParams(vector<float>{(float)0.7, (float)0.1, (float)0.2, 0, 0, 0, (float)1, (float)1, (float)1, 0, 0, 0});//location,color...
	test.SetIntParams(vector<int>{10});//object type 10 obj
	test.SetStringParams(vector<string>{"City Islands"});
	pview->addObjectCommand->SetParams(test);//one object once
	pview->addObjectCommand->exec();
	test.SetIntParams(vector<int>{0, 0});// 0/1(0 add 1 delete) lighttype/deleteID 
	test.SetFloatParams(vector<float>{0, 0, 500, 1, 1, 1, 1, 1, 1, 1, 1, 1});
	pview->addOrDeleteLightCommand->SetParams(test);
	pview->addOrDeleteLightCommand->exec();
	test.SetIntParams(vector<int>{0});//object id 
	pview->drawobjCommand->SetParams(test);//this will confirm that the id input is a obj type
	pview->drawobjCommand->exec();*/
	//============================
	//pview->DrawList.push_back(shared_ptr<SkyDraw>(new SkyDraw));
	glutDisplayFunc(display);
	mainWindowRender();

	glutMainLoop();
	return 0;
}
