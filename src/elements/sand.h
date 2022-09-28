#ifndef _SAND_H_
#define _SAND_H_

#include "element.h"
#include "grid.h"

class Sand : public Element
{

private:
    virtual ~Sand();

    int velocity_y;
    int velocity_direction;
    int friction;

public:
    Sand();
    virtual void Update(Grid &grid, int x, int y) override;

    virtual Element *clone() const
    {
        return new Sand(); // call the copy ctor.
    }
};

#endif