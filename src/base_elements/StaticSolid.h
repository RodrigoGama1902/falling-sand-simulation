#ifndef _STATIC_SOLID_H_
#define _STATIC_SOLID_H_

#include "Element.h"
#include "Grid.h"
#include "Solid.h"

class StaticSolid : public Solid
{
public:
    StaticSolid();
    virtual ~StaticSolid();

    virtual void Render() override;
    virtual void Update(Grid &grid, int x, int y) override;
    virtual void Move(Grid &grid, int x, int y) override;
};

#endif