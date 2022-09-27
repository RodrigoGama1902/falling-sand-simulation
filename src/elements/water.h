#ifndef _WATER_H_
#define _WATER_H_

#include "element.h"
#include "grid.h"

class Water : public Element
{
public:
    Water();
    virtual void Update(Grid &grid, int x, int y) override;

    virtual Element *clone() const
    {
        return new Water(); // call the copy ctor.
    }

private:
    int velocity_y;
    int velocity_direction;
    int friction;
};

#endif