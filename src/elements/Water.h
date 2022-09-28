#ifndef _WATER_H_
#define _WATER_H_

#include "element.h"
#include "liquid.h"
#include "Color.h"

#include <iostream>

class Water : public Liquid
{
public:
    Water();
    virtual ~Water();

    virtual Element *clone() const
    {
        return new Water();
    }

    int density = 0;
    int elmColorFadeFrequency = 5;
    int currentColorFadeFrequency = 0;

private:
    int velocity_y = 0;
    int friction = 20;
};

#endif