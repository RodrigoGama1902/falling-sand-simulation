#include "element.h"
#include "grid.h"

class Water : public Element
{
public:
    Water();
    virtual void Update(Grid &grid, int x, int y) override;
};