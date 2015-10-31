#include"Lights.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace DSOpenGL
{
	Lights::Lights(string lightFilePath)
	{
		ifstream inputFile;
		inputFile.open(lightFilePath);
		if (inputFile)
		{
			string line;
			int lightIndex = 0;
			while (getline(inputFile, line))
			{
				istringstream lineStream(line);
				string word;
				lineStream >> word;
				if (word == "light")
				{
					Light* light = new Light();
					lights.push_back(light);
					
					light->lightIndex = lightIndex;
					lineStream >> light->position[0] >> light->position[1] >> light->position[2];
					light->position[3] = 1.0f;

					lineStream >> light->ambient[0] >> light->ambient[1] >> light->ambient[2];			
					lineStream >> light->diffuse[0] >> light->diffuse[1] >> light->diffuse[2];				
					lineStream >> light->specular[0] >> light->specular[1] >> light->specular[2];

					lightIndex++;
				}
				else if(word == "ambient")
				{
					if(ambientLight == nullptr)
						ambientLight = new AmbientLight();
					lineStream >> ambientLight->ambient[0] >> ambientLight->ambient[1] >> ambientLight->ambient[2];
				}
			}
			inputFile.close();
		}
		else
		{
			cerr << "light file open error!" << endl;
		}
	}
	Lights::~Lights()
	{
		for (int i = 0; i < lights.size(); i++)
		{
			if(lights[i] != nullptr)
				delete lights[i];
		}
		if (ambientLight != nullptr)
			delete ambientLight;
	}
	void Lights::OpenAll()
	{
		glEnable(GL_LIGHTING);
		for (int i = 0; i < lights.size(); i++)
		{
			if (lights[i] != nullptr)
				lights[i]->Open();
		}
		if (ambientLight != nullptr)
			ambientLight->Open();
	}

	Light::Light()
	{
	}
	Light::~Light()
	{
	}
	void Light::Open()
	{
		glEnable(GL_LIGHT0 + lightIndex);
		glLightfv(GL_LIGHT0 + lightIndex, GL_POSITION, position);
		glLightfv(GL_LIGHT0 + lightIndex, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT0 + lightIndex, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT0 + lightIndex, GL_SPECULAR, specular);
	}

	AmbientLight::AmbientLight()
	{
	}
	AmbientLight::~AmbientLight()
	{
	}
	void AmbientLight::Open()
	{
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	}
}