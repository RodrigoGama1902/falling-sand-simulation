#ifndef _STATIC_SOLID_H_
#define _STATIC_SOLID_H_

#include "simulation/elements/base/Element.h"
#include "simulation/Grid.h"
#include "simulation/elements/base/Solid.h"

class StaticSolid : public Solid
{
public:
    StaticSolid();
    virtual ~StaticSolid();

    virtual void UpdateColor() override;
    virtual void Update(Grid &grid, int x, int y) override;
    virtual void Move(Grid &grid, int x, int y) override;
};

#endif