#include "sand.h"
#include "element.h"
#include "null.h"
#include <iostream>
#include <random>

Sand::Sand() : Element()
{
    std::cout << "Sand created" << std::endl;
    elmColor = Color(255, 255, 0, 255);
    solid = true;
}

void Sand::Update(Grid &grid, int x, int y)
{

    Null *null_elm = new Null();

    // stop at screen y edge

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
}