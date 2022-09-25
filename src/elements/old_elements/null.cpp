
#include "element.h"
#include "null.h"

Null::Null() : Element()
{
    elmColor = Color(0, 0, 0, 0);
    solid = false;
}

void Null::Update(Grid &grid, int x, int y)
{
}