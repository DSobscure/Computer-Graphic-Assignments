#include "Vector3.h"
#include <math.h>
#include <iostream>

namespace DSOpenGL
{
	Vector3::Vector3(GLfloat x, GLfloat y, GLfloat z)
	{
		_x = x;
		_y = y;
		_z = z;
	}
	Vector3::Vector3(GLfloat value[3])
	{
		_x = value[0];
		_y = value[1];
		_z = value[2];
	}
	float Vector3::Magnitude()
	{
		return sqrt(_x*_x + _y*_y + _z*_z);
	}
	Vector3 Vector3::Normarlize()
	{
		Vector3 result = *this / Magnitude();
		return result;
	}
	Vector3 Vector3::Cross(Vector3 vector)
	{
		Vector3 result(_y*vector._z - _z*vector._y, _z*vector._x - _x*vector._z, _x*vector._y - _y*vector._x);
		return result;
	}
	void Vector3::ToGLfloatArray(GLfloat result[3])
	{
		result[0] = _x;
		result[1] = _y;
		result[2] = _z;
	}
	Vector3 Vector3::operator+(Vector3 vector)
	{
		Vector3 result(_x+vector._x, _y + vector._y, _z + vector._z);
		return result;
	}
	Vector3 Vector3::operator-(Vector3 vector)
	{
		Vector3 result(_x - vector._x, _y - vector._y, _z - vector._z);
		return result;
	}
	Vector3 Vector3::operator*(GLfloat value)
	{
		Vector3 result(_x*value, _y*value, _z*value);
		return result;
	}
	Vector3 Vector3::operator/(GLfloat value)
	{
		if (value != 0)
		{
			Vector3 result(_x/value, _y/value, _z/value);
			return result;
		}
		else
		{
			std::cerr << "Error: Vector3 divide with 0" << std::endl;
			Vector3 result(0,0,0);
			return result;
		}
	}
}