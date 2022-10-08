#ifndef _SOLID_H_
#define _SOLID_H_

#include "Element.h"
#include "Grid.h"

class Solid : public Element
{

public:
    Solid();
    virtual ~Solid();

    virtual void UpdateColor() override;

protected:
    int velocity_y;
    int velocity_direction;
    int friction;
};

#endif