#ifndef _UTILS_H_
#define _UTILS_H_

static const float EPSILON = 0.0001f;

const float PI = 3.14159265358979323846f;
const float TWO_PI = 2.0f * PI;

bool is_equal(float mX, float mY);

bool is_greater_than_or_equal(float mX, float mY);

bool is_less_than_or_equal(float mX, float mY);

#endif