#ifndef _SAND_H_
#define _SAND_H_

#include "element.h"
#include "MovableSolid.h"
#include "Color.h"

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