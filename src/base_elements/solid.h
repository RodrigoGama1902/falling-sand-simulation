#ifndef _SOLID_H_
#define _SOLID_H_

#include "element.h"
#include "grid.h"

class Solid : public Element
{

public:
    Solid();
    virtual ~Solid();

    // virtual void Render() override;
    // virtual void Update(Grid &grid, int x, int y) override;
    // virtual void Move(Grid &grid, int x, int y) override;

    /*
    virtual Element *clone() const
    {
        return new Solid(); // call the copy ctor.
    }*/

protected:
    int velocity_y;
    int velocity_direction;
    int friction;
};

#endif