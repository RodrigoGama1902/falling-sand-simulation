#ifndef _WATER_H_
#define _WATER_H_

#include "element.h"
#include "grid.h"

class Water : public Element
{
public:
    Water();
    virtual void Update(Grid &grid, int x, int y) override;
};

#endif