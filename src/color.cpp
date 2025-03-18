#include "color.h"
#include <assert.h>

Color::Color()
{
    // Nichts
}

Color::Color(float r, float g, float b)
{
    this->R = r;
    this->G = g;
    this->B = b;
}

Color Color::operator*(const Color& c) const
{
    float neuR = this->R * c.R;
    float neuG = this->G * c.G;
    float neuB = this->B * c.B;
    return Color(neuR, neuG, neuB);
}

Color Color::operator*(const float Factor) const
{
    float neuR = this->R * Factor;
    float neuG = this->G * Factor;
    float neuB = this->B * Factor;
    return Color(neuR, neuG, neuB);
}

Color Color::operator+(const Color& c) const
{
    float neuR = this->R + c.R;
    float neuG = this->G + c.G;
    float neuB = this->B + c.B;
    return Color(neuR, neuG, neuB);
}

Color& Color::operator+=(const Color& c)
{
    this->R = this->R + c.R;
    this->G = this->G + c.G;
    this->B = this->B + c.B;
    return *this;
}