#pragma once
#include "FreeImage.h"
#include "glew.h"
#include <string>
#include "glut.h"

using namespace std;

namespace DSOpenGL
{
	enum TextureType
	{
		No_Texture,
		Single_Texture,
		Multi_Texture,
		Cube_Map
	};

	class Texture
	{
	public:
		virtual void Active(bool active) = 0;
	protected:
		GLuint*  textures;
	};

	class SingleTexture : public Texture
	{
	public:
		SingleTexture(string fileDirectory, string fileName);
		~SingleTexture();
		void Active(bool active);
	};

	class MultiTexture : public Texture
	{
	public:
		MultiTexture(string fileDirectory, string* fileNames, int fileCount);
		~MultiTexture();
		void Active(bool active);
	};

	class CubeMapTexture : public Texture
	{
	public:
		CubeMapTexture(string fileDirectory, string cubeFileNames[6]);
		~CubeMapTexture();
		void Active(bool active);
	};
}