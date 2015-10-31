#pragma once
#include "glut.h"
#include <string>
#include <vector>

using namespace std;

namespace DSOpenGL
{
	class Lights;
	class Light;
	class AmbientLight;

	class Lights
	{
	public:
		Lights(string lightFilePath);
		~Lights();
		void OpenAll();

	private:
		vector<Light*> lights;
		AmbientLight* ambientLight;
	};

	class Light
	{
		friend class Lights;
	public:
		Light();
		~Light();
		void Open();

	private:
		int lightIndex;
		GLfloat position[4];
		GLfloat ambient[3];
		GLfloat diffuse[3];
		GLfloat specular[3];
	};

	class AmbientLight
	{
		friend class Lights;
	public:
		AmbientLight();
		~AmbientLight();
		void Open();

	private:
		GLfloat ambient[3];
	};
}
