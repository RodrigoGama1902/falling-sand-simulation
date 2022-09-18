#ifndef _VEC2D_H_
#define _VEC2D_H_

#include <ostream>

class Vec2D
{
public:
    static const Vec2D Zero;

    Vec2D();
    Vec2D(float mX, float mY);
    Vec2D(const Vec2D &src);

    inline float GetX() const { return mX; }
    inline float GetY() const { return mY; }
    inline void SetX(float x) { mX = x; }
    inline void SetY(float y) { mY = y; }

    friend std::ostream &operator<<(std::ostream &ostream_ref, const Vec2D vec);

    bool operator==(const Vec2D &vec2) const;
    bool operator!=(const Vec2D &vec2) const;

    Vec2D operator-() const; // unary minus - Negating vector

    Vec2D operator*(float scale) const; // scalar multiplication
    Vec2D operator/(float scale) const;
    Vec2D operator+(const Vec2D &vec2) const;
    Vec2D operator-(const Vec2D &vec2) const;

    Vec2D &operator+=(const Vec2D &vec2);
    Vec2D &operator-=(const Vec2D &vec2);
    Vec2D &operator*=(float scale);
    Vec2D &operator/=(float scale);

    float Mag2() const;
    float Mag() const;

    Vec2D get_unit_vec() const;
    Vec2D &normalize();
    float Dot(const Vec2D &vec) const;

    Vec2D ProjectOnto(const Vec2D &vec2) const;
    float Distance(const Vec2D &vec) const;
    float AngleBetween(const Vec2D &vec2) const;
    Vec2D Reflect(const Vec2D &normal) const;

    void Rotate(float angle, const Vec2D &aroundPoint);
    Vec2D RotationResult(float angle, const Vec2D &aroundPoint) const;

    friend Vec2D operator*(float scalar, const Vec2D &vec);

private:
    float mX;
    float mY;
};

#endif