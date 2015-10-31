#include "View.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include "Vector3.h"

namespace DSOpenGL
{
	View::View(string viewFilePath)
	{
		ifstream inputFile;
		inputFile.open(viewFilePath);
		if (inputFile)
		{
			glEnable(GL_LIGHTING);
			string line;
			int lightIndex = 0;
			while (getline(inputFile, line))
			{
				istringstream lineStream(line);
				string word;
				lineStream >> word;
				if (word == "eye")
				{
					lineStream >> eyePosition[0] >> eyePosition[1] >> eyePosition[2];
				}
				else if(word =="vat")
				{
					lineStream >> centerPosition[0] >> centerPosition[1] >> centerPosition[2];
				}
				else if (word == "vup")
				{
					lineStream >> upVector[0] >> upVector[1] >> upVector[2];
				}
				else if (word == "fovy")
				{
					lineStream >> fovy;
				}
				else if (word == "dnear")
				{
					lineStream >> zNear;
				}
				else if (word == "dfar")
				{
					lineStream >> zFar;
				}
				else if (word == "viewport")
				{
					lineStream >> viewPort[0] >> viewPort[1] >> width >> height;
				}
			}
			inputFile.close();
		}
		else
		{
			cerr << "view file open error!" << endl;
		}
	}
	View::~View()
	{

	}
	void View::Show()
	{
		glViewport(viewPort[0], viewPort[1], width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(fovy, (GLfloat)width / (GLfloat)height, zNear, zFar);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(
			eyePosition[0], eyePosition[1], eyePosition[2], 
			centerPosition[0], centerPosition[1], centerPosition[2], 
			upVector[0], upVector[1], upVector[2]
		);
	}
	void View::ZoomIn()
	{
		Vector3 center(centerPosition), eye(eyePosition);
		Vector3 direction = center - eye;
		GLfloat size = direction.Magnitude();
		if (size > 0.01)
		{
			(eye + direction.Normarlize()*GetControlValue()).ToGLfloatArray(eyePosition);
		}
	}
	void View::ZoomOut()
	{
		Vector3 center(centerPosition), eye(eyePosition);
		Vector3 direction = center - eye;
		GLfloat size = direction.Magnitude();
		if (size > 0.01)
		{
			(eye - direction.Normarlize()*GetControlValue()).ToGLfloatArray(eyePosition);
		}
	}
	void View::MoveLeft()
	{
		Vector3 center(centerPosition), eye(eyePosition),up(upVector);
		Vector3 direction = center - eye;
		GLfloat size = direction.Magnitude();
		eye = eye + up.Cross(direction).Normarlize()*GetControlValue();
		(eye.Normarlize()*size).ToGLfloatArray(eyePosition);
	}
	void View::MoveRight()
	{
		Vector3 center(centerPosition), eye(eyePosition), up(upVector);
		Vector3 direction = center - eye;
		GLfloat size = direction.Magnitude();
		eye = eye + direction.Cross(up).Normarlize()*GetControlValue();
		(eye.Normarlize()*size).ToGLfloatArray(eyePosition);
	}
	GLfloat View::GetControlValue()
	{
		Vector3 center(centerPosition), eye(eyePosition);
		return (center - eye).Magnitude() / 50;
	}
}