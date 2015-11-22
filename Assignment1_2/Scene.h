#pragma once
#include "FreeImage.h"
#include "Model.h"
#include "Texture.h"
#include <string>
#include <vector>
#include "glut.h"

using namespace std;

namespace DSOpenGL
{
	class Scene
	{
	public:
		Scene(string fileDirectory, string fileName);
		~Scene();
		void Display();
		void TranslateModel(int modelIndex, GLfloat x, GLfloat y);

	private:
		vector<Model*> models;
		vector<Texture*> textures;
	};
}