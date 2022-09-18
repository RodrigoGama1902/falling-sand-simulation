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

    Null *null_elm = new Null();

    grid.SetElement(x, y, *null_elm);
    grid.SetElement(x, y + 1, *this);
}