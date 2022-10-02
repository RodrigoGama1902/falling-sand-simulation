#ifndef _STATIC_SOLID_H_
#define _STATIC_SOLID_H_

#include "element.h"
#include "grid.h"
#include "Solid.h"

class StaticSolid : public Solid
{
public:
    StaticSolid();
    virtual ~StaticSolid();

    virtual void Render() override;
    virtual void Update(Grid &grid, int x, int y) override;
    virtual void Move(Grid &grid, int x, int y) override;

    virtual Element *clone() const
    {
        return new StaticSolid(); // call the copy ctor.
    }
};

#endif