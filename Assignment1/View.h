#pragma once
#include "glut.h"
#include<string>

using namespace std;

namespace DSOpenGL
{
	class View
	{
	public:
		View(string viewFilePath);
		~View();
		void Show();
		void ZoomIn();
		void ZoomOut();
		void MoveLeft();
		void MoveRight();
		GLfloat GetControlValue();

		GLint viewPort[2];
		GLsizei width, height;

	private:
		GLfloat eyePosition[3];
		GLfloat centerPosition[3];
		GLfloat upVector[3];
		GLfloat fovy;
		GLfloat zNear;
		GLfloat zFar;
	};
}