#include "vector.h"
#include <assert.h>
#include <math.h>

Vector::Vector(float x, float y, float z)
{
    this->X = x;
    this->Y = y;
    this->Z = z;
}

Vector::Vector()
{
    // Nichts
}

// Xa * Xb + Ya * Yb + Za * Zb = float
float Vector::dot(const Vector& v) const
{
    float skalarprodukt = this->X * v.X + this->Y * v.Y + this->Z * v.Z;
    return skalarprodukt;
}

// ( YaZb - ZaYb )
// ( ZaXb - XaZb ) = Vector
// ( XaYb - YaXb )
Vector Vector::cross(const Vector& v) const
{
    float neuX = this->Y * v.Z - this->Z * v.Y;
    float neuY = this->Z * v.X - this->X * v.Z;
    float neuZ = this->X * v.Y - this->Y * v.X;
    return Vector(neuX, neuY, neuZ);
}

// ( Xa + Xb )
// ( Ya + Yb ) = Vector
// ( Za + Zb )
Vector Vector::operator+(const Vector& v) const
{
    float neuX = this->X + v.X;
    float neuY = this->Y + v.Y;
    float neuZ = this->Z + v.Z;
    return Vector(neuX, neuY, neuZ);
}

// ( Xa - Xb )
// ( Ya - Yb ) = Vector
// ( Za - Zb )
Vector Vector::operator-(const Vector& v) const
{
    float neuX = this->X - v.X;
    float neuY = this->Y - v.Y;
    float neuZ = this->Z - v.Z;
    return Vector(neuX, neuY, neuZ);
}

// ( Xa  * c )
// ( Ya  * c ) = Vector
// ( Za  * c )
Vector Vector::operator*(float c) const
{
    float neuX = this->X * c;
    float neuY = this->Y * c;
    float neuZ = this->Z * c;
    return Vector(neuX, neuY, neuZ);
}

Vector Vector::operator/(float c) const
{
    float neuX = this->X / c;
    float neuY = this->Y / c;
    float neuZ = this->Z / c;
    return Vector(neuX, neuY, neuZ);
}

Vector Vector::operator-() const
{
    float neuX = this->X * -1;
    float neuY = this->Y * -1;
    float neuZ = this->Z * -1;
    return Vector(neuX, neuY, neuZ);
}

Vector& Vector::operator+=(const Vector& v)
{
    this->X = this->X + v.X;
    this->Y = this->Y + v.Y;
    this->Z = this->Z + v.Z;
    return *this; // dummy (remove)
}


// norm(->a) = ->a / |->a| => L�nge = 1
Vector& Vector::normalize()
{
    float laenge = length();
    this->X = this->X / laenge;
    this->Y = this->Y / laenge;
    this->Z = this->Z / laenge;
    return *this;
}

// |->a| = sqrt(x^2 + y^2 + z^2)
float Vector::length() const
{
    float laenge = sqrt(this->X * this->X + this->Y * this->Y + this->Z * this->Z);
    return laenge;
}

float Vector::lengthSquared() const
{
    float laenge = length();
    float quadratrischeLaenge = laenge * laenge;
    return quadratrischeLaenge;
}

Vector Vector::reflection(const Vector& normal) const
{
    Vector v = Vector(this->X, this->Y, this->Z);
    Vector r = v - (normal * normal.dot(v)) * 2;

    return r;
}

// d        = Richtung Punkt
// a, b, c  = Ecken vom Dreieck
// s        = l�nge des Strahls d von o zu p
bool Vector::triangleIntersection(const Vector& d, const Vector& a, const Vector& b, const Vector& c, float& s) const
{
    //Schritt 1

    Vector o = Vector(this->X, this->Y, this->Z);

    //n berechnen (Vom Urpsrung durch Ebene oder was ?)
    //test
    float length = (b - a).cross(c - a).length();
    Vector n = (b - a).cross(c - a) / length;

    //d berechnen (L�nge vom Urpsrung zur Ebene ?)
    float dLength = n.dot(a);

    //s berechnen (l�nge von origin zum Punkt p ?)
    s = (dLength - (n.dot(o))) / (n.dot(d));

    if (s > 0) {

        // Punkt p berechnen
        Vector p = o + (d * s);

        //Schritt 2
        float epsilon = 1e-6;
        float abc = (((b - a).cross(c - a)).length() / 2) + epsilon;
        float abp = (((b - a).cross(p - a)).length() / 2);
        float acp = (((c - a).cross(p - a)).length() / 2);
        float bcp = (((c - b).cross(p - b)).length() / 2);

        if (abc >= abp + acp + bcp) {
            return true;
        }

    }

    return false;
}
