#pragma once
#include "FreeImage.h"
#include "glew.h"
#include "mesh.h"
#include <string>
#include "Texture.h"
#include "glut.h"


using namespace std;

namespace DSOpenGL
{
	class Model
	{
		friend class Scene;
	public:
		Model(string fileDirectory, string fileName, TextureType type);
		~Model();
		void Display();
		void Translate(GLfloat x, GLfloat y);

	private:
		int modelIndex;
		TextureType textureType;
		mesh* modelMesh;
		string fileName;
		GLfloat scale[3];
		GLfloat angle;
		GLfloat axis[3];
		GLfloat transform[3];
		Texture*  texture;
	};
}
