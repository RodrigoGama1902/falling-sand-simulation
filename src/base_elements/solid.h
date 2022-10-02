#ifndef _SOLID_H_
#define _SOLID_H_

#include "Element.h"
#include "grid.h"

class Solid : public Element
{

public:
    Solid();
    virtual ~Solid();

protected:
    int velocity_y;
    int velocity_direction;
    int friction;
};

#endif