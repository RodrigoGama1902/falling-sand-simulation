#include "utils/Utils.h"
#include <cmath>

bool is_equal(float mX, float mY)
{
    return fabsf(mX - mY) < EPSILON;
}

bool is_greater_than_or_equal(float mX, float mY)
{
    return mX > mY || is_equal(mX, mY);
}

bool is_less_than_or_equal(float mX, float mY)
{
    return mX < mY || is_equal(mX, mY);
}