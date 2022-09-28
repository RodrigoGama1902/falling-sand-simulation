#ifndef _SAND_H_
#define _SAND_H_

#include "element.h"
#include "grid.h"

class Solid : public Element
{

private:
    virtual ~Solid();

    int velocity_y;
    int velocity_direction;
    int friction;

public:
    Solid();
    virtual void Update(Grid &grid, int x, int y) override;

    virtual Element *clone() const
    {
        return new Solid(); // call the copy ctor.
    }
};

#endif