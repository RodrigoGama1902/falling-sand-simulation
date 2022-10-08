#ifndef _MOVABLE_SOLID_H
#define _MOVABLE_SOLID_H

#include "Element.h"
#include "Grid.h"
#include "Solid.h"

class MovableSolid : public Solid
{
public:
    MovableSolid();
    virtual ~MovableSolid();

    virtual void UpdateColor() override;
    virtual void Update(Grid &grid, int x, int y) override;
    virtual void Move(Grid &grid, int x, int y) override;
};

#endif