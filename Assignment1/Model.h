#pragma once
#include "glut.h"
#include "mesh.h"
#include <string>

using namespace std;

namespace DSOpenGL
{
	class Model
	{
		friend class Scene;
	public:
		Model(string modelFilePath);
		~Model();
		void Display();
		void Translate(GLfloat x, GLfloat y);

	private:
		int modelIndex;
		mesh* modelMesh;
		string fileName;
		GLfloat scale[3];
		GLfloat angle;
		GLfloat axis[3];
		GLfloat transform[3];
	};
}
