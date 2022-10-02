#ifndef _LIQUID_H_
#define _LIQUID_H_

#include "Element.h"
#include "grid.h"

#include <iostream>

class Liquid : public Element
{
public:
    Liquid();
    virtual ~Liquid();

    virtual void Render() override;
    virtual void Move(Grid &grid, int x, int y) override;
    virtual void Update(Grid &grid, int x, int y) override;

protected:
    int density;
    bool solid = false;

    int elmColorFadeFrequency;
    int fadeStep;
    int currentColorFadeFrequency;
    int dispersion;
};

#endif