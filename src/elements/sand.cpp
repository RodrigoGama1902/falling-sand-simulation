#include "sand.h"
#include "element.h"
#include "null.h"
#include <iostream>
#include <random>
#include <time.h>

Sand::Sand() : Element()
{
    solid = true;
    int m = rand() % 100;
    elmColor = Color(255 * m, 255 * m, 0 * m, 255);
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