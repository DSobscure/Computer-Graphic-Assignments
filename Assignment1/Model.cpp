#include "Model.h"
#include <iostream>

namespace DSOpenGL
{
	Model::Model(string modelFilePath)
	{
		modelMesh = new mesh(modelFilePath.c_str());
	}
	Model::~Model()
	{
		if (modelMesh == nullptr)
			delete modelMesh;
	}
	void Model::Display()
	{
		int lastMaterial = -1;
		glPushMatrix();
			glTranslatef(transform[0], transform[1], transform[2]);
			glRotatef(angle, axis[0], axis[1], axis[2]);
			glScalef(scale[0], scale[1], scale[2]);
			for (size_t i = 0; i < modelMesh->fTotal; ++i)
			{
				// set material property if this face used different material
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
					glNormal3fv(modelMesh->nList[modelMesh->faceList[i][j].n].ptr);
					glVertex3fv(modelMesh->vList[modelMesh->faceList[i][j].v].ptr);
				}
				glEnd();
			}
		glPopMatrix();
	}
	void Model::Translate(GLfloat x, GLfloat y)
	{
		transform[0] += x;
		transform[1] += y;
	}
}