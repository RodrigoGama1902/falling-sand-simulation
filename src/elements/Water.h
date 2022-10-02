#ifndef _WATER_H_
#define _WATER_H_

#include "Element.h"
#include "Liquid.h"
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
    int elmColorFadeFrequency = 0;
    int currentColorFadeFrequency = 0;

private:
    int velocity_y = 0;
    int friction = 20;
    int fadeStep = 1;
};

#endif