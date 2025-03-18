#include "vector.h"
#include <assert.h>
#include <math.h>

Vector::Vector( float x, float y, float z)
{
	// TODO: add your code
}

Vector::Vector()
{
	// TODO: add your code
}

float Vector::dot(const Vector& v) const
{
	// TODO: add your code
	return 0.0f; // dummy (remove)
}

Vector Vector::cross(const Vector& v) const
{
	// TODO: add your code
	return Vector(); // dummy (remove)
}



Vector Vector::operator+(const Vector& v) const
{
	// TODO: add your code
	return Vector(); // dummy (remove)
}

Vector Vector::operator-(const Vector& v) const
{
	// TODO: add your code
	return Vector(); // dummy (remove)
}

Vector Vector::operator*(float c) const
{
	// TODO: add your code
	return Vector(); // dummy (remove)
}

Vector Vector::operator-() const
{
	// TODO: add your code
	return Vector(); // dummy (remove)
}

Vector& Vector::operator+=(const Vector& v)
{
	// TODO: add your code
	return *this; // dummy (remove)
}



Vector& Vector::normalize()
{
	// TODO: add your code
	return *this; // dummy (remove)
}

float Vector::length() const
{
	// TODO: add your code
	return 0.0f; // dummy (remove)
}

float Vector::lengthSquared() const
{
	// TODO: add your code
	return 0.0f; // dummy (remove)
}

Vector Vector::reflection( const Vector& normal) const
{
	// TODO: add your code
	return Vector(); // dummy (remove)
}

bool Vector::triangleIntersection( const Vector& d, const Vector& a, const Vector& b, const Vector& c, float& s) const
{
	// TODO: add your code
	return false; // dummy (remove)
}
