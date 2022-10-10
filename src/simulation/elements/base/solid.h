#ifndef _SOLID_H_
#define _SOLID_H_

#include "simulation/elements/base/Element.h"
#include "simulation/Grid.h"

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