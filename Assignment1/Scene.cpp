#include "Scene.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace DSOpenGL
{
	Scene::Scene(string sceneFilePath)
	{
		ifstream inputFile;
		inputFile.open(sceneFilePath);
		if (inputFile)
		{
			string line;
			int modelIndex = 0;
			while (getline(inputFile, line))
			{
				istringstream lineStream(line);
				string word;
				lineStream >> word;
				if (word == "model")
				{
					string modelName;
					lineStream >> modelName;
					Model* model = new Model(modelName);
					models.push_back(model);

					model->modelIndex = modelIndex;
					lineStream >> model->scale[0] >> model->scale[1] >> model->scale[2];
					lineStream >> model->angle;
					lineStream >> model->axis[0] >> model->axis[1] >> model->axis[2];
					lineStream >> model->transform[0] >> model->transform[1] >> model->transform[2];

					modelIndex++;
				}
			}
			inputFile.close();
		}
		else
		{
			cerr << "scene file open error!" << endl;
		}
	}
	Scene::~Scene()
	{
		for (int i = 0; i < models.size(); i++)
		{
			if (models[i] != nullptr)
				delete models[i];
		}
	}
	void Scene::Display()
	{
		glMatrixMode(GL_MODELVIEW);
		for (int i = 0; i < models.size(); i++)
		{
			if (models[i] != nullptr)
				models[i]->Display();
		}
	}
	void Scene::TranslateModel(int modelIndex, GLfloat x, GLfloat y)
	{
		if (modelIndex >= 1 && modelIndex <= models.size())
		{
			models[modelIndex - 1]->Translate(x, y);
		}
	}
}