#ifndef _WATER_H_
#define _WATER_H_

#include "element.h"
#include "grid.h"

class Liquid : public Element
{
public:
    Liquid();
    virtual ~Liquid();

    virtual void Update(Grid &grid, int x, int y) override;

    virtual Element *clone() const
    {
        return new Liquid(); // call the copy ctor.
    }

private:
    int velocity_y;
    int velocity_direction;
    int friction;
};

#endif