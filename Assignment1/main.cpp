#include "glut.h"
#include "Lights.h"
#include "View.h"
#include "Scene.h"
#include "Vector3.h"
#include <iostream>

using namespace std;
using namespace DSOpenGL;

void Display();
void Reshape(int, int);
void OnButtonDown(unsigned char keyCode, int mouseX, int mouseY);
void OnMouseButtonEvent(int button, int state, int x, int y);
void OnMouseDragEvent(int x, int y);

Lights* lights;
Scene* scene;
View* view;
int selectedObjectIndex = 0;
int mouseState = -1;
int mouseX, mouseY;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	lights = new DSOpenGL::Lights("scene2.light");
	scene = new DSOpenGL::Scene("scene2.scene");
	view = new DSOpenGL::View("scene2.view");

	glutInitWindowSize(view->width, view->height);
	glutInitWindowPosition(view->viewPort[0], view->viewPort[1]);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("Planet");

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(OnButtonDown);
	glutMouseFunc(OnMouseButtonEvent);
	glutMotionFunc(OnMouseDragEvent);
	glutMainLoop();

	delete lights;
	delete scene;
	delete view;

	return 0;
}

void Display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);//³]©w©³¦â
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	lights->OpenAll();
	scene->Display();
	view->Show();

	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	view->Show();
}

void OnButtonDown(unsigned char keyCode, int mouseX, int mouseY)
{
	switch (keyCode)
	{
	case 'w':
		view->ZoomIn();
		break;
	case 'a':
		view->MoveLeft();
		break;
	case 's':
		view->ZoomOut();
		break;
	case 'd':
		view->MoveRight();
		break;
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		selectedObjectIndex = keyCode - '0';
		break;
	}
	glutPostRedisplay();
}

void OnMouseButtonEvent(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mouseX = x;
			mouseY = y;
			mouseState = GLUT_DOWN;
		}
		else if (state == GLUT_UP)
		{
			scene->TranslateModel(selectedObjectIndex, (x - mouseX)*view->GetControlValue()/50, (mouseY - y)*view->GetControlValue()/50);
			glutPostRedisplay();
			mouseState = GLUT_UP;
		}
	}
}

void OnMouseDragEvent(int x, int y)
{
	if (mouseState == GLUT_DOWN)
	{
		scene->TranslateModel(selectedObjectIndex, (x - mouseX)*view->GetControlValue() / 20, (mouseY - y)*view->GetControlValue() / 20);
		mouseX = x;
		mouseY = y;
		glutPostRedisplay();
	}
}