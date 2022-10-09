#ifndef _HONEY_H_
#define _HONEY_H_

#include "simulation/elements/base/Element.h"
#include "simulation/elements/base/Liquid.h"
#include "graphics/Color.h"

class Honey : public Liquid
{
public:
    Honey();
    virtual ~Honey();

    virtual Element *clone() const
    {
        return new Honey();
    }

    int density = 0;
    int elmColorFadeFrequency = 200;
    int currentColorFadeFrequency = 200;

private:
    int velocity_y = 0;
    int friction = 20;
};

#endif