#ifndef _WATER_H_
#define _WATER_H_

#include "simulation/elements/base/Element.h"
#include "simulation/elements/base/Liquid.h"

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

    int elmColorFadeFrequency = 0;
    int currentColorFadeFrequency = 0;

private:
    int velocity_y = 0;
    int friction = 20;
    int fadeStep = 1;
};

#endif