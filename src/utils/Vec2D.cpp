#include "Vec2D.h"
#include "Utils.h"

#include <cassert>
#include <cmath>
#include <iostream>

const Vec2D Vec2D::Zero;

//------------------------------
// Constructor
//------------------------------

Vec2D::Vec2D()
    : mX{0}, mY{0}
{
}

Vec2D::Vec2D(float mX, float mY)
    : mX{mX}, mY{mY}
{
}

Vec2D::Vec2D(const Vec2D &src)
    : mX{src.mX}, mY{src.mY}
{
}

//------------------------------
// Friend Functions
//------------------------------

Vec2D operator*(float scalar, const Vec2D &vec)
{
    return vec * scalar;
}

std::ostream &operator<<(std::ostream &ostream_ref, const Vec2D vec)
{
    ostream_ref << "(" << vec.mX << ", " << vec.mY << ")" << std::endl;
    return ostream_ref;
}

//------------------------------
// Class Methods
//------------------------------

float Vec2D::Mag2() const
{
    return Dot(*this);
}
float Vec2D::Mag() const
{
    return sqrt(Mag2());
}

Vec2D Vec2D::get_unit_vec() const
{

    float mag = Mag();

    if (mag > EPSILON)
    {
        return *this / mag;
    }

    return Vec2D::Zero;
}

Vec2D &Vec2D::normalize()
{
    float mag = Mag();

    if (mag > EPSILON)
    {
        *this /= mag;
    }

    return *this;
}

float Vec2D::Distance(const Vec2D &vec) const
{
    return (vec - *this).Mag();
}

//------------------------------
// Unary Operator Overload
//------------------------------

Vec2D Vec2D::operator-() const
{
    return Vec2D(-mX, -mY);
}

//------------------------------
// Binary Operator Overload
//------------------------------

bool Vec2D::operator==(const Vec2D &vec2) const
{
    return is_equal(mX, vec2.mX) && is_equal(mY, vec2.mY);
}

bool Vec2D::operator!=(const Vec2D &vec2) const
{
    return !(*this == vec2);
}

Vec2D Vec2D::operator*(float scalar) const
{
    return Vec2D(mX * scalar, mY * scalar);
}

Vec2D Vec2D::operator/(float scale) const
{
    assert(fabsf(scale) > EPSILON);
    return Vec2D(mX / scale, mY / scale);
}

Vec2D Vec2D::operator+(const Vec2D &vec2) const
{
    return Vec2D(mX + vec2.mX, mY + vec2.mY);
}

Vec2D Vec2D::operator-(const Vec2D &vec2) const
{
    return Vec2D(mX - vec2.mX, mY - vec2.mY);
}

Vec2D &Vec2D::operator*=(float scale)
{
    *this = *this * scale;
    return *this;
}

Vec2D &Vec2D::operator/=(float scale)
{
    assert(fabsf(scale) > EPSILON);
    *this = *this / scale;
    return *this;
}

Vec2D &Vec2D::operator+=(const Vec2D &vec2)
{
    *this = *this + vec2;
    return *this;
}

Vec2D &Vec2D::operator-=(const Vec2D &vec2)
{
    *this = *this - vec2;
    return *this;
}

float Vec2D::Dot(const Vec2D &vec) const
{
    return mX * vec.mX + mY * vec.mY;
}

Vec2D Vec2D::ProjectOnto(const Vec2D &vec2) const
{

    Vec2D unitVec2 = vec2.get_unit_vec();

    float dot = Dot(unitVec2);

    return unitVec2 * dot;
}

float Vec2D::AngleBetween(const Vec2D &vec2) const
{

    return acosf(get_unit_vec().Dot(vec2.get_unit_vec()));
}

Vec2D Vec2D::Reflect(const Vec2D &normal) const
{

    return *this - 2 * ProjectOnto(normal);
}

void Vec2D::Rotate(float angle, const Vec2D &aroundPoint)
{

    float cosine = cosf(angle);
    float sine = sinf(angle);

    Vec2D thisVec(mX, mY);

    thisVec -= aroundPoint;

    float xRot = thisVec.mX * cosine - thisVec.mY * sine;
    float yRot = thisVec.mX * sine + thisVec.mY * cosine;

    Vec2D rot = Vec2D(xRot, yRot);

    *this = rot + aroundPoint;
}
Vec2D Vec2D::RotationResult(float angle, const Vec2D &aroundPoint) const
{

    float cosine = cosf(angle);
    float sine = sin(angle);

    Vec2D thisVec(mX, mY);

    thisVec -= aroundPoint;

    float xRot = thisVec.mX * cosine - thisVec.mY * sine;
    float yRot = thisVec.mX * sine + thisVec.mY * cosine;

    Vec2D rot = Vec2D(xRot, yRot);

    return rot + aroundPoint;
}