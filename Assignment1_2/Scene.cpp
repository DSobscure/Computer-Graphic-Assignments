#include "Scene.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace DSOpenGL
{
	Scene::Scene(string fileDirectory, string fileName)
	{
		FreeImage_Initialise();
		glewInit();

		ifstream inputFile;
		inputFile.open(fileDirectory + "/" + fileName);
		if (inputFile)
		{
			string line;
			int modelIndex = 0;
			TextureType textureType = No_Texture;
			Texture* currentTexture = nullptr;
			while (getline(inputFile, line))
			{
				istringstream lineStream(line);
				string word;
				lineStream >> word;
				if (word == "model")
				{
					string modelName;
					lineStream >> modelName;

					Model* model = new Model(fileDirectory, modelName, textureType);
					models.push_back(model);

					model->modelIndex = modelIndex;
					lineStream >> model->scale[0] >> model->scale[1] >> model->scale[2];
					lineStream >> model->angle;
					lineStream >> model->axis[0] >> model->axis[1] >> model->axis[2];
					lineStream >> model->transform[0] >> model->transform[1] >> model->transform[2];
					model->texture = currentTexture;			
					modelIndex++;
				}
				else if (word == "no-texture")
				{
					textureType = No_Texture;
					currentTexture = nullptr;
				}
				else if (word == "single-texture")
				{
					textureType = Single_Texture;
					string imageName;

					lineStream >> imageName;
					currentTexture = new SingleTexture(fileDirectory, imageName);
					textures.push_back(currentTexture);
				}
				else if (word == "multi-texture")
				{
					textureType = Multi_Texture;
					string imageNames[2];

					for (int i = 0; i < 2; i++)
					{
						lineStream >> imageNames[i];
					}
					currentTexture = new MultiTexture(fileDirectory, imageNames, 2);
					textures.push_back(currentTexture);
				}
				else if (word == "cube-map")
				{
					textureType = Cube_Map;
					string imageNames[6];

					for (int i = 0; i < 6; i++)
					{
						lineStream >> imageNames[i];
					}
					currentTexture = new CubeMapTexture(fileDirectory, imageNames);
					textures.push_back(currentTexture);
				}
			}
			inputFile.close();
		}
		else
		{
			cerr << "scene file open error!" << endl;
		}

		FreeImage_DeInitialise();
	}
	Scene::~Scene()
	{
		for (int i = 0; i < models.size(); i++)
		{
			if (models[i] != nullptr)
				delete models[i];
		}
		for (int i = 0; i < textures.size(); i++)
		{
			if (textures[i] != nullptr)
				delete textures[i];
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