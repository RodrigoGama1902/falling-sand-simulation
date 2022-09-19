#include "wall.h"
#include "element.h"
#include "null.h"
#include <iostream>

Wall::Wall() : Element()
{
    elmColor = Color(211, 211, 211, 255);
    solid = true;
}

void Wall::Update(Grid &grid, int x, int y)
{
}