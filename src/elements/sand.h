#include "element.h"
#include "grid.h"

class Sand : public Element
{
public:
    Sand();
    virtual void Update(Grid &grid, int x, int y) override;
};