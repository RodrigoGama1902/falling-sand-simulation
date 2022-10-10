#ifndef _MOVABLE_SOLID_H
#define _MOVABLE_SOLID_H

#include "simulation/elements/base/Element.h"
#include "simulation/Grid.h"
#include "simulation/elements/base/Solid.h"

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