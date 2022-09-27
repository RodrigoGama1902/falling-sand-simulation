#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "Shape.h"

class Circle : public Shape
{
public:
    Circle();
    Circle(const Vec2D &center, float radius);

    inline virtual Vec2D GetCenterPoint() const override { return mPoints[0]; };
    virtual std::vector<Vec2D> GetPoints() const override { return mPoints; };

    inline float GetRadius() const { return mRadius; }
    inline void SetRadius(float radius) { mRadius = radius; }
    inline void MoveTo(const Vec2D &newCenter) { mPoints[0] = newCenter; }

    bool Intersects(const Circle &other) const;
    bool ContainsPoint(const Vec2D &point) const;

private:
    float mRadius;
};

#endif