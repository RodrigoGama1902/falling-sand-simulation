#ifndef _WALL_H_
#define _WALL_H_

#include "simulation/elements/base/Element.h"
#include "simulation/elements/base/StaticSolid.h"

#include <iostream>

class Wall : public StaticSolid
{
public:
    Wall();
    virtual ~Wall();

    virtual Element *clone() const
    {
        return new Wall();
    }
};

#endif