#pragma once
#include "glut.h"
#include "Model.h"
#include <string>
#include <vector>

using namespace std;

namespace DSOpenGL
{
	class Scene
	{
	public:
		Scene(string sceneFilePath);
		~Scene();
		void Display();
		void TranslateModel(int modelIndex, GLfloat x, GLfloat y);

	private:
		vector<Model*> models;
	};
}