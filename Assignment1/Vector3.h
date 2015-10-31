#pragma once
#include "glut.h"

namespace DSOpenGL
{
	class Vector3
	{
	public:
		Vector3(GLfloat x, GLfloat y, GLfloat z);
		Vector3(GLfloat value[3]);
		float Magnitude();
		Vector3 Normarlize();
		Vector3 Cross(Vector3 vector);
		void ToGLfloatArray(GLfloat result[3]);
		Vector3 operator+(Vector3 vector);
		Vector3 operator-(Vector3 vector);
		Vector3 operator*(GLfloat value);
		Vector3 operator/(GLfloat value);
	
	private:
		GLfloat _x, _y, _z;
	};
}