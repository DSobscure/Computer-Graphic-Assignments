#include "Model.h"
#include <iostream>

namespace DSOpenGL
{
	Model::Model(string fileDirectory, string fileName, TextureType type)
	{
		modelMesh = new mesh(fileDirectory, fileName);
		textureType = type;
	}
	Model::~Model()
	{
		if (modelMesh == nullptr)
			delete modelMesh;
	}
	void Model::Display()
	{
		int lastMaterial = -1;

		if(textureType != No_Texture)
			texture->Active(true);

		glPushMatrix();

		glTranslatef(transform[0], transform[1], transform[2]);
		glRotatef(angle, axis[0], axis[1], axis[2]);
		glScalef(scale[0], scale[1], scale[2]);
		for (size_t i = 0; i < modelMesh->fTotal; ++i)
		{
			if (lastMaterial != modelMesh->faceList[i].m)
			{
				lastMaterial = (int)modelMesh->faceList[i].m;
				glMaterialfv(GL_FRONT, GL_AMBIENT, modelMesh->mList[lastMaterial].Ka);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, modelMesh->mList[lastMaterial].Kd);
				glMaterialfv(GL_FRONT, GL_SPECULAR, modelMesh->mList[lastMaterial].Ks);
				glMaterialfv(GL_FRONT, GL_SHININESS, &modelMesh->mList[lastMaterial].Ns);
			}

			glBegin(GL_TRIANGLES);
			for (size_t j = 0; j<3; ++j)
			{
				glMultiTexCoord2fv(GL_TEXTURE0, modelMesh->tList[modelMesh->faceList[i][j].t].ptr);
				glMultiTexCoord2fv(GL_TEXTURE1, modelMesh->tList[modelMesh->faceList[i][j].t].ptr);
				glNormal3fv(modelMesh->nList[modelMesh->faceList[i][j].n].ptr);
				glVertex3fv(modelMesh->vList[modelMesh->faceList[i][j].v].ptr);
			}
			glEnd();
		}
		glPopMatrix();
		if (textureType != No_Texture)
			texture->Active(false);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void Model::Translate(GLfloat x, GLfloat y)
	{
		transform[0] += x;
		transform[1] += y;
	}
}