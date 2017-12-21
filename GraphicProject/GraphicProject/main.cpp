#include"Model.h"
#include"ViewModel.h"
#include"View.h"

#include<memory>
using std::shared_ptr;
shared_ptr<Model> pmodel(new Model());
shared_ptr<ViewModel> pviewModel(new ViewModel(pmodel));
shared_ptr<View> pview(new View());
void display() {//it's just a test.We may create light class and eye class.
	
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 600, 400);
	glMatrixMode(GL_PROJECTION);						
	glLoadIdentity();																		
	gluPerspective(30.0f, 600 / 400, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);							
	glLoadIdentity();
	gluLookAt(5, 0, 0, 0, 0, 1, 0, 0, 1);
	for (auto it : pview->DrawList) {
		printf("hello world");
		it.DrawObject();
	}
	glutSwapBuffers();
}
int main(int argc, char *argv[]) {

	pmodel->AddObserver(pviewModel);
	pviewModel->AddObserver(pview);

	pview->SetCommands(pviewModel->GetCommands());



	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(600, 400);
	glutCreateWindow("Simple GLUT App");


	Params test;
	test.SetFloatParams(vector<float>{1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0});
	test.SetIntParams(vector<int>{0});
	pview->AddObjectCommand->SetParams(test);
	pview->AddObjectCommand->exec();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}