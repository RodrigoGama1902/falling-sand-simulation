#ifndef _WALL_H_
#define _WALL_H_

#include "element.h"
#include "StaticSolid.h"
#include "Color.h"

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