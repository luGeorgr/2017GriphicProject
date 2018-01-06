#include "Model.h"
#include "ViewModel.h"
#include "View.h"
#include <memory>
#include "HighGUI.h"

#define MONET_PATH string("D://from_ImageNet/CGTexture/Monet.bmp")
#define CRACK_PATH string("D://from_ImageNet/CGTexture/Crack.bmp")
#define SPOT_PATH string("D://from_ImageNet/CGTexture/Spot.bmp")

using std::shared_ptr;
shared_ptr<Model> pmodel(new Model());
shared_ptr<ViewModel> pviewModel(new ViewModel(pmodel));
shared_ptr<View> pview(new View());

void display()
{  // it's just a test. We may create light class and eye class.
	
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, WIN_WID, WIN_LEN);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0f, 600 / 400, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], 0, 0, 1);
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

	Params test;
	
	test.SetFloatParams(vector<float>{1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0});
	test.SetIntParams(vector<int>{0});
	pview->addObjectCommand->SetParams(test);
	pview->addObjectCommand->exec();

	vector<string> paths = { MONET_PATH };
	test.SetStringParams(paths);
	test.SetIntParams(vector<int>({1}));
	pview->readTexCommand->SetParams(test);
	pview->readTexCommand->exec();
	test.SetIntParams(vector<int>{1, -1, 0, 0, 0, 0, 0,0});
	pview->drawObjectCommand->SetParams(test);
	pview->drawObjectCommand->exec();
	
	// ==============================
	glutDisplayFunc(display);
	mainWindowRender();

	glutMainLoop();
	return 0;
}
