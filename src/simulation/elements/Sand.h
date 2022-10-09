#ifndef _SAND_H_
#define _SAND_H_

#include "simulation/elements/base/Element.h"
#include "simulation/elements/base/MovableSolid.h"
#include "graphics/Color.h"

#include <iostream>

class Sand : public MovableSolid
{
public:
    Sand();
    virtual ~Sand();

    virtual Element *clone() const
    {
        return new Sand();
    }
};

#endif