#include "sand.h"
#include "element.h"
#include "null.h"
#include <iostream>

Sand::Sand() : Element()
{
    elmColor = Color(255, 255, 0, 255);
}

void Sand::Update(Grid &grid, int x, int y)
{

    // grid.SetElement(x, y + 1, Eleme);

    Null *null_elm = new Null();

    grid.SetElement(x, y - 1, *this);
    grid.SetElement(x, y, *null_elm);

    /*
    if (grid.GetElement(x, y + 1).elmColor.a == 0)
    {
        grid.SetElement(x, y + 1, *this);
        grid.SetElement(x, y, Element());
    }
    else if (grid.GetElement(x + 1, y + 1).elmColor.a == 0)
    {
        grid.SetElement(x + 1, y + 1, *this);
        grid.SetElement(x, y, Element());
    }
    else if (grid.GetElement(x - 1, y + 1).elmColor.a == 0)
    {
        grid.SetElement(x - 1, y + 1, *this);
        grid.SetElement(x, y, Element());
    }
    */
}