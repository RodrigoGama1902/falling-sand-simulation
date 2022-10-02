#ifndef _MOVABLE_SOLID_H
#define _MOVABLE_SOLID_H

#include "Element.h"
#include "grid.h"
#include "Solid.h"

class MovableSolid : public Solid
{
public:
    MovableSolid();
    virtual ~MovableSolid();

    virtual void Render() override;
    virtual void Update(Grid &grid, int x, int y) override;
    virtual void Move(Grid &grid, int x, int y) override;
};

#endif