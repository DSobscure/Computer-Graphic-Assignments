#include "Texture.h"
#include <iostream>

namespace DSOpenGL
{
	SingleTexture::SingleTexture(string fileDirectory, string fileName)
	{
		textures = new GLuint[1];
		glGenTextures(1, textures);

		string filePath = fileDirectory + "/" + fileName;

		FIBITMAP* rawImage = FreeImage_Load(FreeImage_GetFileType(filePath.c_str(), 0), filePath.c_str());
		FIBITMAP* image = FreeImage_ConvertTo32Bits(rawImage);

		int width = FreeImage_GetWidth(image);
		int height = FreeImage_GetHeight(image);
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height,
			0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(image));
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		FreeImage_Unload(rawImage);
		FreeImage_Unload(image);
	}
	SingleTexture::~SingleTexture()
	{
		delete textures;
	}
	void SingleTexture::Active(bool active)
	{
		if (active)
		{
			glActiveTexture(GL_TEXTURE0);
			glDisable(GL_CULL_FACE);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.5f);
			glBindTexture(GL_TEXTURE_2D, textures[0]);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		}
		else
		{
			glActiveTexture(GL_TEXTURE0);
			glDisable(GL_ALPHA_TEST);
			glDisable(GL_TEXTURE_2D);
		}
	}

	MultiTexture::MultiTexture(string fileDirectory, string* fileNames, int fileCount)
	{
		textures = new GLuint[fileCount];
		glGenTextures(fileCount, textures);

		for (int i = 0; i < fileCount; i++)
		{
			string filePath = fileDirectory + "/" + fileNames[i];
			FIBITMAP* rawImage = FreeImage_Load(FreeImage_GetFileType(filePath.c_str(), 0), filePath.c_str());
			FIBITMAP* image = FreeImage_ConvertTo32Bits(rawImage);
			int width = FreeImage_GetWidth(image);
			int height = FreeImage_GetHeight(image);

			glBindTexture(GL_TEXTURE_2D, textures[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height,
				0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(image));
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
			glGenerateMipmap(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

			FreeImage_Unload(rawImage);
			FreeImage_Unload(image);
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	MultiTexture::~MultiTexture()
	{
		delete textures;
	}
	void MultiTexture::Active(bool active)
	{
		if (active)
		{
			glActiveTexture(GL_TEXTURE0);
			glDisable(GL_CULL_FACE);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.5f);
			glBindTexture(GL_TEXTURE_2D, textures[0]);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

			glActiveTexture(GL_TEXTURE1);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textures[1]);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
			glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE);
		}
		else
		{
			glActiveTexture(GL_TEXTURE1);
			glDisable(GL_TEXTURE_2D);

			glActiveTexture(GL_TEXTURE0);
			glDisable(GL_ALPHA_TEST);
			glDisable(GL_TEXTURE_2D);
		}
	}

	CubeMapTexture::CubeMapTexture(string fileDirectory, string cubeFileNames[6])
	{
		textures = new GLuint[1];
		glGenTextures(1, textures);

		glBindTexture(GL_TEXTURE_CUBE_MAP, textures[0]);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		for (int i = 0; i < 6; i++)
		{
			string filePath = fileDirectory + "/" + cubeFileNames[i];
			FIBITMAP* rawImage = FreeImage_Load(FreeImage_GetFileType(filePath.c_str(), 0), filePath.c_str());
			FIBITMAP* image = FreeImage_ConvertTo32Bits(rawImage);
			int width = FreeImage_GetWidth(image);
			int height = FreeImage_GetHeight(image);

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
				width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(image));

			FreeImage_Unload(rawImage);
			FreeImage_Unload(image);
		}
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	CubeMapTexture::~CubeMapTexture()
	{
		delete textures;
	}
	void CubeMapTexture::Active(bool active)
	{
		if (active)
		{
			glBindTexture(GL_TEXTURE_CUBE_MAP, textures[0]);
			glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
			glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
			glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);
			glEnable(GL_TEXTURE_GEN_R);
			glEnable(GL_TEXTURE_CUBE_MAP);
		}
		else
		{
			glDisable(GL_TEXTURE_CUBE_MAP);
			glDisable(GL_TEXTURE_GEN_R);
			glDisable(GL_TEXTURE_GEN_T);
			glDisable(GL_TEXTURE_GEN_S);
		}
	}
}
