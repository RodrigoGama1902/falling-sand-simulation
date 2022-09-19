#ifndef _WALL_H_
#define _WALL_H_

#include "element.h"
#include "grid.h"

class Wall : public Element
{
public:
    Wall();
    virtual void Update(Grid &grid, int x, int y) override;
};

#endif