#include "water.h"
#include "element.h"
#include "null.h"
#include <iostream>

Water::Water() : Element()
{
    elmColor = Color(0, 191, 255, 255);
    solid = true;
}

void Water::Update(Grid &grid, int x, int y)
{

    Null *null_elm = new Null();

    // Water Simulation

    if (y + 1 >= grid.GetHeight())
    {
        return;
    }

    if (grid.GetElement(x, y + 1).solid == false)
    {
        grid.SetElement(x, y + 1, *this);
        grid.SetElement(x, y, *null_elm);
    }
    else if (grid.GetElement(x + 1, y + 1).solid == false)
    {
        grid.SetElement(x + 1, y + 1, *this);
        grid.SetElement(x, y, *null_elm);
    }
    else if (grid.GetElement(x - 1, y + 1).solid == false)
    {
        grid.SetElement(x - 1, y + 1, *this);
        grid.SetElement(x, y, *null_elm);
    }

    else if (grid.GetElement(x + 1, y).solid == false)
    {
        grid.SetElement(x + 1, y, *this);
        grid.SetElement(x, y, *null_elm);
    }
    else if (grid.GetElement(x - 1, y).solid == false)
    {
        grid.SetElement(x - 1, y, *this);
        grid.SetElement(x, y, *null_elm);
    }
}